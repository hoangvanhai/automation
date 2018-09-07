#ifndef LAYER1_H
#define LAYER1_H

#include "crc8.h"
#include "fifo.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <communication/socket/serialport/SerialSocket.h>
#include "iscconfig.h"
#include "debug.h"

typedef  struct _CV{
    std::mutex mtx;
    std::condition_variable cv;
}SCV;


typedef enum
{
    TRANS_ERR_SUCCESS = 0,
    TRANS_ERR_FAILURE = 1,
    TRANS_ERR_MEM = 2,
    TRANS_ERR_BUSY = 10,
    TRANS_ERR_NOT_STARTED = 11,
    TRANS_ERR_L1_TIMEOUT = 12,
    TRANS_ERR_L2_TIMEOUT = 13,
    TRANS_ERR_INVALID_PTR = 14,
    TRANS_ERR_INVALID_DATA = 15,
    TRANS_ERR_CRCH = 16,
    TRANS_ERR_CRCD = 17,
    TRANS_ERR_PARAM = 18,
    TRANS_ERR_REMOTE = 19,
    TRANS_ERR_REMOTE_DLEN = 20,
    TRANS_ERR_REMOTE_CRCH = 21,
    TRANS_ERR_REMOTE_CRCD = 22,
    TRANS_ERR_UNKNOWN = 30
}ETransReturn, ETransErrorCode, ETransStatus;


class Layer1
{

public:

    typedef struct _SerialContext {
        std::shared_ptr<communication::ISocket> sock;
        std::string portName;
        int baudRate;
        int dePin;
    }SerialPort;



    enum EL1Event
    {
        TRANSL1_EVT_NONE = 0,
        TRANSL1_EVT_SEND_DONE = 1,	//L1 Send done
        TRANSL1_EVT_RECV_BYTE = 2,	//L1 receive a byte
        TRANSL1_EVT_ERROR = 3
    };

    typedef struct _SL1Flag
    {
        bool bL1Started;
        bool bL1Sending;
    }SL1Flag;

public:
    Layer1();
    Layer1(std::string port, int baudrate);

    void    Configure(std::string port, int baudrate);
    bool    Start();
    void    Stop(void);
    bool    InitSerial(void);
    bool    IsSendReady(void);
    ETransErrorCode Send(uint8_t *data, uint32_t len);
    bool    SendData(uint8_t* data, uint32_t len);

    inline uint32_t Recv(uint8_t *data, uint32_t len) { return m_recvFifo.Recv(data, len); }
    inline uint32_t GetRecvCount() { return m_recvFifo.GetCount(); }
    inline uint8_t RecvFifoPop() {uint8_t b; m_recvFifo.Pop(b);return b; }
    inline void RecvFifoEnProtect()     { m_recvFifo.EnableProtect(); }
    inline void RecvFifoDisProtect()    { m_recvFifo.DisableProtect(); }
    inline void RecvFifoRewindHead()    { m_recvFifo.RewindHeader(); }
    inline void RecvFifoReset()         { m_recvFifo.Reset(); }

    void    SerialListenerThread();
    void    RegisterCallbackEvent(EL1Event type,
                                  std::function<void(void*pParam)> pFunc,
                                  void* pParam);

private:

    SerialPort  m_serialPort;    
    bool        m_serialListenTerm;
    uint8_t     *m_pSendBuff;
    uint32_t    m_sendSize;
    FIFO        m_recvFifo;

    void        *m_recDataParam;
    void        *m_sendDataParam;

    std::function<void(void*pParam)> m_fRecvDataClb;
    std::function<void(void*pParam)> m_fSentDataClb;
    std::function<void(void*pParam)> m_fErrorClb;

    std::thread m_serialThread;

    SL1Flag     m_flag;

};

#endif // LAYER1_H
