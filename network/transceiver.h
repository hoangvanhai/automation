#ifndef TRANSCEIVER_H
#define TRANSCEIVER_H
#include <communication/socket/tcp/TCPClient.h>
#include <communication/socket/tcp/TCPServer.h>
#include <communication/protocol/StreamFraming.h>
#include "debug.h"
#include <thread>
#include <mutex>
#include <condition_variable>


class Transceiver
{

public:
    Transceiver();
    bool Start(std::string ipaddr, uint16_t port);
    void commThread();
    void Stop();
    int sendDataToServerWoLength(uint8_t *pu8Data, size_t len);
    int sendDataToServerWithLength(uint8_t *pu8Data, size_t len);
    void SetEventConnectionCallback(std::function<void(communication::Event_Network evt)> func, void *pParam) {
        (void)pParam;
        if(func) {
            m_notify = func;
        }
    }

    void SetEventDataCallback(std::function<void(const void *data, int len)> func, void *pParam) {
        (void)pParam;
        if(func) {
            m_recvdata = func;
        }
    }

    communication::Status_Network getStatus(void) const;
    communication::endpoint::tcp::Client::AttributeDestination getAddress() const;
private:

    std::shared_ptr<communication::ISocket> m_client;
    communication::endpoint::tcp::Client::AttributeDestination m_address;
    std::shared_ptr<communication::ILayer> m_framing;

    std::function<void(communication::Event_Network evt)>              m_notify;
    std::function<void(const void *data, int len)>      m_recvdata;
    void *m_user;

    std::thread          m_readThread;
    bool                 m_threadTerm;
    communication::Status_Network       m_status;

};
#endif // TRANSCEIVER_H
