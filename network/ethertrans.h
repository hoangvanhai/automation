#ifndef ETHERTRANS_H
#define ETHERTRANS_H
#include <cppframework.h>
#include <communication/socket/ethernet/EthernetSocket.h>
#include <thread>
#include <safe/Safe.h>


#ifdef __linux__
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <unistd.h>
#elif defined(_MSC_VER)
#include <WinSock2.h>
#define IFNAME_1    "p4p1"
#define IFNAME_2    "p4p2"

#define ETH_ALEN	6
struct ether_header {
        uint8_t  ether_dhost[ETH_ALEN];
        uint8_t  ether_shost[ETH_ALEN];
        unsigned short ether_type;
};
#endif


#define TXSIZE      (1024*16)
#define RXSIZE      (1024*32)
#define TXDATASIZE  65536
#define TXDATALOOP  5
#define ETHTYPE     0x1234





class EtherTrans
{

public:
    EtherTrans();

    bool start(const std::string &ifname, bool send = false);
    void stop();
    void transmitThread();
    void receiveThread();
    communication::Status_Network getStatus() const;
    int  sendData(uint8_t *data, uint32_t len);

    std::shared_ptr<communication::ISocket> m_ether;
    std::shared_ptr<communication::endpoint::ethernet::ReceivedDataObject> recvObj;

    void SetEventDataCallback(std::function<void(uint8_t *data, int len)> func, void *pParam) {
        (void)pParam;
        if(func) {
            m_recvdata = func;
        }
    }


private:
    bool        m_transTerm;
    bool        m_recvTerm;
    std::thread m_readThread;
    std::thread m_writeThread;

    std::function<void(uint8_t *data, int len)>      m_recvdata;

    communication::endpoint::ethernet::AttributeInterface m_ifName;

    communication::Status_Network m_status;
};

#endif // ETHERTRANS_H
