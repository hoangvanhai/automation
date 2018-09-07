#include "ethertrans.h"


EtherTrans::EtherTrans()
{
    recvObj = std::make_shared<communication::endpoint::ethernet::ReceivedDataObject>();
    m_ether = std::make_shared<communication::endpoint::ethernet::Socket>();
    m_status = communication::Event_Disconnected;
}

bool EtherTrans::start(const std::string &ifname, bool send)
{
    int err;
    if(m_ether == nullptr)  {
        std::cout << "Error null m_ether" << std::endl;
        return false;
    }
    m_ifName.ifname = ifname;
    err =  m_ether->setAttribute(communication::endpoint::ethernet::Attribute_Interface, &m_ifName);    
    if(err != 0) return false;


    communication::endpoint::ethernet::AttributeBufferSize bufSize;
    bufSize.recvBufferSize = RXSIZE;
    bufSize.sendBufferSize = TXSIZE;
    bufSize.blockSize      = 65536;
    err = m_ether->setAttribute(communication::endpoint::ethernet::Attribute_BufferSize, &bufSize);   
    if(err != 0) return false;

    m_recvTerm = false;
    m_readThread = std::thread([&] {
        receiveThread();
    });

    if(send) {
        m_transTerm = false;
        m_writeThread = std::thread([&] {
            transmitThread();
        });
    }

    m_status = communication::Event_Connected;
    return true;
}

void EtherTrans::stop()
{
    m_recvTerm = true;
    if(m_readThread.joinable())
        m_readThread.join();
}

void EtherTrans::transmitThread()
{

    uint8_t *sendBuf  = new uint8_t[1000];

    std::cout << "Send thread started \n";
    while(!m_transTerm) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        int slen = sendData(sendBuf, 1000);
        if(slen <= 0)
            std::cout << "Send error len = " << slen << std::endl;
        else
            std::cout << "Send len = " << slen << std::endl;
    }
}

void EtherTrans::receiveThread()
{
    recvObj->receivedEthernetFrame = [&](void* frame, int frameSize){
        struct ether_header* eth = (struct ether_header*)frame;        
        if(ntohs(eth->ether_type) == ETHTYPE){
            int dataLen = frameSize - sizeof(struct ether_header);
            uint8_t *pData = &((uint8_t*)frame)[sizeof(struct ether_header)];
            if(m_recvdata && dataLen > 0) {                
                m_recvdata(pData, dataLen);
            }
        }
    };

    while(!m_recvTerm){
        int event = m_ether->waitEvent(communication::Event_Readable, 100);
        if(event & communication::Event_Error){
            std::cout<<"select error, break"<<std::endl;
            break;
        }
        if(event & communication::Event_Readable){            
            m_ether->readData(0, 0, recvObj);
        }else if(event == communication::Event_Timeout){
            std::cout<<"timeout"<<std::endl;
        }
    }

    m_status = communication::Event_Disconnected;
}

communication::Status_Network EtherTrans::getStatus() const
{
    return m_status;
}

int EtherTrans::sendData(uint8_t *data, uint32_t len)
{
    if(m_status == communication::Event_Disconnected) {
        return -1;
    }

    uint8_t *ethPacket = new uint8_t[len + sizeof(struct ether_header)];

    struct ether_header* eth = (struct ether_header*)ethPacket;
    for(int i = 0; i < ETH_ALEN; i++)
        eth->ether_dhost[i] = 0xFF;
    eth->ether_type = htons(ETHTYPE);

    int event = m_ether->waitEvent(communication::Event_Writable, 100);
    if((event & communication::Event_Writable) == 0){
        std::cout<<"wait ready to write failed or timeout"<<std::endl;
        return -1;
    }

    for(size_t i = 0; i < len; i++){
        ethPacket[sizeof(struct ether_header) + i] = data[i];
    }
    int wlen = m_ether->writeData(ethPacket, sizeof(struct ether_header) + len);    
    delete[] ethPacket;
    return wlen;
}





