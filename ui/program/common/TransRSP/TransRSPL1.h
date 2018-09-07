#ifndef TRANSRSPL1_H
#define TRANSRSPL1_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>
#include "../GeneralLib/QRingBuffer.h"
#include "TransRSPCommon.h"

#define TRANS_RSP_L1_RBUFF_MAX_SIZE         RSP_FRM_MAX_SIZE * 32
#define TRANS_RSP_L1_SEND_TIMEOUT_MS        100
#define TRANS_RSP_L1_WAIT_ACK_TIMEOUT_MS    500
#define TRANS_RSP_L1_WAIT_ACK_STEP_MS       10

#define TRANS_RSP_L1_MAX_RETRY              4

#define TRANS_RSP_L1_DEBUG_ENABLE       0

// Error enumeration
typedef enum
{
    ERR_TRANSL1_NO_ERROR = 10,

    // Error found on Layer 1
    ERR_TRANSL1_RX_BUFFER_PUSH_FAILED,
    ERR_TRANSL1_RX_PAP0_BUFFER_PUSH_FAILED,
    ERR_TRANSL1_RX_PAP1_BUFFER_PUSH_FAILED,
    ERR_TRANSL1_RX_PAPID_INVALID,
    ERR_TRANSL1_TX_BUFFER_PUSH_FAILED,
    ERR_TRANSL1_INVALID_PREAMBLE,
    ERR_TRANSL1_CRCH,
    ERR_TRANSL1_UART_FRAME_ERROR,
    ERR_TRANSL1_UART_OVERRUN,
    ERR_TRANSL1_BUSY,
    ERR_TRANSL1_PARAM_INVALID,
    ERR_TRANSL1_SEND_ERROR,


}	EL1ErrorCode;

class TransRSPL1 : public QObject
{
    Q_OBJECT
public:
    explicit        TransRSPL1(QObject *parent = 0);
    ~TransRSPL1();


    int            TransRSPL1Init(QString szPortName, uint32_t nBaudRate);
    int            TransRSPL1DeInit();
    int            TransRSPL1IsConnected() {return bIsConnected;}


    int 			TransRSPL1BufferPush(void* pvData) {return psTransL1RXBuffer->BufferPush(pvData);}
    uint8_t         TransRSPL1BufferPop() {uint8_t u8popData; psTransL1RXBuffer->BufferPop(&u8popData); return u8popData;}
    int 			TransRSPL1BufferPushStream(void* pvStream, uint16_t u16Length) {return psTransL1RXBuffer->BufferPushStream(pvStream, u16Length);}
    uint16_t        TransRSPL1BufferPopStream(void* pvStream, uint16_t u16Length) {return psTransL1RXBuffer->BufferPopStream(pvStream, u16Length);}

    int			TransRSPL1BufferPushBack(uint16_t u16PushBackNumber) {return psTransL1RXBuffer->BufferPushBack(u16PushBackNumber);}
    uint16_t        TransRSPL1BufferGetCount() {return psTransL1RXBuffer->BufferGetCount();}
    uint16_t        TransRSPL1BufferGetAvailableCount() {return psTransL1RXBuffer->BufferGetAvailableCount();}
    void 			TransRSPL1BufferFlush() {psTransL1RXBuffer->BufferFlush();}

    int            TransRSPL1IsReady2Send();
    uint16_t        TransRSPL1Send2Device(uint8_t* pucData, uint16_t uiDataLength);

    uint64_t        ulL1StartSendTime;
    uint64_t        ulL1SendTimeout;
    int            bIsSending;
    uint8_t         u8Error;


    QRingBuffer*        psTransL1RXBuffer;
    QSerialPort*        pDevice;
    QThread*            pThreadTransRSPL2Notify;
    QWaitCondition*     pWaitDataReceived;
    QMutex              mutex;

private:
    void                vTaskNotifyTransRSPL2();
    int                bIsConnected;
    uint8_t             u8L2Response;
signals:
    void                onSendDone(uint16_t nByteSent);
    void                onDataReceived(TransRSPL1* pTransRSPL1Object);
public slots:
    void                onReadyRead();
    void                onTransRSPL2FrameReceived(uint8_t* pRSPFrame);
};

#endif // TRANSRSPL1_H
