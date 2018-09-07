#include "layer1.h"


Layer1::Layer1()
{
    m_serialPort.portName = DEFAULT_PORT_NAME;
    m_serialPort.baudRate = DEFAULT_BAUDRATE;
    m_serialListenTerm = true;

    m_fErrorClb = nullptr;
    m_fRecvDataClb = nullptr;
    m_fSentDataClb = nullptr;
    m_recDataParam = nullptr;
    m_sendDataParam = nullptr;

}

Layer1::Layer1(std::string port, int baudrate)
{
    m_serialPort.portName = port;
    m_serialPort.baudRate = baudrate;
    m_serialListenTerm = true;

    m_fErrorClb = nullptr;
    m_fRecvDataClb = nullptr;
    m_fSentDataClb = nullptr;
    m_recDataParam = nullptr;
    m_sendDataParam = nullptr;
}

void Layer1::Configure(std::string port, int baudrate)
{
    m_serialPort.portName = port;
    m_serialPort.baudRate = baudrate;
    m_serialListenTerm = true;
}

bool Layer1::Start()
{
    if(m_recvFifo.Init(DEFAULT_SIZE_RECV_BUF) != true) {
        ASSERT(false);
        return false;
    }

    if(InitSerial() != true) {
        ASSERT(false);
        return false;
    }

    m_serialListenTerm = false;
    m_serialThread = std::thread([&]{
        SerialListenerThread();
    });

    m_flag.bL1Started = true;
    m_flag.bL1Sending = false;
    return true;
}

void Layer1::Stop()
{
    m_serialListenTerm = true;
    if(m_serialThread.joinable()) {
        m_serialThread.join();
    }
    communication::endpoint::serialport::AttributePortName portNameArgs;
    m_serialPort.sock->setAttribute(communication::endpoint::serialport::Attribute_CloseDevice, &portNameArgs);
    m_serialPort.sock.reset();

    m_recvFifo.DeInit();
}

bool Layer1::InitSerial(void)
{
    int err = 0;
    m_serialPort.sock = std::make_shared<communication::endpoint::serialport::SerialSocket>();
    if(m_serialPort.sock == nullptr) {
        LREP("Create handle failed -> null pointer \r\n");
        return false;
    }

    communication::endpoint::serialport::AttributePortName portNameArgs;
#if defined (__linux__)
    portNameArgs.portname = "/dev/" + m_serialPort.portName;
#else
    portNameArgs.portname = m_serialPort.portName;
    err = m_serialPort.sock->setAttribute(communication::endpoint::serialport::Attribute_CloseDevice, &portNameArgs);
#endif
    LREP("ISC started on {} ", portNameArgs.portname);
    err = m_serialPort.sock->setAttribute(communication::endpoint::serialport::Attribute_PortName, &portNameArgs);
    if(err != 0) {
        LREP(" FAILED (Port open failed, check privilege)\r\n");
        return false;
    }
    // setup config
    communication::endpoint::serialport::AttributeConfiguration cfgArgs;
    cfgArgs.baudrate = m_serialPort.baudRate;
    cfgArgs.wordBits = communication::endpoint::serialport::WordBits_8;
    cfgArgs.stopBits = communication::endpoint::serialport::StopBits_1;
    cfgArgs.parity = communication::endpoint::serialport::Parity_None;
    cfgArgs.useHardwareFlowControl = false;
    err = m_serialPort.sock->setAttribute(communication::endpoint::serialport::Attribute_Configuration, &cfgArgs);
    if(err != 0) {
        LREP("Setup attribute failed !\r\n");
        return false;
    }
    LREP(" SUCCESS \r\n")
    return true;
}

bool Layer1::IsSendReady()
{
    return (m_flag.bL1Started == true && m_flag.bL1Sending == false);
}

ETransErrorCode Layer1::Send(uint8_t *data, uint32_t len)
{
    if (m_flag.bL1Started == false)
    {
        ASSERT(false);
        return TRANS_ERR_NOT_STARTED;
    }

    if (m_flag.bL1Sending == true)
    {
        ASSERT(false);
        return TRANS_ERR_BUSY;
    }

    if (data == NULL || len == 0)
    {
        ASSERT(false);
        return TRANS_ERR_PARAM;
    }

    m_pSendBuff = data;
    m_sendSize = len;


    m_flag.bL1Sending = true;


    // Need to check when tx buffer is free
    if (m_serialPort.sock) {
        ASSERT(SendData(data, len) == true)
    }

//    for(int i = 0; i < len; i++)
//        printf("0x%x-", data[i]);

    m_flag.bL1Sending = false;

    if (m_fSentDataClb != nullptr && m_sendDataParam != NULL) {
        m_fSentDataClb(m_sendDataParam);
    } else {
        ASSERT(false);
    }

    return TRANS_ERR_SUCCESS;
}

bool Layer1::SendData(uint8_t *data, uint32_t len) {


    int event = m_serialPort.sock->waitEvent(communication::Event_Writable, 100);

    if(event & communication::Event_Error){
        LREP("select failed");
        return false;
    }
    if((event & communication::Event_Writable) == 0){
        LREP("event not writable");
        return false;
    }



    uint32_t w = (uint32_t)m_serialPort.sock->writeData(data, len);


    ASSERT(w == len);

    return true;
}



void Layer1::SerialListenerThread() {

    uint8_t rxBuff[4096];
    int idx;


    while (!m_serialListenTerm) {

        int event = m_serialPort.sock->waitEvent(communication::Event_Readable, 100);

        if (event & communication::Event_Error) {
            LREP_WARN("Wait error\r\n");
        }

        if (event & communication::Event_Readable) {
            int rlen = m_serialPort.sock->readData(rxBuff, 4096);
            if (rlen > 0) {
                if(m_recvFifo.Push(rxBuff, (uint32_t)rlen) < rlen) {
                    LREP("ISC push large data {} -> FIFO error -> Reset FIFO\n");
                    m_recvFifo.Reset();
                }

                if (m_fRecvDataClb != nullptr && m_recDataParam != NULL) {
                    m_fRecvDataClb(m_recDataParam);
                } else {
                    ASSERT(false);
                }
            }
        }

        if(event == communication::Event_Timeout) {

        }
    }

    LREP("ISC stopped!\r\n");
}

/**
 * @brief Layer1::RegisterCallbackFunction
 * @param type
 * @param pFunc
 * @param pParam
 */
void Layer1::RegisterCallbackEvent(Layer1::EL1Event type,
                                      std::function<void (void *)> pFunc,
                                      void *pParam) {

    switch (type) {
    case TRANSL1_EVT_RECV_BYTE:
        m_fRecvDataClb = pFunc;
        m_recDataParam = pParam;
        break;
    case TRANSL1_EVT_SEND_DONE:
        m_fSentDataClb = pFunc;
        m_sendDataParam = pParam;
        break;
    case TRANSL1_EVT_ERROR:
        m_fErrorClb = pFunc;
        break;
    default:
        ASSERT(false);
        break;

    }
}


