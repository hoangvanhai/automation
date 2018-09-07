#include "datastream.h"
#include "limits.h"

DataStream::DataStream()
{
    m_comThreadTerm = true;    
    m_user          = NULL;
    m_dataEvent     = nullptr;
    m_errCode       = 0;
    m_fRecvData     = nullptr;
    m_fSentData     = nullptr;
    m_fError        = nullptr;
    m_recvEvtParam = NULL;
    m_sendEvtParam = NULL;
    m_errorEvtParam = NULL;
    m_flag.Started = false;    
    memset(aesKey, 0, 100);
    hasKey = false;
    m_transType   = DATA_RAW;
    m_crypt = std::make_shared<Crypto>();
}

bool DataStream::Start(std::string ipaddress, int port)
{

    ASSERT(m_packageOneFrame.Init(STREAM_MAX_BYTE_IN_PACKAGE) == true);

    StreamRegisterEvtCallback(Stream_Evt_Recv_Data,
                              [&](uint8_t *pMem, uint32_t len,
                              void *user) {
        StreamProcessFrame(pMem, len, user);
    }, 0);    

    m_flag.Started = true;    

    LREP("Stream service on: {}\r\n", port);
    m_ipaddress = ipaddress;
    m_port = port;
    m_comThreadTerm = false;    
    m_commThread = std::thread([&] {
        ThreadFunction();
    });

    return true;
}

void DataStream::Stop()
{
    m_comThreadTerm = true;
    if(m_commThread.joinable()) {
        m_commThread.join();
    }

    m_packageOneFrame.DeInit();
}

void DataStream::StreamRegisterEvtCallback(DataStream::StreamEvent evt,
                                       std::function<void (uint8_t*, uint32_t, void *)> func,
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


void DataStream::ThreadFunction() {
    int err;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    std::string service;
    service = cppframework::str::Util::convert(m_port);

    if (0 != getaddrinfo(NULL, service.c_str(), &hints, &res)) {
       LREP("illegal port number or port is busy.\n");
       return;
    }

    m_serv = UDT::socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    /**
     * @brief addition option for UDT here
     */
//    int lingerTimeout = 5000;
//    err = UDT::setsockopt(m_serv, 0, UDT_LINGER, (const void*)&lingerTimeout, sizeof(lingerTimeout));
//    if(err != 0) {
//        LREP("UDT_LINGER Error: {}\n", err);
//    }

//    bool block = true;
//    err = UDT::setsockopt(m_serv, 0, UDT_RCVSYN, (const void*)&block, sizeof(block));

    int recvTimeout = 500;
    err = UDT::setsockopt(m_serv, 0, UDT_RCVTIMEO, (const void*)&recvTimeout, sizeof(recvTimeout));
    if(err != 0) {
        LREP("UDT_RCVTIMEO Error: {}\n", err);
    }


    if (UDT::ERROR == UDT::bind(m_serv, res->ai_addr, res->ai_addrlen)) {
       LREP("bind: {}\n" ,UDT::getlasterror_desc());
       return;
    }

    freeaddrinfo(res);

    LREP("Server is ready at: {}\n", service);

    if (UDT::ERROR == UDT::listen(m_serv, 10)) {
       LREP("listen: {}\n",UDT::getlasterror().getErrorMessage());
       return;
    }

    sockaddr_storage clientaddr;
    int addrlen = sizeof(clientaddr);

    UDTSOCKET recver;

    int readSize;
    uint8_t *data = new uint8_t[STREAM_MAX_BYTE_IN_PACKAGE];;

    while(!m_comThreadTerm){

        if (UDT::INVALID_SOCK == (recver = UDT::accept(m_serv, (sockaddr*)&clientaddr, &addrlen))) {
           LREP("accept: {}\n", UDT::getlasterror().getErrorMessage());
           m_comThreadTerm = true;
           return;
        }

        char clienthost[NI_MAXHOST];
        char clientservice[NI_MAXSERV];
        getnameinfo((sockaddr *)&clientaddr, addrlen, clienthost, sizeof(clienthost), clientservice, sizeof(clientservice), NI_NUMERICHOST|NI_NUMERICSERV);
        LREP("new connection: {}:{}\n" , clienthost,clientservice);

        while (!m_comThreadTerm) {
            readSize = UDT::recvmsg(recver, (char*)data, STREAM_MAX_BYTE_IN_PACKAGE);

            if (UDT::ERROR == readSize) {
                if(UDT::getlasterror_code() == 2001) {
                    //LREP("Connection lost\n");
                    break;

                } else {
                    switch(UDT::getlasterror_code()) {
                    case 6003:
                        //LREP("timeout "); fflush(stdout);
                        break;

                    default:
                        break;
                    }
                }
            }            

            if(readSize > 0) {
                if(m_fRecvData) {
                    m_fRecvData(data, readSize, m_recvEvtParam);
                }
            }
        }
        UDT::close(recver);
        LREP("Close recver\n");
    }   
    UDT::close(m_serv);
    LREP("Close server\n");
    delete[] data;
}

int DataStream::SendDataToServerWithLen(uint8_t* data, int len)
{
    int length = len + 4;

    uint8_t *sendData = new uint8_t[length];

    *((uint32_t*)sendData) = len;
    memcpy(&sendData[4], data, len);
    //m_stream->writeData(sendData, length, m_streamDest);

    delete[] sendData;
    return 0;
}


void DataStream::SetAesKey(std::string key)
{
    const char *ptr = key.data();
    LREP("SET KEY: \r\n");
//    for(size_t i = 0; i < key.size(); i++) {
//        aesKey[i] = ptr[i];
//        printf("%02x ", aesKey[i]);
//    }

    hasKey = true;
    m_crypt->SetKey(aesKey, 32);
}



int DataStream::SendDataToServerWithoutLen(uint8_t* data, int len)
{
    (void)data;
    (void)len;

    //return m_stream->writeData(data, len, m_streamDest);
    return 0;
}


void DataStream::StreamProcessFrame(uint8_t *data, uint32_t len, void *user)
{
    (void)user;

    if(m_dataEvent != nullptr && hasKey) {

        if(m_packageOneFrame.Push(data, len) < len) {
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
        if(m_transType == DATA_ENCRYPTED) {
            uint8_t *dataDecrypted = new uint8_t[dataLeng];
            memset(dataDecrypted, 0, dataLeng);
            RecvData(data, dlen);
            m_crypt->DataDecrypt(data, dlen, dataDecrypted);
            m_dataEvent(dataDecrypted[0], dataDecrypted, dataLeng);

            delete[] dataDecrypted;
            delete[] data;
        } else { // raw data
            RecvData(data, dlen);
            m_dataEvent(data[0], data, dlen);
        }
        // Reset status and buffer
        m_packageOneFrame.Reset();

    }
}





















