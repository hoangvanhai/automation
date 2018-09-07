#ifndef LAYER2_H
#define LAYER2_H

#include "layer1.h"
#include "timer.h"
#include <memory>


namespace communication {
namespace isc {
class Layer2
{
private:
    typedef enum
    {
        E_CMD_FRM = 0,      //(CMD_ACK or CMD_NACK)
        E_DATA_FRM = 1       //(DATA_FRM)

    }EPackageType;


    typedef enum E_ISCL2_EVENT {
        TRANSL2_EVT_NONE = 0,
        TRANSL2_EVT_SEND_DONE = 1,	//Data indicate
        TRANSL2_EVT_RECV_DATA = 2,	//Data confirm
        TRANSL2_EVT_ERROR = 3
    }EL2Event;

    typedef enum
    {
        ISCL2_ACT_NO = 0,

        ISCL2_RCV_ACK = 1,  //receive ACK frame from master
        ISCL2_RCV_NACK = 2,  //receive ACK frame from master

        ISCL2_REQ_ACK = 3,  //recieve data frame requireing ACK
        ISCL2_REQ_NACK = 4   //receive a wrong frame

    }EL2RecvAction;


    typedef struct _L2Flag {
        bool bL2Started;
        bool bL2Sending;
        bool bL2L1Sending;
        bool bL2WaitingL1Send;
        bool bL2CheckSeqNum;
        bool bUpdateWaitingACKFrameState;
        bool bMacStarted;
    }L2Flag;

public:
    typedef struct _SFrameInfo
    {
        /*Time out, in mili-second*/
        uint16_t			i16TimeOut;

        /*Number of send*/
        uint8_t             u8NumSend;

        /*Control*/
        uint8_t 			u8Ctrl;

        /*Sequence*/
        uint8_t             u8Seq;

        /*data length*/
        uint16_t 			u16DLen;

        /*Pointer to data field of IBC frame*/
        uint8_t 			*pu8Data;

        /*Pointer to frame*/
        uint8_t             *pFrame;

    } SFrameInfo;

    enum MACEvent
    {
        MAC_EVT_NONE = 0,
        MAC_EVT_SEND_DONE = 1,	//Data indicate
        MAC_EVT_RECV_DATA = 2,	//Data confirm
        MAC_EVT_ERROR = 3,
        MAC_EVT_CONNECTED,
        MAC_EVT_DISCONNECTED,
    };    

    /* INTERFACE SECTION */
    Layer2();
private:
    bool    Start(std::string portname, int baudrate, void *sem, uint8_t myId);

    EL2RecvAction RecvTask();
    bool    SendTask();


    ETransErrorCode Send(std::shared_ptr<uint8_t> pMem);

    void    RegisterClbEvent(EL2Event event,
                          std::function<void(EL2Event eEventCode,
                                             std::shared_ptr<uint8_t> pMem, void *pClbParam)> pFunction,
                          void *pClbParam);

    bool    MemAlloc();
    void    FreeMemory(std::shared_ptr<uint8_t> pMem);

    bool    ProcessRecvData();
    EL2RecvAction OnRecvFrame();
    bool    IsSendReady();
    bool    RunSendFrame();
    void    FireEvent(EL2Event event);

    void    InitL1TimeOutTimer();
    void    StartL1TimeOutTimer(uint32_t time);
    void    StopL1TimeOutTimer();

    static void Clb_L1SendDone(void* pParam);
    static void Clb_L1RecvData(void* pParam);
    static void Clb_L1SendTimeOut(uint32_t time, void *pParam);

public:
     /* MAC SECTION */
    bool    Mac_Start(std::string portname, int baudrate, uint8_t myId);

    bool    Mac_SendDataLater(uint8_t dest, uint8_t ctrl, uint8_t *data, uint8_t dlen);
    bool    Mac_SendDataImmediate(uint8_t dest, uint8_t ctrl, uint8_t *data, uint8_t dlen);
    bool    Send(uint8_t *data, uint8_t dlen);

    void    Mac_Stop();
    void    Mac_SetMyId(uint8_t myId);
    void    Mac_SetDstId(uint8_t dstId);
    void    Mac_RegisterClbEvent(Layer2::MACEvent event,
                                  std::function<void(std::shared_ptr<uint8_t> pMem, void *pClbParam)> pFunction,
                                  void *pParam);
    bool    Mac_GetStatus() const ;

private:

    bool    Mac_sendLater(uint8_t dest, uint8_t ctrl, uint8_t *data, uint8_t dlen, EPackageType type);
    bool    Mac_sendImmediate(uint8_t dest, uint8_t ctrl, uint8_t *data, uint8_t dlen, EPackageType type);
    static  void Clb_UpdateTimer(uint32_t time, void* pParam);

    void    Mac_SendTask();
    void    Mac_RecvTask();

    std::shared_ptr<uint8_t> Mac_PopHead(std::list<std::shared_ptr<uint8_t>> &usrList);
    std::shared_ptr<uint8_t> Mac_SearchAndPop(std::list<std::shared_ptr<uint8_t>> &usrList, uint8_t seq);

    void    Mac_StartThread();
    void    Mac_OwnerThread();

    static void Mac_ClbRecvData(EL2Event eEventCode, std::shared_ptr<uint8_t> pMem, void *pClbParam);
    static void Mac_ClbSentData(EL2Event eEventCode, std::shared_ptr<uint8_t> pMem, void *pClbParam);
    static void Mac_ClbErr(EL2Event eEventCode, std::shared_ptr<uint8_t> pMem, void *pClbParam);
    void        Mac_CheckTimeOutOfSentFrame();

    /* INTERFACE SECTION */
    std::shared_ptr<Layer1>     m_L1;
    std::shared_ptr<Timer>      m_Timer;
    std::string m_portname;
    int         m_baudrate;

    uint32_t    m_recvCount;
    uint32_t    m_recvDlen;
    uint8_t     m_seqError;
    bool        m_isError;
    uint8_t     m_seqRemote;
    uint8_t     m_seqLocal;
    uint8_t     m_seqCMDfrm;

    std::shared_ptr<uint8_t>    m_memRecv;
    std::shared_ptr<uint8_t>    m_memSend;

    uint8_t     *frmRecv;
    uint8_t     *frmSend;

    uint8_t     m_myId;
    uint8_t     m_dstId;

    uint8_t     m_errCode;

    uint32_t    L1SendTimeout;

    std::function<void(EL2Event eEventCode, std::shared_ptr<uint8_t> pMem, void *pClbParam)> m_fRecvData;
    std::function<void(EL2Event eEventCode, std::shared_ptr<uint8_t> pMem, void *pClbParam)> m_fSentData;
    std::function<void(EL2Event eEventCode, std::shared_ptr<uint8_t> pMem, void *pClbParam)> m_fError;
    std::function<void(MACEvent evt)>              m_notify;

    void        *m_recvEvtParam;
    void        *m_sendEvtParam;
    void        *m_errorEvtParam;

    L2Flag      m_flag;


    SCV         *m_Cv;

    void        *hL1TrackingTimer;
    uint32_t    m_l1TimeTrackValue;


    /* MAC SECTION */
    std::mutex          m_lsendingDataMutex;
    std::mutex          m_lsentDataMutex;
    std::mutex          m_lsendingCmdMutex;

    std::list<std::shared_ptr<uint8_t>> m_listSendingData;
    std::list<std::shared_ptr<uint8_t>> m_listSendingCmd;
    std::list<std::shared_ptr<uint8_t>> m_listSentData;

    std::thread m_ownerThread;
    bool        m_ownerThreadTerm;
    void        *m_hUpdateTimer;

    std::function<void(std::shared_ptr<uint8_t> pMem, void *pClbParam)> m_fMacRevData;
    std::function<void(std::shared_ptr<uint8_t> pMem, void *pClbParam)> m_fMacSentData;
    std::function<void(std::shared_ptr<uint8_t> pMem, void *pClbParam)> m_fMacError;

    void        *m_macRecvParam;
    void        *m_macSentParam;
    void        *m_macErrorParam;

    SCV         m_hSync;

    /* For simple transceiver use */
    uint8_t				RecvBufProcess[DEFAULT_SIZE_RECV_BUF];
    bool                RecFrmDone;
    std::function<void(uint8_t *data, uint32_t len, void *pClbParam)>        m_fSimpleRecvEvent;
    void                *pSimpleClbParam;

    MACEvent        m_status;

};
}}
#endif // LAYER2_H
