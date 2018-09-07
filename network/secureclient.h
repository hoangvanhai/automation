#ifndef SSLCLIENT_H
#define SSLCLIENT_H

#include <communication/socket/ssl/SSLClient.h>
#include <communication/protocol/StreamFraming.h>
#include "debug.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <client_msg/msg.pb.h>
#include <client_msg/connection/pingpong.pb.h>
#include <client_msg/connection/authentication.pb.h>
#include <client_msg/connection/data_channel.pb.h>
#include <client_msg/configuration/online.pb.h>


class SecureClient
{
public:
    SecureClient();
    bool Start(std::string ipaddr, uint16_t port);
    void StartBackGround();
    void commThread();    
    void Stop();
    int sendDataToServer(uint8_t id, uint8_t *payload, int32_t len);
    int sendDataToServer(uint8_t *payload, int32_t len);
    void sendKeepConnection();
    void sendAuthenMsg();
    void requestDataMsg(int port);
    void ProcessSslRecvData(void *data, uint32_t len);
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


    void  setDataInfo(bool val) {m_hasDataInfo = val;}
    bool  getDataInfo(void) const {return m_hasDataInfo;}


    communication::Status_Network getStatus(void) const;


private:

    std::shared_ptr<communication::ISocket> m_client;
    communication::endpoint::tcp::Client::AttributeDestination m_address;

    std::function<void(communication::Event_Network evt)>        m_notify;
    std::function<void(const void *data, int len)>    m_recvdata;
    void *m_user;

    std::thread          m_readThread;
    bool                 m_threadTerm;    
    communication::Status_Network       m_status;

    bool                 m_isauthen;
    bool                 m_hasDataInfo;
    uint64_t             m_authkey;

};

#endif // SSLCLIENT_H
