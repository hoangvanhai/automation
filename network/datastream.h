#ifndef STREAM_H
#define STREAM_H

#include <communication/socket/ISocket.h>
#include <communication/protocol/ILayer.h>
#include <communication/socket/udp/UDPSocket.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "debug.h"
#include "isc/fifo.h"
#include "isc/crc8.h"
#include <cstring>
#include "isc/timer.h"
#include "aes/crypto.h"
#include "dataflowextract.h"
#include "udt/udt.h"
#include "string/StringUtils.h"

#ifndef WIN32
   #include <unistd.h>
   #include <cstdlib>
   #include <cstring>
   #include <netdb.h>
#else
   #include <winsock2.h>
   #include <ws2tcpip.h>
   #include <wspiapi.h>
#endif


#define UDP_FRAME_SIZE                          65536

#define STREAM_NACK                             0x10
#define STREAM_ACK                              0x08
#define STREAM_ACK_REQ                          0x02

#define STREAM_TIMEOUT_MILLISECOND              300
#define STREAM_MAX_NUM_SEND                     4

#define STREAM_MAX_BYTE_IN_PACKAGE              (UDP_FRAME_SIZE * 2)

class DataStream
{

    struct Sync{
        std::mutex mtx;
        std::condition_variable cv;
    };

    enum FragFrameStatus {
        Frag_Frame_Done = 0,
        Frag_Frame_Collecting,
    };

    enum FrameType {
        Frame_Command = 0,
        Frame_Data,
    };
    enum StreamStatus
    {
        /*General return values*/
        STREAM_ERR_SUCCESS = 0,
        STREAM_ERR_FAILURE = 1,
        STREAM_ERR_MEM = 2,
        STREAM_ERR_BUSY = 10,
        STREAM_ERR_NOT_STARTED = 11,
        STREAM_ERR_L1_TIMEOUT = 12,
        STREAM_ERR_L2_TIMEOUT = 13,
        STREAM_ERR_INVALID_PTR = 14,
        STREAM_ERR_INVALID_DATA = 15,
        STREAM_ERR_CRCH = 16,
        STREAM_ERR_CRCD = 17,
        STREAM_ERR_PARAM = 18,
        STREAM_ERR_REMOTE = 19,
        STREAM_ERR_REMOTE_DLEN = 20,
        STREAM_ERR_REMOTE_CRCH = 21,
        STREAM_ERR_REMOTE_CRCD = 22,
        STREAM_ERR_UNKNOWN = 30
    };


    enum StreamEvent {
        Stream_Evt_None = 0,
        Stream_Evt_Send_Done,
        Stream_Evt_Recv_Data,
        Stream_Evt_Error,
    };

    enum StreamAction {
        Stream_Act_None = 0,
        Stream_Recv_Ack,
        Stream_Recv_Nack,
        Stream_Req_Ack,
        Stream_Req_Nack,
    };

    struct StreamFlag {
        bool    Started;
    };

    struct StreamFrame{
        uint32_t        timeout;
        uint8_t         maxSend;
        uint8_t         flag;
        uint8_t         frag;
        uint16_t        seq;
        uint32_t        dataLength;
        uint8_t         *data;
        uint8_t         *frame;
    };

    struct SplitedFrame {
      uint8_t                   fragSeq;
      uint32_t                  length;
      std::shared_ptr<uint8_t>  body;
    };

    struct WaitingPackage {
        uint16_t    sequence;
        std::list<SplitedFrame> splitedData;
    };

public:
    DataStream();

    bool    Start(std::string ipaddress, int port);
    void    Stop();
    void    registerCallback(
            std::function<void(uint8_t type, uint8_t* data, uint32_t dlen)> recvCallbackFn) {
            m_dataEvent = recvCallbackFn;
    }

    bool    StreamSendDataLater(uint8_t flag, uint8_t frag, uint8_t *data, uint32_t length);
    bool    StreamSendDataImmediate(uint8_t flag, uint8_t frag, uint8_t *data, uint32_t length);
    void    SetAesKey(std::string key);
    void    SetTransType(DataTransferType type) { m_transType = type;}
    DataTransferType GetTransType(void) const { return m_transType;}
private:
    void    ThreadFunction();
    int     SendDataToServerWithoutLen(uint8_t* data, int len);
    int     SendDataToServerWithLen(uint8_t* data, int len);

    void    ProcessThreadFunc();
    void    ReceiveTask();
    void    SendTask();
    StreamStatus RunSendFrame(std::shared_ptr<uint8_t> pMem);
    void    CheckTimeOutOfSentFrame();
    bool    StreamSendLater(uint8_t flag, uint8_t frag, uint8_t *data,
                    uint32_t length, FrameType ftype);

    bool    StreamSendImmediate(uint8_t flag, uint8_t frag, uint8_t *data,
                    uint32_t length, FrameType ftype);    

    void StreamProcessFrame(uint8_t *data, uint32_t len, void *user);

    inline uint32_t     RecvData(uint8_t *data, uint32_t len) {return m_packageOneFrame.Recv(data, len);}    

    static void Clb_UpdateTimer(uint32_t time, void *pParam);
    std::shared_ptr<uint8_t> PopHead(std::list<std::shared_ptr<uint8_t>> &usrList);

    void StreamRegisterEvtCallback(StreamEvent evt,
                                   std::function<void (uint8_t *, uint32_t, void *)> func,
                                   void *pParam);


private:

    UDTSOCKET m_serv;
    addrinfo hints;
    addrinfo* res;

    std::string m_ipaddress;
    int         m_port;

    std::thread m_commThread;
    bool        m_comThreadTerm;

    void        *m_user;
    std::function<void(uint8_t type, uint8_t* data, uint32_t dlen)>  m_dataEvent;

    Sync         m_trigger;

    uint8_t      m_errCode;

    FIFO         m_packageOneFrame;

    std::function<void(uint8_t* pMem, uint32_t len, void *pClbParam)> m_fRecvData;
    std::function<void(uint8_t* pMem, uint32_t len, void *pClbParam)> m_fSentData;
    std::function<void(uint8_t* pMem, uint32_t len, void *pClbParam)> m_fError;

    void        *m_recvEvtParam;
    void        *m_sendEvtParam;
    void        *m_errorEvtParam;


    StreamFlag          m_flag;

    void*               m_hUpdateTimer;    

    uint8_t         aesKey[100];
    AES_KEY 		sAESEncryptKey;
    std::shared_ptr<Crypto>          m_crypt;
    bool            hasKey;

    std::list<WaitingPackage>  m_waitingPackageList;

    DataTransferType    m_transType;
};

#endif // STREAM_H
