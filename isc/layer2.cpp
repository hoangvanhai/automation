#include "layer2.h"
#include "timer.h"

namespace communication {
namespace isc {
Layer2::Layer2() {
    m_L1 = nullptr;
    m_Timer = nullptr;
    m_recvCount = 0;
    m_recvDlen = 0;
    m_seqRemote = 0xFF;
    m_seqError = 0x00;
    m_isError = false;
    m_seqLocal = 0;
    m_seqCMDfrm = 0;
    m_errCode = 0;
    m_memRecv = nullptr;
    m_memSend = nullptr;
    frmRecv = nullptr;
    frmSend = nullptr; 
    L1SendTimeout = 0;
    m_fRecvData = nullptr;
    m_fSentData = nullptr;
    m_fError = nullptr;
    m_recvEvtParam = nullptr;
    m_sendEvtParam = nullptr;
    m_errorEvtParam = nullptr;
    m_Cv = nullptr;
    hL1TrackingTimer = nullptr;
    m_flag.bL2CheckSeqNum = false;
    m_flag.bL2L1Sending = false;
    m_flag.bL2Started = false;
    m_flag.bL2WaitingL1Send = false;
    m_flag.bL2Sending = false;
    m_portname = DEFAULT_PORT_NAME;
    m_baudrate = DEFAULT_BAUDRATE;
    m_myId = 0x00;
    m_dstId = 0x00;
    m_fMacError = nullptr;
    m_fMacRevData = nullptr;
    m_fMacSentData = nullptr;
    m_macErrorParam = NULL;
    m_macRecvParam = NULL;
    m_macSentParam = NULL;
    m_ownerThreadTerm = true;
    m_listSendingData.clear();
    m_listSendingCmd.clear();
    m_listSentData.clear();
    m_status = MAC_EVT_DISCONNECTED;
}

/**
 * @brief Layer2::Start : Init comport and some frame manager service
 * @param portname
 * @param baudrate
 * @param sem
 * @param myId
 * @param dstId
 * @return
 */
bool Layer2::Start(std::string portname, int baudrate, void *sem, uint8_t myId) {

    if(sem == NULL) return false;

    if(portname == "" && (baudrate > 5000000 || baudrate < 0)) {
        m_portname = DEFAULT_PORT_NAME;
        m_baudrate = DEFAULT_BAUDRATE;
    }else {
        m_portname = portname;
        m_baudrate = baudrate;
    }

    m_L1 = std::make_shared<Layer1>(m_portname, m_baudrate);
    if(m_L1 == nullptr) {
        ASSERT(false);
        return false;
    }

    // Register callback
    m_L1->RegisterCallbackEvent(Layer1::TRANSL1_EVT_RECV_BYTE, Clb_L1RecvData, this);
    m_L1->RegisterCallbackEvent(Layer1::TRANSL1_EVT_SEND_DONE, Clb_L1SendDone, this);

    // Setting
    m_flag.bL2CheckSeqNum = true;
    m_myId = myId;
    //m_dstId = dstId;

    // Get sync
    m_Cv = (SCV*)sem;

    if(MemAlloc() == false) {
        return false;
    }

    // Start L1
    if(m_L1->Start() != true) {
        return false;
    }

    /* INIT TIMER OBJECT */
    m_Timer = std::make_shared<Timer>(1000);
    //m_Timer->StartTimerObject();

    InitL1TimeOutTimer();

    m_flag.bL2Started = true;
    return true;
}

/**
 * @brief Layer2::RecvTask
 * @return
 */
Layer2::EL2RecvAction Layer2::RecvTask() {

    EL2RecvAction eRecvAction = ISCL2_ACT_NO;
    if(ProcessRecvData()) {

        eRecvAction = OnRecvFrame();
    }
    return eRecvAction;
}
/**
 * @brief Layer2::SendTask
 * @return
 */
bool Layer2::SendTask() {
    if(m_flag.bL2Sending) {
        RunSendFrame();
        return true;
    }
    return false;
}


/**
 * @brief Layer2::Send
 * @param pMem
 * @return
 */
ETransErrorCode Layer2::Send(std::shared_ptr<uint8_t> pMem) {
    SFrameInfo 		*pFrameInfo;
    uint8_t 		*pSendFrm;
    uint8_t 		*pData;
    uint32_t		dlen;
    ETransErrorCode u8ErrorCode;

    /*-------------------------*/

    if(pMem == NULL) {
        ASSERT(false);
        return (ETransErrorCode)TRANS_ERR_MEM;
    }
    /*-------------------------*/
    // Check valid and parameters
    /*-------------------------*/
    if (m_flag.bL2Started != true)
    {
        u8ErrorCode = TRANS_ERR_NOT_STARTED;
        ASSERT(false);
        return u8ErrorCode;
    }

    if (m_flag.bL2Sending)
    {
        u8ErrorCode = TRANS_ERR_BUSY;
        ASSERT(false);
        return u8ErrorCode;
    }

    /*-------------------------*/
    pFrameInfo = (SFrameInfo *)pMem.get();
    //pFrameInfo = (SFrameInfo *)pMem;

    pFrameInfo->u8NumSend--;

    m_memSend = pMem; /*save this for callback function*/

    frmSend = (uint8_t*)pFrameInfo + sizeof(SFrameInfo);
    pSendFrm = frmSend;
    pData = &frmSend[IDX_SFRM_DATA0];

    /*---------------------------*/
    // Building the sending frame
    /*---------------------------*/
    pSendFrm[IDX_SFRM_PREAM] = CST_PREAMBLE;
    pSendFrm[IDX_SFRM_SRCADR] = m_myId;
    pSendFrm[IDX_SFRM_DSTADR] = m_dstId;
    pSendFrm[IDX_SFRM_SEQNUM] = pFrameInfo->u8Seq;    
    pSendFrm[IDX_SFRM_CTRL] = pFrameInfo->u8Ctrl;

    SFRAME_SET_DLEN(pSendFrm, (uint8_t)pFrameInfo->u16DLen);

    dlen = SFRAME_GET_DLEN(pSendFrm);

    ASSERT(frmSend[IDX_SFRM_SRCADR] != frmSend[IDX_SFRM_DSTADR]);

    if (dlen > SFRM_MAX_DLEN) {
        u8ErrorCode = TRANS_ERR_PARAM;
        ASSERT(false);
        LREP("dlen: {},SFRM_MAX_DLEN = {}", dlen, SFRM_MAX_DLEN);
        return u8ErrorCode;
    }

    //CRCD
    if (dlen != 0) {
        pSendFrm[IDX_SFRM_CRCD] = CalCRC8(pData, dlen);
    } else {
        pSendFrm[IDX_SFRM_CRCD] = 0;
    }
    //CRCH
    pSendFrm[IDX_SFRM_CRCH] = CalCRC8(&pSendFrm[IDX_SFRM_SRCADR], SFRM_HDR_SIZE - 2);

    /*---------------------------*/
    // Queue the frame to send
    /*---------------------------*/
    m_flag.bL2Sending = true;
    m_flag.bL2WaitingL1Send = false;
    m_flag.bL2L1Sending = false;

    u8ErrorCode = TRANS_ERR_SUCCESS;
    return u8ErrorCode;
}
/**
 * @brief Layer2::RegisterClbEvent
 * @param event
 * @param pFunction
 * @param pClbParam
 */
void Layer2::RegisterClbEvent(Layer2::EL2Event event,
                              std::function<void (Layer2::EL2Event, std::shared_ptr<uint8_t> , void *)> pFunction,
                              void *pClbParam) {

    switch (event)
    {
    case TRANSL2_EVT_NONE:
        break;
    case TRANSL2_EVT_RECV_DATA:
        m_fRecvData = pFunction;
        m_recvEvtParam = pClbParam;
        break;
    case TRANSL2_EVT_SEND_DONE:
        m_fSentData = pFunction;
        m_sendEvtParam = pClbParam;
        break;
    case TRANSL2_EVT_ERROR:
        m_fError = pFunction;
        m_errorEvtParam = pClbParam;
        break;
    default:
        ASSERT(false);
        break;
    }
}

/**
 * @brief Layer2::MemAlloc
 * @return
 */
bool Layer2::MemAlloc()
{
    SFrameInfo *pFrameInfo;

    std::shared_ptr<uint8_t> pMem (new uint8_t[LARGE_MEM_SIZE], [](uint8_t* p){delete[] p;});

    m_memRecv = pMem;

    if(m_memRecv == NULL) {
        frmRecv = NULL;
        FireEvent(TRANSL2_EVT_ERROR);
        return false;
    }

    pFrameInfo = (SFrameInfo*)m_memRecv.get();
    frmRecv = (uint8_t*)pFrameInfo + sizeof(SFrameInfo);
    pFrameInfo->pFrame = frmRecv;
    pFrameInfo->pu8Data = &frmRecv[IDX_SFRM_DATA0];
    return true;
}

/**
 * @brief Layer2::ProcessRecvData
 * @return
 */
bool Layer2::ProcessRecvData()
{
    uint8_t 	bCRCH;
    uint32_t    recvCount;
    uint8_t  	*pRecvFrm = frmRecv;
    uint8_t 	*pRecvData = &pRecvFrm[IDX_SFRM_DATA0];


    if (frmRecv == NULL)
    {
        ASSERT(false);

        if (MemAlloc() == false)
        {
            ASSERT(false);
            return false;
        }
    }

    *pRecvFrm = CST_PREAMBLE;	//Start byte of frame

    while (m_L1->GetRecvCount())
    {

        /*-------------------------------
        * WAIT_HEADER - Waiting for header
        *--------------------------------*/
        if (m_recvCount == 0)
        {
            /*-------------------------*/
            // Start receiving if received at least a frame header
            if (m_L1->GetRecvCount() < SFRM_HDR_SIZE)
                break;

            /*-------------------------*/
            // Seek for a valid preamble
            if (m_L1->RecvFifoPop() != CST_PREAMBLE)
                continue;

            // Enter FIFO protection mode
            // This step is needed in case any collision occured
            m_L1->RecvFifoEnProtect();

            /*-------------------------*/
            // Receiving header's fields
            //            u16Recv = TransL1_Recv(&pRecvFrm[1], SFRM_HDR_SIZE-1);


            recvCount = m_L1->Recv(&pRecvFrm[1], SFRM_HDR_SIZE - 1);

            if(recvCount != SFRM_HDR_SIZE - 1)
                return false;

            bCRCH = CalCRC8(&pRecvFrm[1], SFRM_HDR_SIZE - 2);

            /*-------------------------*/
            // Checking CRC for header
            if (bCRCH != pRecvFrm[IDX_SFRM_CRCH])
            {
                // If CRC for header is error,
                // ... comes back and search again.
                LREP("**CRCH ERROR**\t");
                m_L1->RecvFifoRewindHead();
                m_L1->RecvFifoDisProtect();
                continue;
            }

            /*-------------------------*/
            // Exit protected mode after received a correct header
            // NOTE: Assumes that collision can only occur in the period of header
            m_L1->RecvFifoDisProtect();

            /*-------------------------*/
            // If needs recv DATA
            m_recvDlen = SFRAME_GET_DLEN(pRecvFrm);

            if (m_recvDlen != 0)
            {
                m_recvCount = SFRM_HDR_SIZE;
                continue;
            }


            /*-------------------------*/
            // Processes received frame
            return true;

        } // WAIT_HEADER


        /*----------------------------------------
        * WAIT_DATA - Waiting Data
        *----------------------------------------*/
        else
        {
            uint32_t nDataCount = m_recvCount - SFRM_HDR_SIZE;
            uint8_t b;

            /*-------------------------*/
            // Store received data
            b = m_L1->RecvFifoPop();

            if (nDataCount < SFRM_MAX_DLEN) {
                pRecvData[nDataCount] = b;
            }

            /*-------------------------*/
            m_recvCount++;
            nDataCount++;

            if (nDataCount < m_recvDlen)
            {
                continue;
            }

            /*-------------------------*/
            m_recvCount = 0;
            return true;

        } // WAIT_DATA
    } // while(1)
    return false;
}

/**
 * @brief Layer2::OnRecvFrame
 * @return
 */
Layer2::EL2RecvAction Layer2::OnRecvFrame()
{
    uint8_t*          pRecvFrm = frmRecv;
    uint8_t*          pRecvData = &pRecvFrm[IDX_SFRM_DATA0];
    bool              bRecvFrame = false;
    uint32_t          dlen;
    EL2RecvAction     eRecvAction = ISCL2_ACT_NO;


    dlen = SFRAME_GET_DLEN(pRecvFrm);
    //LREPS("\r\nDLen = %d",(uint32)u16DLen);
    /*-------------------------*/
    // If the frame is NOT for this node
    if (pRecvFrm[IDX_SFRM_DSTADR] != m_myId && pRecvFrm[IDX_SFRM_DSTADR] != ADDR_BROADCAST) {
        LREP("L2 Recv ID {hex} but myID: {hex}\r\n", (int)pRecvFrm[IDX_SFRM_DSTADR], (int)m_myId);
        return eRecvAction;
    }

    /*-------------------------*/
    // Invalid data length
    if ((dlen > SFRM_MAX_DLEN) && (pRecvFrm[IDX_SFRM_DSTADR] != ADDR_BROADCAST)) {
        eRecvAction = ISCL2_REQ_NACK;
        m_errCode = TRANS_ERR_REMOTE_DLEN;
        m_seqError = pRecvFrm[IDX_SFRM_SEQNUM];
        LREP("L2 - invalid DLen: {}\r\n", dlen);

        return eRecvAction;
    }

    /*-------------------------*/
    // Check CRC for data

    if ((dlen != 0) && (pRecvFrm[IDX_SFRM_CRCD] != CalCRC8(pRecvData, dlen))) {
        // Wrong CRC -> Send NACK
        if (IS_ACK_REQ(pRecvFrm[IDX_SFRM_CTRL]) && pRecvFrm[IDX_SFRM_DSTADR] != ADDR_BROADCAST) {
            eRecvAction = ISCL2_REQ_NACK;
            m_seqError = pRecvFrm[IDX_SFRM_SEQNUM];
            m_errCode = TRANS_ERR_REMOTE_CRCD;
        }

        m_L1->RecvFifoReset();
        LREP("L2 - wrong CRCD -> Reset FIFIO\r\n");

        return eRecvAction;
    }

    if (IS_DATA_FRM(pRecvFrm[IDX_SFRM_CTRL])) { /* DATA FRAME */
        // Check Sequence number
        if (!m_flag.bL2CheckSeqNum || (pRecvFrm[IDX_SFRM_SEQNUM] != m_seqRemote)) {
            bRecvFrame = true;            
            m_seqRemote = pRecvFrm[IDX_SFRM_SEQNUM];
        } else {
            LREP("L2 - same SEQ\r\n");
            m_L1->RecvFifoReset();
        }
    } else { /* COMMAND FRAME */
        switch (GET_FRM_TYPE(pRecvFrm[IDX_SFRM_CTRL]))
        {
        case CMD_NONE:
            break;
        case CMD_ACK:
            eRecvAction = ISCL2_RCV_ACK;
            m_seqCMDfrm = pRecvFrm[IDX_SFRM_SEQNUM];
            break;
        case CMD_NACK:
            eRecvAction = ISCL2_RCV_NACK;
            m_seqCMDfrm = pRecvFrm[IDX_SFRM_SEQNUM];
            break;
        default:
            ASSERT(false);
            break;
        }
    }

    /*-------------------------*/
    // Send ACK if required
    if (IS_ACK_REQ(pRecvFrm[IDX_SFRM_CTRL]) &&
            (pRecvFrm[IDX_SFRM_DSTADR] != ADDR_BROADCAST))
    {
        eRecvAction = ISCL2_REQ_ACK;
    }

    /*-------------------------*/
    // Callback

    if (bRecvFrame) {
        /*DATA.ind to higher layer*/
        FireEvent(TRANSL2_EVT_RECV_DATA);
    }

    return eRecvAction;
}

/**
 * @brief Layer2::IsSendReady
 * @return
 */
bool Layer2::IsSendReady()
{
    return (m_flag.bL2Started == true  && m_flag.bL2Sending == false);
}

/**
 * @brief Layer2::RunSendFrame
 * @return
 */
bool Layer2::RunSendFrame()
{
    uint8_t*   pSendFrm = frmSend;
    uint32_t   sendSize = SFRAME_SIZE(pSendFrm);
    ETransErrorCode      eErrorCode;

    /*-------------------------*/
    /* Check if L1 is sending  */
    /*-------------------------*/
    if (m_flag.bL2WaitingL1Send)
    {
        if (m_flag.bL2L1Sending)
        {
            return false;
        }
        else
        {
            /*L1 send done*/
            m_flag.bL2Sending = false;
            m_flag.bL2WaitingL1Send = false;

            FireEvent(TRANSL2_EVT_SEND_DONE);
            return true;
        }
    }
    /*-------------------------
    * Transfer buffer to L1 to send
    *-------------------------*/
    if (m_L1->IsSendReady() == true) {
        m_flag.bL2L1Sending = true;
        m_flag.bL2WaitingL1Send = true;

        eErrorCode = (ETransErrorCode)m_L1->Send(pSendFrm, sendSize);

        if (eErrorCode == TRANS_ERR_SUCCESS) {
            m_l1TimeTrackValue = 200L;
            /*
            *Start TimeOut Timer to monitor L1 Sending
            */
            //StartL1TimeOutTimer(m_l1TimeTrackValue);

        } else { /*Error - L1 is busy or error*/
            m_flag.bL2Sending = false;
            LREP("L2 Fire Event L1 Send Failure\r\n");
            FireEvent(TRANSL2_EVT_ERROR);
            return false;
        }
    }

    return true;
}

/**
 * @brief Layer2::FireEvent
 * @param event
 */
void Layer2::FireEvent(Layer2::EL2Event event)
{
    switch (event)
    {
    case TRANSL2_EVT_RECV_DATA:
        ASSERT(m_fRecvData != NULL);
        if (m_fRecvData) {

            SFrameInfo *pFrameInfo = (SFrameInfo *)m_memRecv.get();
            pFrameInfo->u16DLen = SFRAME_GET_DLEN(pFrameInfo->pFrame);
            pFrameInfo->u8Ctrl = pFrameInfo->pFrame[IDX_SFRM_CTRL];

            m_fRecvData(TRANSL2_EVT_RECV_DATA, m_memRecv, m_recvEvtParam);

            /*The previous buffer is eaten up and a new buffer is not assigned yet*/            
            MemAlloc();
        }
        break;

    case TRANSL2_EVT_SEND_DONE:
        ASSERT(m_fSentData != NULL);
        if (m_fSentData) {
            m_fSentData(TRANSL2_EVT_SEND_DONE, m_memSend, m_sendEvtParam);
        }
        break;

    case TRANSL2_EVT_ERROR:
        ASSERT(m_fError != NULL);
        if (m_fError) {
            m_fError(TRANSL2_EVT_ERROR, m_memSend, m_errorEvtParam);
        }
        break;
    default:
        ASSERT(false);
        break;
    }
}

/**
 * @brief Layer2::InitL1TimeOutTimer
 */
void Layer2::InitL1TimeOutTimer() {
    hL1TrackingTimer = m_Timer->Create(Clb_L1SendTimeOut, this);
}

/**
 * @brief Layer2::StartL1TimeOutTimer
 * @param time
 */
void Layer2::StartL1TimeOutTimer(uint32_t time) {
    m_Timer->StartAt(hL1TrackingTimer, time);
}

/**
 * @brief Layer2::StopL1TimeOutTimer
 */
void Layer2::StopL1TimeOutTimer() {
    m_Timer->Stop(hL1TrackingTimer);
}

/**
 * @brief Layer2::Clb_L1SendDone
 * @param pParam
 */
void Layer2::Clb_L1SendDone(void *pParam)
{
    if(pParam == NULL) {
        ASSERT(false);
        return;
    }
    Layer2 *pInst = static_cast<Layer2*>(pParam);
    pInst->m_flag.bL2L1Sending = false;
    /*Stop L1 TimeOut Timer*/
    pInst->StopL1TimeOutTimer();

    /*Signal to run Trans thread*/
    if(pInst->m_Cv != NULL) {
        //std::unique_lock<std::mutex> lck(pISCLayer2->hCV->mtx);
        pInst->m_Cv->cv.notify_one();
        //lck.unlock();
    } else {
        ASSERT(false);
    }

}

/**
 * @brief Layer2::Clb_L1RecvData
 * @param pParam
 */
void Layer2::Clb_L1RecvData(void *pParam) {

    if(pParam == NULL) {
        ASSERT(false);
        return;
    }

    Layer2 *pInst = static_cast<Layer2*>(pParam);

    if(pInst->m_Cv != NULL) {
        //std::unique_lock<std::mutex> lck(pISCLayer2->hCV->mtx);
        pInst->m_Cv->cv.notify_one();
        //lck.unlock();
    } else {
        ASSERT(false);
    }
}




/**
 * @brief Layer2::Clb_L1SendTimeOut
 * @param time
 * @param pParam
 */
void Layer2::Clb_L1SendTimeOut(uint32_t time, void *pParam)
{
    (void)time;

    if(pParam == NULL)
    {
        ASSERT(false);
        return;
    }

    Layer2 *pInst = static_cast<Layer2*>(pParam);

    uint8_t*   pSendFrm = pInst->frmSend;

    ASSERT(false);

    pInst->StopL1TimeOutTimer();

    if (pInst->m_flag.bL2L1Sending) {
        pInst->m_flag.bL2L1Sending = false;
        pInst->m_flag.bL2WaitingL1Send = false;
        pInst->m_flag.bL2Sending = false;
        //pInst->u8ErrorCode = TRANS_ERR_L1_TIMEOUT;
        /*Layer 1 timeout*/
        if (IS_DATA_FRM(pSendFrm[IDX_SFRM_CTRL])) {
            /* DATA.con to higher layer
            * Sended frame is Data frame (Data.req) from higher layer
            */
            LREP("L1 Timeout Event\r\n");
            pInst->FireEvent(TRANSL2_EVT_ERROR);
        } else {
            /*Sended frame is Command frame -> free buffer internally*/
            pInst->FreeMemory(pInst->m_memSend);
            //Do not need to indicate to higher layer
            ASSERT(false);
        }
    } else {
        ASSERT(false);
    }
}


/**
 * @brief Layer2::FreeMemory
 * @param pMem
 */
void Layer2::FreeMemory(std::shared_ptr<uint8_t> pMem) {

    if(pMem != NULL) {
        pMem.reset();
        pMem = NULL;
    }else{
        ASSERT(false);
    }
}

/**
 * @brief Layer2::Mac_Send
 * @param dest
 * @param ctrl
 * @param data
 * @param dlen
 * @param type
 * @return
 */
bool  Layer2::Mac_sendLater(uint8_t dest, uint8_t ctrl, uint8_t *data, uint8_t dlen, EPackageType type) {

    if(m_flag.bMacStarted != true) {
        ASSERT(false);
        return false;
    }

    m_dstId = dest;

    std::shared_ptr<uint8_t> pMem(new uint8_t[CALCULATE_MEM_SIZE(dlen + SFRM_HDR_SIZE)], [](uint8_t* p){delete[] p;});

    if (pMem == NULL) {
        ASSERT(false);
        return false;
    }

    SFrameInfo *pFrameInfo = (SFrameInfo*)pMem.get();
    //
    pFrameInfo->u8Ctrl = ctrl;
    pFrameInfo->u16DLen = dlen;
    pFrameInfo->pFrame = (uint8_t*)pFrameInfo + sizeof(SFrameInfo);    
    pFrameInfo->pu8Data = &pFrameInfo->pFrame[IDX_SFRM_DATA0];

    //SEQ
    if (type == E_CMD_FRM){
        if(ctrl == CMD_NACK && m_isError) {
            pFrameInfo->u8Seq = m_seqError;
        } else {
            pFrameInfo->u8Seq = m_seqRemote;
        }
    } else {
        pFrameInfo->u8Seq = m_seqLocal++;
    }

    if (dlen > 0) {
        for (uint16_t u16Idx = 0; u16Idx < dlen; u16Idx++) {
            pFrameInfo->pu8Data[u16Idx] = data[u16Idx];
        }
    }

    pFrameInfo->u8NumSend = ISCL3_MAX_NUM_SEND;
    pFrameInfo->i16TimeOut = ISCL3_TIMEOUT_TICK;


    switch (ctrl & 0x3F)
    {
        case CMD_ACK:
        case CMD_NACK:
            m_listSendingCmd.push_back(pMem);
            break;
        default:
            m_lsendingDataMutex.lock();
            m_listSendingData.push_back(pMem);
            m_lsendingDataMutex.unlock();
            break;
    }

    m_hSync.cv.notify_one();

    return true;
}

bool Layer2::Mac_sendImmediate(uint8_t dest, uint8_t ctrl, uint8_t *data, uint8_t dlen, Layer2::EPackageType type)
{
    if(m_flag.bMacStarted != true) {
        ASSERT(false);
        return false;
    }

    m_dstId = dest;

    std::shared_ptr<uint8_t> pMem(new uint8_t[CALCULATE_MEM_SIZE(dlen + SFRM_HDR_SIZE)], [](uint8_t* p){delete[] p;});

    if (pMem == NULL) {
        ASSERT(false);
        return false;
    }


    SFrameInfo *pFrameInfo = (SFrameInfo*)pMem.get();
    //
    pFrameInfo->u8Ctrl = ctrl;
    pFrameInfo->u16DLen = dlen;
    pFrameInfo->pFrame = (uint8_t*)pFrameInfo + sizeof(SFrameInfo);
    pFrameInfo->pu8Data = &pFrameInfo->pFrame[IDX_SFRM_DATA0];

    //SEQ
    if (type == E_CMD_FRM){
        if(ctrl == CMD_NACK && m_isError) {
            pFrameInfo->u8Seq = m_seqError;
        } else {
            pFrameInfo->u8Seq = m_seqRemote;
        }
    } else {
        pFrameInfo->u8Seq = m_seqLocal++;
    }

    if (dlen > 0) {
        for (uint16_t u16Idx = 0; u16Idx < dlen; u16Idx++) {
            pFrameInfo->pu8Data[u16Idx] = data[u16Idx];
        }
    }

    pFrameInfo->u8NumSend = ISCL3_MAX_NUM_SEND;
    pFrameInfo->i16TimeOut = ISCL3_TIMEOUT_TICK;

    if (Send(pMem) != TRANS_ERR_SUCCESS)
        ASSERT(false);

    return SendTask();
}

/**
 * @brief Layer2::Mac_Send
 * @param ctrl
 * @param data
 * @param dlen
 * @return
 */
bool Layer2::Mac_SendDataLater(uint8_t dest, uint8_t ctrl, uint8_t *data, uint8_t dlen) {
    return Mac_sendLater(dest, ctrl, data, dlen, E_DATA_FRM);
}

bool Layer2::Mac_SendDataImmediate(uint8_t dest, uint8_t ctrl, uint8_t *data, uint8_t dlen)
{
    return Mac_sendImmediate(dest, ctrl, data, dlen, E_DATA_FRM);
}

//bool Layer2::Send(uint8_t *data, uint8_t dlen)
//{
//    LREP("Send data len: {}\r\n", dlen);
//    uint8_t sendData[100];
//    memcpy(&sendData[3], data, dlen);
//    sendData[0] = '!';
//    sendData[1] = 0x01;
//    sendData[2] = 100;
//    sendData[dlen + 3] = '#';
//    return Mac_SendDataLater(m_dstId, FRM_DATA, sendData, dlen + 4);
//}

/**
 * @brief Layer2::Clb_UpdateTimer
 * @param time
 * @param pParam
 */
void Layer2::Clb_UpdateTimer(uint32_t time, void *pParam) {
    (void)time;
    Layer2 *pMac = static_cast<Layer2 *>(pParam);
    pMac->m_flag.bUpdateWaitingACKFrameState = true;
    std::unique_lock<std::mutex> lck(pMac->m_hSync.mtx);
    //LREP(".");
    pMac->m_hSync.cv.notify_all();
    lck.unlock();
}


/**
 * @brief Layer2::Mac_Start
 * @param portname
 * @param baudrate
 * @param myId
 * @param dstId
 * @return
 */
bool Layer2::Mac_Start(std::string portname, int baudrate, uint8_t myId)
{
    RegisterClbEvent(TRANSL2_EVT_RECV_DATA,   Mac_ClbRecvData, this);
    RegisterClbEvent(TRANSL2_EVT_SEND_DONE,   Mac_ClbSentData, this);
    RegisterClbEvent(TRANSL2_EVT_ERROR,       Mac_ClbErr,    this);

    if(Start(portname, baudrate, &m_hSync, myId) == false) {
        return false;
    }

    Mac_StartThread();
    m_flag.bMacStarted = true;

    m_hUpdateTimer =  m_Timer->Create(Clb_UpdateTimer, this);
    m_Timer->SetRate(m_hUpdateTimer, ISCL3_UPDATE_TIMER_RATE_MS);
    m_Timer->Start(m_hUpdateTimer);
    return true;
}

/**
 * @brief Layer2::Mac_Stop
 */
void Layer2::Mac_Stop() {

    //LREP("Stop update timer\r\n");
    m_Timer->Stop(m_hUpdateTimer);
    //LREP("Delete update timer\r\n");
    m_Timer->Delete(m_hUpdateTimer);
    //LREP("Stop platform timer\r\n")
    //m_Timer->StopTimerObject();
    //LREP("Deleted timer object\r\n");
    m_Timer.reset();
    m_Timer = nullptr;

    //LREP("Start terminate thread\r\n");
    m_ownerThreadTerm = true;

    if(m_ownerThread.joinable()){
        m_ownerThread.join();
    }
    LREP("Let L1 destroy\r\n");
    m_L1->Stop();
    m_L1.reset();
    m_flag.bMacStarted = false;
}

/**
 * @brief Layer2::Mac_SetMyId
 * @param myId
 */

void Layer2::Mac_SetMyId(uint8_t myId) {
    m_myId = myId;
}

/**
 * @brief Layer2::Mac_SetDstId
 * @param dstId
 */
void Layer2::Mac_SetDstId(uint8_t dstId) {
    m_dstId = dstId;
}

/**
 * @brief Layer2::Mac_SendTask
 */
void Layer2::Mac_SendTask() {
    /*------------------------------------------------------------------------*/
    //Update State of waiting frames
    if (m_flag.bUpdateWaitingACKFrameState == true)
    {
        m_flag.bUpdateWaitingACKFrameState = false;
        Mac_CheckTimeOutOfSentFrame();
    }

    if (IsSendReady() == true)
    {
        std::shared_ptr<uint8_t> pMem;
        /*First, Send ACK/NACK message*/
        if (m_listSendingCmd.size() > 0) {

            pMem = Mac_PopHead(m_listSendingCmd);
        } else if (m_listSendingData.size() > 0) {
            /*Secondly, Send UI Control/Status message*/
            m_lsendingDataMutex.lock();
            pMem = Mac_PopHead(m_listSendingData);
            m_lsendingDataMutex.unlock();
        }

        if (pMem != NULL) {
            if (Send(pMem) != TRANS_ERR_SUCCESS) {
                ASSERT(false);
            }
        }
    }

    /*-----------------------------------------------------------------------
    * Run UTPL2 to send frame
    *-----------------------------------------------------------------------*/
    SendTask();
}

/**
 * @brief Layer2::Mac_RecvTask
 */
void Layer2::Mac_RecvTask() {
    std::shared_ptr<uint8_t> pMem;
    size_t          listSize = 0;
    SFrameInfo      *pFrameInfo = NULL;
    /*------------------------------------------------------------------------*/
    /* Run RecvTask of Layer 2 to process receiving frame */
    EL2RecvAction eL2Action = RecvTask();

    switch (eL2Action)
    {
    case ISCL2_ACT_NO:
        break;
    case ISCL2_RCV_ACK:
        //LREP("MAC_RCV_ACK\r\n");
        listSize = m_listSentData.size();
        if(listSize == 0) {
            ASSERT(false);
            return;
        }
        m_lsentDataMutex.lock();
        pMem = Mac_SearchAndPop(m_listSentData, m_seqCMDfrm);
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
    case ISCL2_RCV_NACK:
        LREP("RCV_NACK {}\r\n", (int)m_seqCMDfrm);
        listSize = m_listSentData.size();
        if(listSize == 0) {
            ASSERT(false);
            return;
        }
        m_lsentDataMutex.lock();
        pMem = Mac_SearchAndPop(m_listSentData, m_seqCMDfrm);
        m_lsentDataMutex.unlock();
        if(pMem == NULL) {
            ASSERT(false);
            return;
        }
        pFrameInfo = (SFrameInfo*)pMem.get();
        pFrameInfo->i16TimeOut = ISCL3_TIMEOUT_TICK;
        LREP("-> Resend frm: {}\r\n", (int)m_seqCMDfrm);
        m_listSendingData.push_back(pMem);

        break;

    case ISCL2_REQ_ACK:
        //L2 get a data frame requiring ACK		->	Add CMD_ACK frame to queue
        Mac_sendImmediate(m_dstId, CMD_ACK, NULL, 0, E_CMD_FRM);
        break;

    case ISCL2_REQ_NACK:
        m_isError = true;
        LREP("SEND NACK SEQ: {}\r\n", (int)m_seqError);
        //L2 get a frame but DLEN or CRCD is wrong	->	Add CMD_NACK frame to queue
        Mac_sendImmediate(m_dstId, CMD_NACK, NULL, 0, E_CMD_FRM);
        m_isError = false;
        break;

    default:
        ASSERT(false);
        break;
    }
    /*------------------------------------------------------------------------*/
}

/**
 * @brief Layer2::Mac_PopHead
 * @param usrList
 * @return
 */
std::shared_ptr<uint8_t> Layer2::Mac_PopHead(std::list<std::shared_ptr<uint8_t>> &usrList) {

    std::shared_ptr<uint8_t> data;
    if(usrList.size() > 0) {
        std::list<std::shared_ptr<uint8_t>>::iterator iter = usrList.begin();
        data = *iter;
        usrList.erase(iter);
    }

    return data;
}

/**
 * @brief Layer2::Mac_SearchAndPop
 * @param usrList
 * @param seq
 * @return
 */
std::shared_ptr<uint8_t> Layer2::Mac_SearchAndPop(std::list<std::shared_ptr<uint8_t>> &usrList, uint8_t seq) {

    std::shared_ptr<uint8_t> data;
    if(usrList.size() > 0) {
        //LREP("List before search: {}\r\n", usrList.size());
        std::list<std::shared_ptr<uint8_t>>::iterator iter = usrList.begin();
        while(iter != usrList.end()) {
            data = *iter;
            SFrameInfo *pFramInfo = (SFrameInfo*)(data.get());
            if(pFramInfo->u8Seq == seq) { // Found
                //LREP("Search match seq: {}\r\n", seq);
                iter = usrList.erase(iter);
                //LREP("List after search and pop: {}\r\n", usrList.size());
                return data;
            }
            ++iter;
        }
        //ASSERT(false); // Not found
        return nullptr;
    }
    //ASSERT(false); // List empty
    return nullptr;
}

/**
 * @brief Layer2::Mac_StartThread
 */
void Layer2::Mac_StartThread() {
    m_ownerThreadTerm = false;
    m_ownerThread = std::thread([&]{
        Mac_OwnerThread();
    });
}

/**
 * @brief Layer2::Mac_OwnerThread
 */
void Layer2::Mac_OwnerThread() {

    //std::unique_lock<std::mutex> lck(m_hSync.mtx);
    while(!m_ownerThreadTerm) {               
        //if(m_hSync.cv.wait_for(lck, std::chrono::milliseconds(100)) == std::cv_status::no_timeout) {
            Mac_RecvTask();
            Mac_SendTask();
        //}
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    //LREP("ISC thread is exited!\r\n");
}

/**
 * @brief Layer2::Mac_RegisterClbEvent
 * @param event
 * @param pFunction
 * @param pParam
 */
void Layer2::Mac_RegisterClbEvent(Layer2::MACEvent event,
                                  std::function<void(std::shared_ptr<uint8_t> pMem, void *pClbParam)> pFunction,
                                  void *pParam) {
    if(pFunction == NULL) {
        ASSERT(false);
        return;
    }

    switch (event) {
    case MAC_EVT_SEND_DONE:
        m_fMacSentData =  pFunction;
        m_macSentParam = pParam;
        break;
    case MAC_EVT_RECV_DATA:
        m_fMacRevData =  pFunction;
        m_macRecvParam = pParam;
        break;
    case MAC_EVT_ERROR:
        m_fMacError=  pFunction;
        m_macErrorParam = pParam;
        break;

    default:
        ASSERT(false);
        break;

    }
}

bool Layer2::Mac_GetStatus() const
{
    return m_flag.bMacStarted;
}

/**
 * @brief Layer2::Mac_ClbRecvData
 * @param eEventCode
 * @param pMem
 * @param pClbParam
 */
void Layer2::Mac_ClbRecvData(EL2Event eEventCode, std::shared_ptr<uint8_t> pMem, void *pClbParam) {

//    static uint32_t count = 0;
//    LREP("MAC RECV FRAME {}\r\n", count++);

    Layer2 *pMac = static_cast<Layer2 *>(pClbParam);

    ASSERT(eEventCode == TRANSL2_EVT_RECV_DATA);
    if (NULL != pMem)
    {
        SFrameInfo *pFrameInfo = (SFrameInfo*)pMem.get();

        uint8_t	   *pFrame = pFrameInfo->pFrame;
        pFrameInfo->u16DLen = SFRAME_GET_DLEN(pFrame);
        pFrameInfo->u8Ctrl = SFRAME_GET_CTRL(pFrame);

        if (pMac->m_fMacRevData) {
            pMac->m_fMacRevData(pMem, pMac->m_macRecvParam);
        }

        // Free in higher layer
        pMem.reset();

    } else {
        ASSERT(false);
    }


}
/**
 * @brief Layer2::Mac_ClbSentData
 * @param eEventCode
 * @param pMem
 * @param pClbParam
 */
void Layer2::Mac_ClbSentData(EL2Event eEventCode, std::shared_ptr<uint8_t> pMem, void *pClbParam) {
    Layer2      *pMac = static_cast<Layer2 *>(pClbParam);
    SFrameInfo  *pFrameInfo = (SFrameInfo*)pMem.get();
    uint8_t 	*pFrame = pFrameInfo->pFrame;

    ASSERT(eEventCode == TRANSL2_EVT_SEND_DONE);
    if(pMem == NULL) {
        ASSERT(false);
        return;
    }

    if (pMac->m_fMacSentData) {
        pMac->m_fMacSentData(pMem, pMac->m_macSentParam);
    }

    /*if the frame require ACK --> queue to SendedQueue*/
    if (IS_ACK_REQ(pFrame[IDX_SFRM_CTRL])) {
        LREP("#");
        pMac->m_lsentDataMutex.lock();
        pMac->m_listSentData.push_back(pMem);
        pMac->m_lsentDataMutex.unlock();
    } else {
        if (pMem != NULL) {
            LREP(">");
            pMem.reset();
        }
    }
}
/**
 * @brief Layer2::Mac_ClbErr
 * @param eEventCode
 * @param pMem
 * @param pClbParam
 */
void Layer2::Mac_ClbErr(EL2Event eEventCode, std::shared_ptr<uint8_t> pMem, void *pClbParam) {

    LREP("MAC ERR \r\n");
    (void)pClbParam;
    ASSERT(eEventCode == TRANSL2_EVT_ERROR);
    if (pMem != NULL)
        pMem.reset();
}

/**
 * @brief Layer2::Mac_CheckTimeOutOfSentFrame
 */
void Layer2::Mac_CheckTimeOutOfSentFrame() {

    size_t listSize = m_listSentData.size();
    for (size_t idx = 0; idx < listSize; idx++) {
        m_lsentDataMutex.lock();
        std::shared_ptr<uint8_t> pMem = Mac_PopHead(m_listSentData);
        m_lsentDataMutex.unlock();
        ASSERT(pMem != NULL);
        SFrameInfo* pFrameInfo = (SFrameInfo*)pMem.get();
        // If frame still wait ACK
        if (pFrameInfo->u8NumSend > 0) {
            if (--pFrameInfo->i16TimeOut == 0)
            {
                //if need, can set timeout by random value
                pFrameInfo->i16TimeOut = ISCL3_TIMEOUT_TICK;
                m_lsendingDataMutex.lock();
                m_listSendingData.push_back(pMem);
                m_lsendingDataMutex.unlock();

                LREP("Resend frm {}\r\n", (int)pFrameInfo->u8Seq);
            }
            else // If frame is not timeout
            {
                m_lsentDataMutex.lock();
                m_listSentData.push_back(pMem);
                m_lsentDataMutex.unlock();
            }
        } else { // After u8NumSend passed
            LREP("NOT GET ACK SEQ {}\r\n", (int)pFrameInfo->u8Seq);
            //delete frame
            if (pMem != NULL)
                pMem.reset();
        }
    }
}

}
}

/************ END OF FILE *************/
