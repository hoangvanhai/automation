#include "stream.h"
#include "limits.h"

Stream::Stream()
{
    m_comThreadTerm = true;
    m_processThreadTerm = true;
    m_user  = NULL;
    m_dataEvent  = nullptr;    
    m_errCode = 0;
    m_recvFifo.Reset();
    m_recvCount = 0;
    m_recvDlen = 0;
    m_seqError = 0;
    m_isError = false;
    m_seqRemote = 0xFFFF;
    m_seqLocal = 0;
    m_seqCMDfrm = 0;
    m_memRecv = nullptr;
    m_memSend = nullptr;
    frmRecv  = NULL;
    frmSend  = NULL;
    m_fRecvData = nullptr;
    m_fSentData = nullptr;
    m_fError = nullptr;
    m_recvEvtParam = NULL;
    m_sendEvtParam = NULL;
    m_errorEvtParam = NULL;
    m_fragStt = Frag_Frame_Done;
    m_flag.Started = false;
    m_flag.WaitAckFrame = false;
    m_flag.CheckSeqNum = false;
    m_fragSeq = 0;
    memset(aesKey, 0, 100);
    hasKey = false;
    m_crypt = std::make_shared<Crypto>();
}

bool Stream::Start(std::string ipaddress, int port)
{

    ASSERT(m_packageOneFrame.Init(STREAM_MAX_BYTE_IN_PACKAGE) == true);

    StreamRegisterEvtCallback(Stream_Evt_Recv_Data,
                              [&](std::shared_ptr<uint8_t> pMem,
                              void *user) {
        StreamProcessFrame(pMem, user);
    }, 0);

    if(MemAlloc() == false) {
        return false;
    }

    m_recvFifo.Init(UDP_FRAME_SIZE);

    m_flag.Started = true;
    m_flag.CheckSeqNum = true;

    LREP("Stream dest address: {}:{}\r\n", ipaddress, port);
    m_streamDest = std::make_shared<communication::endpoint::udp::Destination>(ipaddress, port);    
    m_comThreadTerm = false;
    m_commThread = std::thread([&] {
        ThreadFunction();
    });

    m_processThreadTerm = false;
    m_processThread = std::thread([&] {
        ProcessThreadFunc();
    });

    m_Timer = std::make_shared<Timer>(1000);
    m_Timer->StartTimerObject();

    m_hUpdateTimer =  m_Timer->Create(Clb_UpdateTimer, this);
    m_Timer->SetRate(m_hUpdateTimer, 20);
    m_Timer->Start(m_hUpdateTimer);

    return true;
}

void Stream::Stop()
{
    if(m_comThreadTerm == false)
    {
        m_Timer->Stop(m_hUpdateTimer);
        //LREP("Delete update timer\r\n");
        m_Timer->Delete(m_hUpdateTimer);
        //LREP("Stop platform timer\r\n")
        m_Timer->StopTimerObject();
        //LREP("Deleted timer object\r\n");
        m_Timer.reset();
        m_Timer = nullptr;

        m_comThreadTerm = true;
        if(m_commThread.joinable()) {
            m_commThread.join();
        }
    }

    if(m_processThreadTerm == false)
    {
        m_processThreadTerm = true;
        if(m_processThread.joinable())
            m_processThread.join();
    }

    m_recvFifo.DeInit();
    m_packageOneFrame.DeInit();
}

void Stream::StreamRegisterEvtCallback(Stream::StreamEvent evt,
                                       std::function<void (std::shared_ptr<uint8_t>, void *)> func,
                                       void *pParam)
{
    switch(evt) {
    case Stream_Evt_Error:
        m_fError = func;
        m_errorEvtParam = pParam;
        break;
    case Stream_Evt_Recv_Data:
        m_fRecvData = func;
        m_recvEvtParam  = pParam;
        break;
    case Stream_Evt_Send_Done:
        m_fSentData = func;
        m_sendEvtParam = pParam;
        break;
    default:
        break;
    }
}


Stream::WaitingPackage Stream::PopWaitingSeq(uint16_t seq)
{
    WaitingPackage wait;
    if(m_waitingPackageList.size() > 0) {
        std::list<WaitingPackage>::iterator iter = m_waitingPackageList.begin();
        while(iter != m_waitingPackageList.end()) {
            wait = *iter;
            if(wait.sequence == seq) { // Found
                wait.splitedData.clear();   // Clear all data in list
                iter = m_waitingPackageList.erase(iter);
                return wait;
            }
            ++iter;
        }
        ASSERT(false); // Not found
        return wait;
    } else {
        ASSERT(false); // List empty
        return wait;
    }
}

bool Stream::SearchWaitingSeq(uint16_t seq)
{
    WaitingPackage wait;
    if(m_waitingPackageList.size() > 0) {
        std::list<WaitingPackage>::iterator iter = m_waitingPackageList.begin();
        while(iter != m_waitingPackageList.end()) {
            wait = *iter;
            if(wait.sequence == seq) { // Found
                return true;
            }
            ++iter;
        }        
        return false;
    } else {
        return false;
    }
}

bool Stream::SearchFrmIdxOnSeq(uint8_t frmIdx, std::list<SplitedFrame> &list)
{
    SplitedFrame frame;
    if(list.size() > 0) {
        std::list<SplitedFrame>::iterator iter = list.begin();
        while(iter != list.end()) {
            frame = *iter;
            if(frame.fragSeq == frmIdx) { // Found
                return true;
            }
            ++iter;
        }
        ASSERT(false); // Not found
        return false;
    } else {
        ASSERT(false); // List empty
        return false;
    }
}

bool Stream::AddWaitingSeqNew(uint16_t seq, Stream::SplitedFrame frm)
{
    WaitingPackage wait;
    if(m_waitingPackageList.size() > 5) {
        LREP("Too many splited package error\n");
        std::list<WaitingPackage>::iterator iter = m_waitingPackageList.begin();
        m_waitingPackageList.erase(iter);
    }

    if(SearchWaitingSeq(seq)) {
        LREP("Add new but already existed\n");
        return false;
    }

    wait.sequence = seq;
    wait.splitedData.push_back(frm);
    m_waitingPackageList.push_back(wait);
    return true;
}

bool Stream::AddWaitingSeqOld(uint16_t seq, Stream::SplitedFrame frm)
{
    WaitingPackage wait;
    if(m_waitingPackageList.size() > 5) {
        LREP("Too many splited package error\n");
        std::list<WaitingPackage>::iterator iter = m_waitingPackageList.begin();
        m_waitingPackageList.erase(iter);
    }

    if(m_waitingPackageList.size() > 0) {
        std::list<WaitingPackage>::iterator iter = m_waitingPackageList.begin();
        while(iter != m_waitingPackageList.end()) {
            wait = *iter;
            if(wait.sequence == seq) { // Found
                wait.splitedData.push_back(frm);
                return true;
            }
            ++iter;
        }
    }
    LREP("Add old but not existed\n");
    return false;
}

bool Stream::SortAndGetDataOnList(FIFO &fifo, std::list<SplitedFrame> &list)
{    
    SplitedFrame frm;

    // Check number frame in list is sufficient
    for(size_t i = 0; i < list.size(); i++) {
        if(!SearchFrmIdxOnSeq(i, list)) {
            LREP("Sequence not enough\n");
            return false;
        }
    }
    list.sort(SortData);
    if(list.size() > 0) {
        std::list<SplitedFrame>::iterator iter = list.begin();
        while(iter != list.end()) {
            frm = *iter;
            fifo.Push(frm.body.get(), frm.length);
            iter++;
        }
    }
    return true;
}

bool Stream::SortData(const Stream::SplitedFrame first, const Stream::SplitedFrame second)
{
    return (first.fragSeq < second.fragSeq);
}


void Stream::ThreadFunction() {
    //unsigned int count = 0;
    m_stream = std::make_shared<communication::endpoint::udp::Socket>();
    ASSERT(m_stream != nullptr);

    communication::endpoint::udp::AttributeListenAddressAndPort destArgs;
    destArgs.address = "any";    //m_streamDest->getAddress();
    destArgs.port    = m_streamDest->getPort();

    int err = m_stream->setAttribute(communication::endpoint::udp::Attribute_ListenAddressAndPort, &destArgs);
    ASSERT(err == 0);
    if(err != 0) {
        LREP("Can not bind sock with address {}:{}\r\n", destArgs.address, destArgs.port);
        return;
    }

    LREP("Stream listen on: {}:{}\r\n", destArgs.address, destArgs.port);
    communication::endpoint::udp::AttributeBufferSize bufferSizeSet;
    bufferSizeSet.recvBufferSize = 1024*1024*1;
    bufferSizeSet.sendBufferSize = 1024*1024*2;
    err = m_stream->setAttribute(communication::endpoint::udp::Attribute_BufferSize, &bufferSizeSet);
    ASSERT(err == 0);

    uint8_t rxBuf[65536];

    std::shared_ptr<communication::endpoint::udp::Destination> clientDest =
            std::make_shared<communication::endpoint::udp::Destination>("", 0);

    while(!m_comThreadTerm){
        int err = m_stream->waitEvent(communication::Event_Readable, 100);

        if(err & communication::Event_Error){
            LREP_WARN("select failed\r\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }else if(err & communication::Event_Readable){
            int rlen = m_stream->readData(rxBuf, 65536, clientDest);
            if(rlen > 0) {        
                if(m_recvFifo.Push(rxBuf, (uint32_t)rlen) < (uint32_t)rlen) {
                    LREP("Stream push large data {} -> FIFO error -> Reset FIFO\n");
                    m_recvFifo.Reset();
                }                
                m_trigger.cv.notify_one();
            }

        }else if(err == communication::Event_Timeout) {

        }
    }

}

int Stream::SendDataToServerWithLen(uint8_t* data, int len)
{
    int event = m_stream->waitEvent(communication::Event_Writable, 100);

    if(event & communication::Event_Error){
        LREP("select failed");
        return -1;
    }

    if((event & communication::Event_Writable) == 0){
        LREP("event not writable");
        return -1;
    }

    int length = len + 4;

    uint8_t *sendData = new uint8_t[length];

    *((uint32_t*)sendData) = len;
    memcpy(&sendData[4], data, len);
    m_stream->writeData(sendData, length, m_streamDest);

    delete[] sendData;
    return 0;
}

void Stream::ProcessThreadFunc()
{

    std::unique_lock<std::mutex> lck(m_trigger.mtx);
    while(!m_processThreadTerm) {
        //TODO
        if(m_trigger.cv.wait_for(lck, std::chrono::milliseconds(100))
                == std::cv_status::no_timeout) {
            ReceiveTask();
            SendTask();            
        }
    }
}

void Stream::ReceiveTask()
{
    std::shared_ptr<uint8_t> pMem;
    size_t          listSize = 0;
    StreamFrame      *pFrameInfo = NULL;
    /*------------------------------------------------------------------------*/
    /* Run RecvTask of Layer 2 to process receiving frame */
    StreamAction action = RecvTask();

    switch (action)
    {
    case Stream_Act_None:
        break;
    case Stream_Recv_Ack:
        //LREP("MAC_RCV_ACK\r\n");
        listSize = m_listSentData.size();
        if(listSize == 0) {
            ASSERT(false);
            return;
        }
        m_lsentDataMutex.lock();
        pMem = SearchAndPop(m_listSentData, m_seqCMDfrm);
        m_lsentDataMutex.unlock();
        if(pMem == NULL) {
            ASSERT(false);
            return;
        }
        if (pMem != NULL) {
            //LREP("Remove Seq = {} \r\n",(int)m_seqCMDfrm);
            pMem.reset();
        }

        break;
    case Stream_Recv_Nack:
        LREP("RCV_NACK {}\r\n", (int)m_seqCMDfrm);
        listSize = m_listSentData.size();
        if(listSize == 0) {
            ASSERT(false);
            return;
        }
        m_lsentDataMutex.lock();
        pMem = SearchAndPop(m_listSentData, m_seqCMDfrm);
        m_lsentDataMutex.unlock();
        if(pMem == NULL) {
            ASSERT(false);
            return;
        }
        pFrameInfo = (StreamFrame*)pMem.get();
        pFrameInfo->timeout = STREAM_TIMEOUT_MILLISECOND;
        LREP("-> Resend frm: {}\r\n", (int)m_seqCMDfrm);
        m_listSendingData.push_back(pMem);

        break;

    case Stream_Req_Ack:
        //L2 get a data frame requiring ACK		->	Add CMD_ACK frame to queue
        StreamSendImmediate(STREAM_ACK, 0, NULL, 0, Frame_Command);
        break;

    case Stream_Req_Nack:
        m_isError = true;
        LREP("SEND NACK SEQ: {}\r\n", (int)m_seqError);
        //L2 get a frame but DLEN or CRCD is wrong	->	Add CMD_NACK frame to queue
        StreamSendImmediate(STREAM_NACK, 0, NULL, 0, Frame_Command);
        m_isError = false;
        break;

    default:
        ASSERT(false);
        break;
    }
}

void Stream::SendTask()
{
    /*------------------------------------------------------------------------*/
    //Update State of waiting frames
    if (m_flag.WaitAckFrame == true) {
        m_flag.WaitAckFrame = false;
        CheckTimeOutOfSentFrame();
    }

    std::shared_ptr<uint8_t> pMem = nullptr;
    if (m_listSendingCmd.size() > 0) {
        pMem = PopHead(m_listSendingCmd);
    } else if (m_listSendingData.size() > 0) {
        m_lsendingDataMutex.lock();
        pMem = PopHead(m_listSendingData);
        m_lsendingDataMutex.unlock();
    }

    if (pMem != nullptr) {
        if (RunSendFrame(pMem) != STREAM_ERR_SUCCESS) {
            ASSERT(false);
        }
    }
}

Stream::StreamStatus Stream::RunSendFrame(std::shared_ptr<uint8_t> pMem)
{
    StreamFrame     *pFrameInfo;
    uint8_t 		*pSendFrm;
    uint8_t 		*pData;
    StreamStatus    u8ErrorCode = STREAM_ERR_SUCCESS;

    if(pMem == nullptr) {
        ASSERT(false);
        return STREAM_ERR_MEM;
    }
    /*-------------------------*/
    // Check valid and parameters
    /*-------------------------*/
    if (m_flag.Started != true) {
        u8ErrorCode = STREAM_ERR_NOT_STARTED;
        ASSERT(false);
        FireEvent(Stream_Evt_Error);
        return u8ErrorCode;
    }

    /*-------------------------*/
    pFrameInfo = (StreamFrame *)pMem.get();
    pFrameInfo->maxSend--;
    m_memSend = pMem; /*save this for callback function*/
    frmSend = (uint8_t*)pFrameInfo + sizeof(StreamFrame);
    pSendFrm = frmSend;
    pData = &frmSend[STREAM_IDX_DATA0];
    /*---------------------------*/
    // Building the sending frame
    /*---------------------------*/
    pSendFrm[STREAM_IDX_PREAM]      = STREAM_CST_PREAMBLE;
    pSendFrm[STREAM_IDX_SEQNUM]     = pFrameInfo->seq >> 8;
    pSendFrm[STREAM_IDX_SEQNUM + 1] = pFrameInfo->seq & 0x00FF;
    pSendFrm[STREAM_IDX_FRAG]       = pFrameInfo->flag;
    pSendFrm[STREAM_IDX_FLAG]       = pFrameInfo->frag;
    pSendFrm[STREAM_IDX_DLEN]       = (uint8_t)(pFrameInfo->dataLength >> 8);
    pSendFrm[STREAM_IDX_DLEN + 1]   = (uint8_t)(pFrameInfo->dataLength & 0x00FF);

    if (pFrameInfo->dataLength > STREAM_MAX_DLEN) {
        u8ErrorCode = STREAM_ERR_PARAM;
        ASSERT(false);
        FireEvent(Stream_Evt_Error);
        return u8ErrorCode;
    }
    //CRCD
    if (pFrameInfo->dataLength != 0) {
        uint16_t crc = CheckCRC16(pData, pFrameInfo->dataLength);
        pSendFrm[STREAM_IDX_CRCD] = (uint8_t)((crc >> 8) & 0x00FF);
        pSendFrm[STREAM_IDX_CRCD + 1] = (uint8_t)(crc & 0x00FF);
    } else {
        pSendFrm[STREAM_IDX_CRCD] = 0;
        pSendFrm[STREAM_IDX_CRCD + 1] = 0;
    }

    int slen = SendDataToServerWithoutLen(frmSend, pFrameInfo->dataLength + STREAM_HEADER_SIZE);
    ASSERT(slen > 0);
    FireEvent(Stream_Evt_Send_Done);
    return u8ErrorCode;
}

void Stream::CheckTimeOutOfSentFrame()
{
    size_t listSize = m_listSentData.size();
    for (size_t idx = 0; idx < listSize; idx++) {
        m_lsentDataMutex.lock();
        std::shared_ptr<uint8_t> pMem = PopHead(m_listSentData);
        m_lsentDataMutex.unlock();
        ASSERT(pMem != NULL);
        StreamFrame* pFrameInfo = (StreamFrame*)pMem.get();
        // If frame still wait ACK
        if (pFrameInfo->maxSend > 0) {
            if (--pFrameInfo->timeout == 0)
            {
                //if need, can set timeout by random value
                pFrameInfo->timeout = STREAM_TIMEOUT_MILLISECOND;
                m_lsendingDataMutex.lock();
                m_listSendingData.push_back(pMem);
                m_lsendingDataMutex.unlock();
                LREP("Resend frm {}\r\n", (int)pFrameInfo->seq);
            }
            else // If frame is not timeout
            {
                m_lsentDataMutex.lock();
                m_listSentData.push_back(pMem);
                m_lsentDataMutex.unlock();
            }
        } else { // After u8NumSend passed
            LREP("NOT GET ACK SEQ {}\r\n", (int)pFrameInfo->seq);
            //delete frame
            if(pMem != NULL)
                pMem.reset();
        }
    }
}

/**
 * @brief Stream::StreamSendLater
 * @param flag
 * @param frag
 * @param data
 * @param length
 * @param ftype
 * @return
 */
bool Stream::StreamSendLater(uint8_t flag, uint8_t frag, uint8_t *data,
                        uint32_t length, FrameType ftype)
{
    if(m_flag.Started != true) {
        ASSERT(false);
        return false;
    }

    int leng = sizeof(StreamFrame) + STREAM_HEADER_SIZE + length ;    
    std::shared_ptr<uint8_t> pMem(new uint8_t[leng],
            [](uint8_t* p){delete[] p;});

    if (pMem == nullptr) {
        ASSERT(false);
        return false;
    }


    StreamFrame *pFrameInfo = (StreamFrame*)pMem.get();

    pFrameInfo->flag = flag;
    pFrameInfo->frag = frag;
    pFrameInfo->dataLength = length;
    pFrameInfo->frame = (uint8_t*)pFrameInfo + sizeof(StreamFrame);
    pFrameInfo->data = &pFrameInfo->frame[STREAM_IDX_DATA0];

    //SEQ
    if (ftype == Frame_Command){
        if(STREAM_IS_NACK_FRM(flag) && m_isError) {
            pFrameInfo->seq = m_seqError;
        } else {
            pFrameInfo->seq = m_seqRemote;
        }
    } else {
        pFrameInfo->seq = m_seqLocal++;
    }

    if (length > 0) {
        for (uint16_t u16Idx = 0; u16Idx < length; u16Idx++) {
            pFrameInfo->data[u16Idx] = data[u16Idx];
        }
    }

    pFrameInfo->maxSend = STREAM_MAX_NUM_SEND;
    pFrameInfo->timeout = STREAM_TIMEOUT_MILLISECOND;


    if(STREAM_IS_DATA_FRM(flag)) {
        m_lsendingDataMutex.lock();
        m_listSendingData.push_back(pMem);
        m_lsendingDataMutex.unlock();
    } else {
        m_listSendingCmd.push_back(pMem);
    }

    m_trigger.cv.notify_one();
    return true;
}

/**
 * @brief Stream::StreamSendImmediate
 * @param flag
 * @param frag
 * @param data
 * @param length
 * @param ftype
 * @return
 */
bool Stream::StreamSendImmediate(uint8_t flag, uint8_t frag, uint8_t *data, uint32_t length, Stream::FrameType ftype)
{

    if(m_flag.Started != true) {
        ASSERT(false);
        return false;
    }

    int leng = sizeof(StreamFrame) + STREAM_HEADER_SIZE + length ;
    std::shared_ptr<uint8_t> pMem(new uint8_t[leng],
            [](uint8_t* p){delete[] p;});

    if (pMem == nullptr) {
        ASSERT(false);
        return false;
    }


    StreamFrame *pFrameInfo = (StreamFrame*)pMem.get();

    pFrameInfo->flag = flag;
    pFrameInfo->frag = frag;
    pFrameInfo->dataLength = length;
    pFrameInfo->frame = (uint8_t*)pFrameInfo + sizeof(StreamFrame);
    pFrameInfo->data = &pFrameInfo->frame[STREAM_IDX_DATA0];

    //SEQ
    if (ftype == Frame_Command){
        if(STREAM_IS_NACK_FRM(flag) && m_isError) {
            pFrameInfo->seq = m_seqError;
        } else {
            pFrameInfo->seq = m_seqRemote;
        }
    } else {
        pFrameInfo->seq = m_seqLocal++;
    }

    if (length > 0) {
        for (uint16_t u16Idx = 0; u16Idx < length; u16Idx++) {
            pFrameInfo->data[u16Idx] = data[u16Idx];
        }
    }

    pFrameInfo->maxSend = STREAM_MAX_NUM_SEND;
    pFrameInfo->timeout = STREAM_TIMEOUT_MILLISECOND;

    return (RunSendFrame(pMem) == STREAM_ERR_SUCCESS);
}

/**
 * @brief Stream::StreamSendDataLater
 * @param flag
 * @param frag
 * @param data
 * @param length
 * @return
 */
bool Stream::StreamSendDataLater(uint8_t flag, uint8_t frag, uint8_t *data, uint32_t length)
{
    return StreamSendLater(flag, frag, data, length, Frame_Data);

}

/**
 * @brief Stream::StreamSendDataImmediate
 * @param flag
 * @param frag
 * @param data
 * @param length
 * @return
 */
bool Stream::StreamSendDataImmediate(uint8_t flag, uint8_t frag, uint8_t *data, uint32_t length)
{
    return StreamSendImmediate(flag, frag, data, length, Frame_Data);
}

void Stream::SetAesKey(std::string key)
{
    const char *ptr = key.data();
    LREP("SET KEY: \r\n");
    for(size_t i = 0; i < key.size(); i++) {
        aesKey[i] = ptr[i];
        printf("%02x ", aesKey[i]);
    }

    hasKey = true;
    m_crypt->SetKey(aesKey, 32);
}

/**
 * @brief Layer2::PopHead
 * @param usrList
 * @return
 */
std::shared_ptr<uint8_t> Stream::PopHead(std::list<std::shared_ptr<uint8_t>> &usrList) {

    std::shared_ptr<uint8_t> data = nullptr;
    if(usrList.size() > 0) {
        std::list<std::shared_ptr<uint8_t>>::iterator iter = usrList.begin();
        data = *iter;
        usrList.erase(iter);
    }

    return data;
}

/**
 * @brief Layer2::SearchAndPop
 * @param usrList
 * @param seq
 * @return
 */
std::shared_ptr<uint8_t> Stream::SearchAndPop(std::list<std::shared_ptr<uint8_t>> &usrList, uint16_t seq) {

    std::shared_ptr<uint8_t> data = nullptr;
    if(usrList.size() > 0) {
        //LREP("List before search: {}\r\n", usrList.size());
        std::list<std::shared_ptr<uint8_t>>::iterator iter = usrList.begin();
        while(iter != usrList.end()) {
            data = *iter;
            StreamFrame *pFramInfo = (StreamFrame*)(data.get());
            if(pFramInfo->seq == seq) { // Found
                //LREP("Search match seq: {}\r\n", seq);
                iter = usrList.erase(iter);
                //LREP("List after search and pop: {}\r\n", usrList.size());
                return data;
            }
            ++iter;
        }
        //ASSERT(false); // Not found
        return NULL;
    }
    //ASSERT(false); // List empty
    return NULL;
}

void Stream::Clb_UpdateTimer(uint32_t time, void *pParam)
{
    (void)time;
    Stream *pStream = static_cast<Stream *>(pParam);
    pStream->m_flag.WaitAckFrame = true;

    std::unique_lock<std::mutex> lck(pStream->m_trigger.mtx);
    //LREP(".");
    pStream->m_trigger.cv.notify_all();
    lck.unlock();
}


/**
 * @brief Stream::RecvTask
 * @return
 */
Stream::StreamAction Stream::RecvTask()
{
    StreamAction eRecvAction = Stream_Act_None;
    if(ProcessRecvData()) {        
        eRecvAction = OnRecvFrame();
    }
    return eRecvAction;
}

bool Stream::ProcessRecvData()
{    
    uint32_t    recvCount;
    uint8_t  	*pRecvFrm = frmRecv;
    uint8_t 	*pRecvData = &pRecvFrm[STREAM_IDX_DATA0];

    if (frmRecv == NULL) {
        ASSERT(false);
        if (MemAlloc() == false) {
            ASSERT(false);
            return false;
        }
    }

    *pRecvFrm = STREAM_CST_PREAMBLE;	//Start byte of frame

    while (GetRecvCount()) {
        /*-------------------------------
        * WAIT_HEADER - Waiting for header
        *--------------------------------*/
        if (m_recvCount == 0) {
            /*-------------------------*/
            // Start receiving if received at least a frame header
            if (GetRecvCount() < STREAM_HEADER_SIZE)
                break;

            /*-------------------------*/
            // Seek for a valid preamble
            if (RecvFifoPop() != STREAM_CST_PREAMBLE)
                continue;

            // Enter FIFO protection mode
            // This step is needed in case any collision occured
            RecvFifoEnProtect();

            recvCount = Recv(&pRecvFrm[1], STREAM_HEADER_SIZE - 1);

            if(recvCount != STREAM_HEADER_SIZE - 1)
                return false;

            /*-------------------------*/
            // Exit protected mode after received a correct header
            // NOTE: Assumes that collision can only occur in the period of header
            RecvFifoDisProtect();

            /*-------------------------*/
            // If needs recv DATA
            m_recvDlen = STREAM_GET_DLEN(pRecvFrm);

            if (m_recvDlen != 0) {
                m_recvCount = STREAM_HEADER_SIZE;
                continue;
            }
            /*-------------------------*/
            // Processes received frame
            return true;

        } // WAIT_HEADER
        /*----------------------------------------
        * WAIT_DATA - Waiting Data
        *----------------------------------------*/
        else {
            uint32_t nDataCount = m_recvCount - STREAM_HEADER_SIZE;
            uint8_t b;

            /*-------------------------*/
            // Store received data
            b = RecvFifoPop();

            if (nDataCount < STREAM_MAX_DLEN) {
                pRecvData[nDataCount] = b;
            }

            /*-------------------------*/
            m_recvCount++;
            nDataCount++;

            if (nDataCount < m_recvDlen) {
                continue;
            }
            /*-------------------------*/
            m_recvCount = 0;
            return true;
        } // WAIT_DATA
    } // while(GetRecvCount())
    return false;
}

Stream::StreamAction Stream::OnRecvFrame()
{
    uint8_t*          pRecvFrm = frmRecv;
    uint8_t*          pRecvData = &pRecvFrm[STREAM_IDX_DATA0];
    bool              bRecvFrame = false;
    uint32_t          dlen;
    uint8_t           flag;
    StreamAction      eRecvAction = Stream_Act_None;    

    flag = STREAM_GET_FLAG(pRecvFrm);
    dlen = STREAM_GET_DLEN(pRecvFrm);

    /*-------------------------*/
    // Invalid data length
    if (dlen > STREAM_MAX_DLEN) {
        eRecvAction = Stream_Recv_Nack;
        m_errCode = STREAM_ERR_REMOTE_DLEN;
        m_seqError = STREAM_GET_SEQ(pRecvFrm);
        LREP("Stream - invalid DLen: {}\r\n", dlen);

        return eRecvAction;
    }

    /*-------------------------*/
    if(STREAM_IS_CRCEN(flag)) {
        uint16_t          crcCalc, crcRecv;
        // Check CRC for data
        crcCalc = CheckCRC16(pRecvData, dlen);
        crcRecv = STREAM_GET_CRCD(pRecvFrm);
        if ((dlen != 0) && (crcRecv != crcCalc)) {
            // Wrong CRC -> Send NACK
            if (STREAM_IS_ACK_REQ(flag)) {
                eRecvAction = Stream_Req_Nack;
                m_seqError = STREAM_GET_SEQ(pRecvFrm);
                m_errCode = STREAM_ERR_REMOTE_CRCD;
            }
            LREP("crc recv: {}, crc calc: {} dlen {} \r\n", crcRecv, crcCalc, dlen);
            RecvFifoReset();
            return eRecvAction;
        }
    }

    if (STREAM_IS_DATA_FRM(flag)) { /* DATA FRAME */
        // Check Sequence number
        if (m_flag.CheckSeqNum) {
            m_seqRemote = STREAM_GET_SEQ(pRecvFrm);
        }        
        bRecvFrame = true;
    } else { /* COMMAND FRAME */

        if(STREAM_IS_ACK_FRM(flag)) {
            eRecvAction = Stream_Recv_Ack;
        } else if (STREAM_IS_NACK_FRM(flag)) {
            eRecvAction = Stream_Recv_Nack;
        } else {
            ASSERT(false);
        }
    }

    /*-------------------------*/
    // Send ACK if required
    if (STREAM_IS_ACK_REQ(flag))
    {
        eRecvAction = Stream_Req_Ack;
    }

    /*-------------------------*/
    // Callback

    if (bRecvFrame) {
        /*DATA.ind to higher layer*/
        FireEvent(Stream_Evt_Recv_Data);
    }

    return eRecvAction;
}

bool Stream::MemAlloc()
{
    StreamFrame *pFrameInfo;

    std::shared_ptr<uint8_t> pMem (new uint8_t[UDP_FRAME_SIZE], [](uint8_t* p){delete[] p;});

    m_memRecv = pMem;

    if(m_memRecv == nullptr) {
        frmRecv = nullptr;
        FireEvent(Stream_Evt_Error);
        return false;
    }

    pFrameInfo = (StreamFrame*)m_memRecv.get();
    frmRecv = (uint8_t*)pFrameInfo + sizeof(StreamFrame);
    pFrameInfo->frame = frmRecv;
    pFrameInfo->data = &frmRecv[STREAM_IDX_DATA0];
    return true;
}

void Stream::FireEvent(Stream::StreamEvent evt)
{
    switch (evt)
    {
        case Stream_Evt_Recv_Data:
            if (m_fRecvData) {
                StreamFrame *pFrameInfo = (StreamFrame *)m_memRecv.get();
                pFrameInfo->dataLength = STREAM_GET_DLEN(pFrameInfo->frame);
                m_fRecvData(m_memRecv, m_recvEvtParam);
                /*The previous buffer is eaten up and a new buffer is not assigned yet*/
                MemAlloc();
            } else {
                ASSERT(false);
            }
            break;

        case Stream_Evt_Send_Done:
            if (m_fSentData) {
                m_fSentData(m_memSend, m_sendEvtParam);
            } else {
                //ASSERT(false);
            }
            if (STREAM_IS_ACK_REQ(STREAM_GET_FLAG(frmSend))) {
                LREP("#");
                m_lsentDataMutex.lock();
                m_listSentData.push_back(m_memSend);
                m_lsentDataMutex.unlock();
            } else {
                if (m_memSend != nullptr) {
                    LREP(">");
                    m_memSend.reset();
                    m_memSend = nullptr;
                }
            }
            break;

        case Stream_Evt_Error:
            if (m_fError) {
                m_fError(m_memSend, m_errorEvtParam);
            } else {
                ASSERT(false);
            }
            if (m_memSend != nullptr) {
                LREP(">");
                m_memSend.reset();
                m_memSend = nullptr;
            }
            break;
        default:
            ASSERT(false);
            break;
    }
}


int Stream::SendDataToServerWithoutLen(uint8_t* data, int len)
{
    int event = m_stream->waitEvent(communication::Event_Writable, 100);

    if(event & communication::Event_Error){
        LREP("select failed\r\n");
        return -1;
    }

    if((event & communication::Event_Writable) == 0){
        LREP("event not writable\r\n");
        return -1;
    }

    return m_stream->writeData(data, len, m_streamDest);
}


void Stream::StreamProcessFrame(std::shared_ptr<uint8_t> pMem, void *user)
{
    (void)user;
    StreamFrame     *pFrameInfo;

    uint8_t flag;
    uint8_t frag;
    uint16_t currSeq;

    if(pMem == nullptr) {
        ASSERT(false);
        return;
    }
    /*-------------------------*/
    pFrameInfo = (StreamFrame *)pMem.get();

    currSeq = STREAM_GET_SEQ(pFrameInfo->frame);
    flag = STREAM_GET_FLAG(pFrameInfo->frame);
    frag = STREAM_GET_FRAG(pFrameInfo->frame);

    if(m_dataEvent != nullptr && hasKey) {
        if(!SearchWaitingSeq(currSeq)) { // If this sequence is new
            if(!STREAM_IS_FRAG_FRM(flag)) { // If is not fragment frame
                // If already received crypto message containt key
                if(m_packageOneFrame.Push(pFrameInfo->data, pFrameInfo->dataLength) < pFrameInfo->dataLength) {
                    LREP("ERROR FRAGMENT FRAME TOO LARGE, FIFO SIZE {}\r\n", m_packageOneFrame.GetCount());
                    m_packageOneFrame.Reset();
                    return;
                }

                uint32_t dlen = m_packageOneFrame.GetCount();
                uint8_t *data = new uint8_t[dlen];
                int32_t dataLeng = (int32_t)(dlen - 16);
                if(dataLeng <= 0) {
                    ASSERT(false);
                    return;
                }
                uint8_t *dataDecrypted = new uint8_t[dataLeng];
                memset(dataDecrypted, 0, dataLeng);
                RecvData(data, dlen);
                m_crypt->DataDecrypt(data, dlen, dataDecrypted);
                m_dataEvent(dataDecrypted[0], dataDecrypted, dataLeng);

                delete[] dataDecrypted;
                delete[] data;
                // Reset status and buffer
                m_packageOneFrame.Reset();
            } else { // This is a fragment frame sequence is new

                SplitedFrame   frm;
                frm.fragSeq = frag;
                frm.length = pFrameInfo->dataLength;
                frm.body = std::shared_ptr<uint8_t>(new uint8_t[pFrameInfo->dataLength], [](uint8_t* p){delete[] p;});
                AddWaitingSeqOld(currSeq, frm);
                LREP("wait size {}\n", m_waitingPackageList.size());

            }
        } else { // If this sequence is already on waiting queue
            if(!STREAM_IS_FRAG_FRM(flag)) { // If is end fragment frame)
                WaitingPackage listFrame = PopWaitingSeq(currSeq);
                FIFO fifo;
                fifo.Init(STREAM_MAX_BYTE_IN_PACKAGE);
                if(SortAndGetDataOnList(fifo, listFrame.splitedData)) {
                    uint32_t dlen  = fifo.GetCount();
                    uint8_t *data = new uint8_t[dlen];
                    int32_t dataLeng = (int32_t)(dlen - 16);
                    if(dataLeng <= 0) { ASSERT(false); return; }
                    uint8_t *dataDecrypted = new uint8_t[dataLeng];
                    memset(dataDecrypted, 0, dataLeng);
                    fifo.Recv(data, dlen);
                    m_crypt->DataDecrypt(data, dlen, dataDecrypted);
                    m_dataEvent(dataDecrypted[0], dataDecrypted, dataLeng);
                    delete[] dataDecrypted;
                    delete[] data;
                }
                fifo.DeInit();
                listFrame.splitedData.clear();

            } else { // If is new fragment frame with old sequence
                SplitedFrame   frm;
                frm.fragSeq = frag;
                frm.length = pFrameInfo->dataLength;
                frm.body = std::shared_ptr<uint8_t>(new uint8_t[pFrameInfo->dataLength], [](uint8_t* p){delete[] p;});
                AddWaitingSeqNew(currSeq, frm);
                LREP("wait size {}\n", m_waitingPackageList.size());
            }
        }
    }
}





















