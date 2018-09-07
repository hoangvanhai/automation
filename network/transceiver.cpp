#include "transceiver.h"
#include <QDebug>

Transceiver::Transceiver()
{
    m_client = std::make_shared<communication::endpoint::tcp::Client>();
    m_status = communication::Event_Disconnected;
    m_notify = nullptr;
    m_recvdata = nullptr;
    m_threadTerm = true;
}

bool Transceiver::Start(std::string ipaddr, uint16_t port)
{

    if(m_client == nullptr) {
        ASSERT(false);
        return false;
    }

    LREP("Client: {}:{}\r\n", ipaddr, port);
    m_address.address = ipaddr;
    m_address.port = port;
    m_threadTerm = false;
    m_readThread = std::thread([&](){
        commThread();
    });

    return true;
}

void Transceiver::commThread()
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
        std::dynamic_pointer_cast<communication::endpoint::tcp::Client>(m_client)->disconnectToServer();
        err = std::dynamic_pointer_cast<communication::endpoint::tcp::Client>(m_client)->connectToServer(2000);

//        if(err != 0) {
//            std::this_thread::sleep_for(std::chrono::milliseconds(500));
//            LREP("Retry connect to {} : {}\r\n", m_address.address, m_address.port);
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

        while(!m_threadTerm){
            int event = this->m_client->waitEvent(communication::Event_Readable, 100);
            if(event == communication::Event_Error){
                ASSERT(false);
                qCode = -2;
                m_status = communication::Event_Network_Down;
                break;

            }else if(event == communication::Event_Readable){
                uint8_t m_rxBuffer[4096];
                int rlen = m_client->readData(m_rxBuffer, 4096);
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
                    //LREP("Transceiver recv data len: {}\n", rlen);
                    if(m_recvdata) {
                        m_recvdata(m_rxBuffer, rlen);
                    }
                }
            }
        }

        std::dynamic_pointer_cast<communication::IClient>(m_client)->disconnectToServer();
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

void Transceiver::Stop()
{
    m_threadTerm = true;

    if(m_readThread.joinable())
        m_readThread.join();
}


int Transceiver::sendDataToServerWoLength(uint8_t *pu8Data, size_t len)
{
    if(m_status != communication::Event_Connected) {
        //ASSERT(false);
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

    //printf("Send: %s", pu8Data); fflush(stdout);
    return m_client->writeData(pu8Data,len);
}

int Transceiver::sendDataToServerWithLength(uint8_t *pu8Data, size_t len)
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

    memcpy(&sendData[4], pu8Data, len);
    int slen = m_client->writeData(sendData, length);
    delete[] sendData;

    return slen;

}


communication::Status_Network Transceiver::getStatus() const
{
    return m_status;
}

communication::endpoint::tcp::Client::AttributeDestination Transceiver::getAddress() const
{
    return m_address;
}



