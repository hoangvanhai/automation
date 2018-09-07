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


#define UDP_FRAME_SIZE                          65536

#define	STREAM_CST_PREAMBLE                     '!'
#define	STREAM_CST_TERMINATE                    '#'

// Byte Index
#define STREAM_IDX_PREAM                        0
#define STREAM_IDX_SEQNUM                       1
#define STREAM_IDX_FRAG                         3
#define STREAM_IDX_FLAG                         4
#define STREAM_IDX_DLEN                         5
#define STREAM_IDX_CRCD                         7
#define STREAM_IDX_DATA0                        9

#define STREAM_GET_SEQ(frm)                     ((frm)[STREAM_IDX_SEQNUM] << 8 | (frm)[STREAM_IDX_SEQNUM + 1])
#define STREAM_GET_FRAG(frm)                    ((frm)[STREAM_IDX_FRAG])
#define STREAM_GET_FLAG(frm)                    ((frm)[STREAM_IDX_FLAG])
#define STREAM_GET_DLEN(frm)                    ((frm)[STREAM_IDX_DLEN] << 8 | (frm)[STREAM_IDX_DLEN + 1])
#define STREAM_GET_CRCD(frm)                    ((frm)[STREAM_IDX_CRCD] << 8 | (frm)[STREAM_IDX_CRCD + 1])
#define STREAM_GET_DATAPTR(frm)                 (&(frm)[STREAM_IDX_DATA0])

#define STREAM_HEADER_SIZE                       9
#define STREAM_MAX_DLEN                         (UDP_FRAME_SIZE - STREAM_HEADER_SIZE)

#define STREAM_IS_ACK_REQ(flag)                 ((flag) & 0x02)
#define STREAM_IS_ACK_FRM(flag)                 ((flag) & 0x08)
#define STREAM_IS_NACK_FRM(flag)                ((flag) & 0x10)
#define STREAM_IS_CRCEN(flag)                   ((flag) & 0x40)
#define STREAM_IS_DATA_FRM(type)                (!STREAM_IS_NACK_FRM(type) && \
                                                 !STREAM_IS_ACK_FRM(type))
#define STREAM_IS_FRAG_FRM(flag)                (!((flag) & 0x01))



#define STREAM_NACK                             0x10
#define STREAM_ACK                              0x08
#define STREAM_ACK_REQ                          0x02

#define STREAM_TIMEOUT_MILLISECOND              300
#define STREAM_MAX_NUM_SEND                     4

#define STREAM_MAX_BYTE_IN_PACKAGE              (UDP_FRAME_SIZE * 256)

class Stream
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
        bool    CheckSeqNum;
        bool    WaitAckFrame;
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
    Stream();

    bool    Start(std::string ipaddress, int port);
    void    Stop();
    void    registerCallback(
            std::function<void(uint8_t type, uint8_t* data, uint32_t dlen)> recvCallbackFn) {
            m_dataEvent = recvCallbackFn;
    }

    bool StreamSendDataLater(uint8_t flag, uint8_t frag, uint8_t *data, uint32_t length);
    bool StreamSendDataImmediate(uint8_t flag, uint8_t frag, uint8_t *data, uint32_t length);
    void SetAesKey(std::string key);
private:
    void ThreadFunction();
    int SendDataToServerWithoutLen(uint8_t* data, int len);
    int SendDataToServerWithLen(uint8_t* data, int len);

    void ProcessThreadFunc();
    void ReceiveTask();
    void SendTask();
    StreamStatus RunSendFrame(std::shared_ptr<uint8_t> pMem);
    void CheckTimeOutOfSentFrame();
    bool StreamSendLater(uint8_t flag, uint8_t frag, uint8_t *data,
                    uint32_t length, FrameType ftype);

    bool StreamSendImmediate(uint8_t flag, uint8_t frag, uint8_t *data,
                    uint32_t length, FrameType ftype);

    StreamAction RecvTask();
    bool    ProcessRecvData();    
    StreamAction OnRecvFrame();
    bool    MemAlloc();
    void    FireEvent(StreamEvent evt);

    void StreamProcessFrame(std::shared_ptr<uint8_t> pMem, void *user);

    inline uint32_t     RecvData(uint8_t *data, uint32_t len) {return m_packageOneFrame.Recv(data, len);}

    inline uint32_t     Recv(uint8_t *data, uint32_t len) {return m_recvFifo.Recv(data, len);}
    inline uint32_t     GetRecvCount()          { return m_recvFifo.GetCount(); }
    inline uint8_t      RecvFifoPop()           { uint8_t b; m_recvFifo.Pop(b); return b; }
    inline void         RecvFifoEnProtect()     { m_recvFifo.EnableProtect(); }
    inline void         RecvFifoDisProtect()    { m_recvFifo.DisableProtect(); }
    inline void         RecvFifoRewindHead()    { m_recvFifo.RewindHeader(); }
    inline void         RecvFifoReset()         { m_recvFifo.Reset(); }


    std::shared_ptr<uint8_t> PopHead(std::list<std::shared_ptr<uint8_t>> &usrList);
    std::shared_ptr<uint8_t> SearchAndPop(std::list<std::shared_ptr<uint8_t>> &usrList, uint16_t seq);
    static void Clb_UpdateTimer(uint32_t time, void *pParam);


    void StreamRegisterEvtCallback(StreamEvent evt,
                                   std::function<void(std::shared_ptr<uint8_t> pMem, void *pClbParam)> func,
                                   void *pParam);

    WaitingPackage    PopWaitingSeq(uint16_t seq);
    bool    SearchWaitingSeq(uint16_t seq);
    bool    SearchFrmIdxOnSeq(uint8_t frmIdx, std::list<SplitedFrame> &list);
    bool    AddWaitingSeqNew(uint16_t seq, SplitedFrame frm);
    bool    AddWaitingSeqOld(uint16_t seq, SplitedFrame frm);
    bool    SortAndGetDataOnList(FIFO & fifo, std::list<SplitedFrame> &list);

    static bool SortData(const SplitedFrame first, const SplitedFrame second);

private:
    std::shared_ptr<communication::ISocket> m_stream;
    std::shared_ptr<communication::endpoint::udp::Destination> m_streamDest;

    std::thread m_commThread;
    bool        m_comThreadTerm;

    std::thread m_processThread;
    bool        m_processThreadTerm;

    void        *m_user;
    std::function<void(uint8_t type, uint8_t* data, uint32_t dlen)>  m_dataEvent;

    Sync         m_trigger;

    uint8_t      m_errCode;

    FIFO         m_recvFifo;
    FIFO         m_packageOneFrame;

    FragFrameStatus m_fragStt;
    uint16_t        m_fragSeq;

    uint32_t     m_recvCount;
    uint32_t     m_recvDlen;
    uint16_t     m_seqError;
    bool         m_isError;
    uint16_t     m_seqRemote;
    uint16_t     m_seqLocal;
    uint16_t     m_seqCMDfrm;

    std::shared_ptr<uint8_t>    m_memRecv;
    std::shared_ptr<uint8_t>    m_memSend;

    uint8_t     *frmRecv;
    uint8_t     *frmSend;

    std::function<void(std::shared_ptr<uint8_t> pMem, void *pClbParam)> m_fRecvData;
    std::function<void(std::shared_ptr<uint8_t> pMem, void *pClbParam)> m_fSentData;
    std::function<void(std::shared_ptr<uint8_t> pMem, void *pClbParam)> m_fError;

    void        *m_recvEvtParam;
    void        *m_sendEvtParam;
    void        *m_errorEvtParam;

    std::mutex          m_lsendingDataMutex;
    std::mutex          m_lsentDataMutex;
    std::mutex          m_lsendingCmdMutex;

    std::list<std::shared_ptr<uint8_t>> m_listSendingData;
    std::list<std::shared_ptr<uint8_t>> m_listSendingCmd;
    std::list<std::shared_ptr<uint8_t>> m_listSentData;

    StreamFlag          m_flag;

    std::shared_ptr<Timer>      m_Timer;
    void*               m_hUpdateTimer;    

    uint8_t         aesKey[100];
    AES_KEY 		sAESEncryptKey;
    std::shared_ptr<Crypto>          m_crypt;
    bool            hasKey;

    std::list<WaitingPackage>  m_waitingPackageList;
};

#endif // STREAM_H
