#include "secureclient.h"
using namespace external::client;
using namespace external::client::connection;

SecureClient::SecureClient()
{
    m_client = std::make_shared<communication::endpoint::ssl::Client>(true);    
    m_status = communication::Event_Disconnected;
    m_notify = nullptr;
    m_recvdata = nullptr;
    m_isauthen = false;
    m_hasDataInfo = false;
    m_threadTerm = true;
}

bool SecureClient::Start(std::string ipaddr, uint16_t port)
{

    if(m_client == nullptr) {
        ASSERT(false);
        return false;
    }

    m_address.address   = ipaddr;
    m_address.port      = port;
    LREP("address {}:{}\n", m_address.address, m_address.port);
    m_threadTerm        = false;
    m_readThread = std::thread([&](){
        commThread();
    });

    return true;
}

void SecureClient::commThread()
{
    int err;
    while(!m_threadTerm){

        m_status = communication::Event_Connecting;
        if(m_notify) {
            m_notify(m_status);
        }        

        err = m_client->setAttribute(communication::endpoint::tcp::Client::Attribute_Destination, &m_address);
        ASSERT(0 == err);

        communication::endpoint::tcp::AttributeBufferSize bufferSizeSet;
        bufferSizeSet.recvBufferSize = 1024*1024*1;
        bufferSizeSet.sendBufferSize = 1024*1024*2;
        err = m_client->setAttribute(communication::endpoint::tcp::Attribute_BufferSize, &bufferSizeSet);
        ASSERT(0 == err);
        std::dynamic_pointer_cast<communication::endpoint::ssl::Client>(m_client)->disconnectToServer();
        LREP("Start connect \n");
        err = std::dynamic_pointer_cast<communication::endpoint::ssl::Client>(m_client)->connectToServer(2000);        

//        if(err != 0) {
//            std::this_thread::sleep_for(std::chrono::milliseconds(500));
//            LREP("Retry connect to {} : {}\n", m_address.address, m_address.port);
//            continue;
//        }

        if(err == 0) {
            m_status = communication::Event_Connected;
            LREP("Connected to server {} : {} \r\n", m_address.address, m_address.port);
            if(m_notify) {
                m_notify(m_status);
            }
        } else {
            m_threadTerm = true;
            m_status = communication::Event_Network_Down;
        }

        int errCnt = 0;
        int qCode = 0;
        int timeoutCount = 0;

        while(!m_threadTerm) {
            int event = m_client->waitEvent(communication::Event_Readable, 100);
            if(event == communication::Event_Error){
                ASSERT(false);
                qCode = -2;
                m_status = communication::Event_Network_Down;
                break;

            } else if(event == communication::Event_Readable){
                uint8_t rxBuffer[65535];
                int rlen = m_client->readData(rxBuffer, 65535);
                if(rlen <= 0)
                {
                    errCnt++;
                    if(errCnt > 5){
                        qCode = -3;
                        m_status = communication::Event_Network_Down;
                        break;
                    }
                } else {
                    errCnt = 0;
                    uint32_t length = (rxBuffer[0] << 24) |
                                       rxBuffer[1] << 16 |
                                       rxBuffer[2] << 8 |
                                       rxBuffer[3];
                    if(length > 65535) {
                        qCode = -4;
                        break;
                    }
                    //LREP("Read length: {}\r\n", rlen);
                    ProcessSslRecvData(&rxBuffer[4], rlen - 4);
                }
            }
            if(event == communication::Event_Timeout){
                if(timeoutCount++ >= 10) { // 1s
                    if (!m_isauthen) {
                        LREP("Send auth msg ... \n");
                        sendAuthenMsg();
                    } /*else if(!m_hasDataInfo) {
                        requestDataMsg(12399);
                    }*/ else {
                        //LREP("<");
                        sendKeepConnection();
                    }
                    timeoutCount = 0;
                }
            }
        }                

        std::dynamic_pointer_cast<communication::endpoint::ssl::Client>(m_client)->disconnectToServer();
        LREP("disconnected to server {}@{} code {}\r\n", m_address.port, m_address.address, qCode);

//        if(!m_threadTerm)
//            continue;

        m_threadTerm = true;
    }

    if(m_status == communication::Event_Connected)
        m_status = communication::Event_Disconnected;

    m_threadTerm = true;
    if(m_notify) {
        m_notify(m_status);
    }

}



void SecureClient::Stop()
{
    //if(m_threadTerm == false)
    {
        m_threadTerm = true;
        if(m_readThread.joinable())
            m_readThread.join();
    }

    m_notify = nullptr;
    m_recvdata = nullptr;
    m_isauthen = false;
    m_hasDataInfo = false;
}

int SecureClient::sendDataToServer(uint8_t id, uint8_t *payload, int32_t len)
{
    int event = m_client->waitEvent(communication::Event_Writable, 100);

    if(event & communication::Event_Error){
        LREP("select failed");
        return -1;
    }

    if((event & communication::Event_Writable) == 0){
        LREP("event not writable");
        return -1;
    }

    uint8_t *sendData = new uint8_t[len + 2];
    if(len > (255 - 2)) {
        ASSERT(false);
        return -1;
    }

    sendData[0] = len + 1;
    sendData[1] = id;
    for(int i = 0; i < len; i++) {
        sendData[2 + i] =  payload[i];
    }

    int slen = m_client->writeData(sendData, len+2);
    delete[] sendData;

    return slen;
}

int SecureClient::sendDataToServer(uint8_t *payload, int32_t len)
{
    if(m_status != communication::Event_Connected) {
        ASSERT(false);
        return -1;
    }
    int event = m_client->waitEvent(communication::Event_Writable, 100);
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

    sendData[0] = (len >> 24) & 0xFF;
    sendData[1] = (len >> 16) & 0xFF;
    sendData[2] = (len >> 8) & 0xFF;
    sendData[3] = len & 0xFF;

    memcpy(&sendData[4], payload, len);
    int slen = m_client->writeData(sendData, length);
    delete[] sendData;

    return slen;
}


void SecureClient::sendKeepConnection()
{
    Message msg;
    Ping ping;
    msg.set_type(Type::PING);
    ::google::protobuf::Any* datamsg = msg.mutable_data();

    datamsg->PackFrom(ping);

    int dlen = msg.ByteSize();
    uint8_t *data = new uint8_t[dlen];

    if(msg.SerializeToArray(data, dlen)) {
        sendDataToServer(data, dlen);
    }

    delete[] data;
}

void SecureClient::sendAuthenMsg() {

    time_t tim;
    time(&tim);
    m_authkey = tim;

    Message msg;
    Authenticate auth;
    auth.set_username("user");
    auth.set_secret("1234");
    msg.set_type(Type::AUTHENTICATION);
    ::google::protobuf::Any* datamsg = msg.mutable_data();

    datamsg->PackFrom(auth);
    Rpc *rpc = msg.mutable_rpc();
    rpc->set_id(m_authkey);

    int dlen = msg.ByteSize();
    uint8_t *data = new uint8_t[dlen];

    LREP(msg.DebugString());

    if(msg.SerializeToArray(data, dlen)) {        
        sendDataToServer(data, dlen);
    }

    delete[] data;
}

void SecureClient::requestDataMsg(int port)
{
    LREP("Send Request data \n");
    Message msg;
    DataChannelRequest dataReq;
    dataReq.set_address("192.168.1.99");
    dataReq.set_port(port);
    dataReq.set_protocol("udt-aes");

    msg.set_type(Type::DATA_CHANNEL);
    ::google::protobuf::Any* datamsg = msg.mutable_data();

    datamsg->PackFrom(dataReq);

    int dlen = msg.ByteSize();
    uint8_t *data = new uint8_t[dlen];

    if(msg.SerializeToArray(data, dlen)) {
        sendDataToServer(data, dlen);
    }

    delete[] data;
}


void SecureClient::ProcessSslRecvData(void *data, uint32_t len)
{
    Message msg;


    if(msg.ParseFromArray(data, len)) {      

        switch (msg.type()) {

        case ::Type::PONG:            
            break;
        case ::Type::RESPONSE:
        {

            const Rpc &rpc = msg.rpc();
            if(rpc.id() == m_authkey) {
                LREP("\r\nAuthenticate Successfully\r\n");
                m_isauthen = true;
            }
        }
            break;

//        case ::Type::PERMISSION:
//        {
//            LREP("PERMISSION MSG\r\n");

//        }
//            break;
//        case ::Type::DATA_CHANNEL:
//        {

//        }
//            break;
//        case ::Type::MISSION:
//        {
//            LREP("Mission msg\r\n");
//        }
//            break;
//        case ::Type::ONLINE:
//        {
//            LREP("Online msg\r\n");
//        }
//            break;
//        case ::Type::SIGNAL_CALC:
//        {
//            LREP("Signal calc msg\r\n");
//        }
//            break;
//        case ::Type::NOISEFLOOR:
//        {
//            LREP("Noise floor msg\r\n");
//        }
//            break;
//        case ::Type::REMOTE_SENSOR:
//        {
//            LREP("Remote sensor msg\r\n");
//        }
//            break;
//        case ::Type::LOCAL_SENSOR:
//        {
//            LREP("Local sensor msg\r\n");
//        }
//            break;
//        case ::Type::SENSOR:
//        {
//            LREP("Sensor msg\r\n");
//        }
//            break;
//        case ::Type::SERVER:
//        {
//            LREP("Server msg\r\n");
//        }
//            break;
//        case ::Type::SPECTRUM_OFFLINE:
//        {
//            LREP("Spectrum online msg\r\n");
//        }
//            break;
//        case ::Type::SIGNAL:
//        {
//            LREP("Signal msg\r\n");
//        }
//            break;
//        case ::Type::GEOLOCATION:
//        {
//            LREP("Geo location msg\r\n");
//        }
//            break;
//        case ::Type::CLASSIFICATION:
//        {
//            LREP("Classification msg\r\n");
//        }
//            break;
//        case ::Type::RECORDING:
//        {
//            LREP("Recording msg\r\n");
//        }
//            break;
//        case ::Type::DEMODULATION:
//        {
//            LREP("Demodulation msg\r\n");
//        }
//            break;
//        case ::Type::AUTOMATION:
//        {
//            LREP("Automation msg\r\n");
//        }
//            break;
//        case ::Type::CALIBRATION:
//        {
//            LREP("Calibration msg\r\n");
//        }
//            break;
//        case ::Type::TEST:
//        {
//            LREP("Test msg\r\n");
//        }
//            break;

        default:
            //LREP("Not handled type: {}\r\n", msg.type());
            break;
        }

//        if(msg.type() != ::Type::PONG)
//            LREP("{} \r\n", msg.DebugString());

    } else {
        LREP("Parse failed\r\n");
    }

    if(m_recvdata)
        m_recvdata(data, len);
}

communication::Status_Network SecureClient::getStatus() const
{
    return m_status;
}








