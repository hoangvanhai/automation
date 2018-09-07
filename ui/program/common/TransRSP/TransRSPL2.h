#ifndef TRANSRSPL2_H
#define TRANSRSPL2_H

#include "TransRSPL1.h"

#define TRANS_RSP_L2_DEBUG_ENABLE       0


typedef enum
{
    ERR_TRANSL2_NO_ERROR = 10,

    ERR_TRANSL2_INVALID_DLEN,
    ERR_TRANSL2_INVALID_CRC_D



}	EL2ErrorCode;

class TransRSPL2 : public QObject
{
    Q_OBJECT
public:
    explicit        TransRSPL2(QObject *parent = 0);
    ~TransRSPL2();
    int            TransRSPL2Init(QString szPortName, uint32_t nBaudRate);
    int            TransRSPL2DeInit();

    TransRSPL1      *pTransRSPL1Instance;

    int            TransRSPL2SendCmd(uint8_t* pu8Data, uint16_t u16Len, int bAckRequired);
    int            TransRSPL2SendData(uint8_t* pu8Data, uint16_t u16Len, int bAckRequired);
    int            TransRSPL2SendAck();
    int            TransRSPL2SendNack();

    int            TransRSPL2IsConnected() {return bIsConnected;}
private:
    uint8_t         pu8RxTempBuff[RSP_FRM_MAX_SIZE];
    uint8_t         pu8TxTempBuff[RSP_FRM_MAX_SIZE];

    //Encode Frame
    uint8_t*        EncodeRSPFrame(uint8_t u8Flags, uint16_t u16DstAddr, uint16_t u16SrcAddr, uint8_t* pu8Data, uint16_t u16Dlen);
    // Decode Frame
    TransRSPFrame   DecodeRSPFrame(uint8_t* pu8Frame);

    int            TransRSPL2ProcessRecvData(TransRSPL1* pTransRSPL1Item);
    void            TransRSPL2ProcessRecvFrame();
    void            TransRSPL2ProcessEvent(uint8_t u8EventCode);



    int            bIsConnected;

    uint16_t        u16MyAddr;
signals:
//    void            evtTransRSPL2DataReceived(TransRSPL1* pTransRSPL1Item);
    void            evtTransRSPL2FrameReceived(uint8_t* pu8RSPFrame);
    void            evtTransRSPL2AckFrameReceived();
    void            evtTransRSPL2NackFrameReceived();
public slots:
    void            onTransRSPL1DataReceived(TransRSPL1* pTransRSPL1Item);

};

#endif // TRANSRSPL2_H
