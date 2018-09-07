#include "TransRSPL2.h"
#include <QDebug>
#include "isc/crc8.h"

TransRSPL2::TransRSPL2(QObject *parent) : QObject(parent)
{

}

TransRSPL2::~TransRSPL2()
{
    if(pTransRSPL1Instance)
    {
//        pTransRSPL1Instance->disconnect();
//        disconnect(pTransRSPL1Instance, SIGNAL(onDataReceived(TransRSPL1*)), this, SLOT(onTransRSPL1DataReceived(TransRSPL1*)));
        delete pTransRSPL1Instance;
    }
}

int TransRSPL2::TransRSPL2Init(QString szPortName, uint32_t nBaudRate)
{
    bIsConnected    = FALSE;
    u16MyAddr       = RSP_ADDR_PC;
    pTransRSPL1Instance = new TransRSPL1;
    connect(pTransRSPL1Instance, SIGNAL(onDataReceived(TransRSPL1*)), this, SLOT(onTransRSPL1DataReceived(TransRSPL1*)));
    connect(this, SIGNAL(evtTransRSPL2FrameReceived(uint8_t*)), pTransRSPL1Instance, SLOT(onTransRSPL2FrameReceived(uint8_t*)));
    if (pTransRSPL1Instance->TransRSPL1Init(szPortName, nBaudRate) == TRUE)
    {
        bIsConnected = TRUE;
        return TRUE;
    }

    return FALSE;
    // TODO: Add TransISCL2OnL2SendDone and register to the Layer1
}

int TransRSPL2::TransRSPL2DeInit()
{
    if(pTransRSPL1Instance->TransRSPL1IsConnected() && pTransRSPL1Instance->TransRSPL1DeInit())
    {
        bIsConnected = FALSE;
        return TRUE;
    }
    return FALSE;
}


void   TransRSPL2::onTransRSPL1DataReceived(TransRSPL1* pTransRSPL1Item)
{
    if (TransRSPL2ProcessRecvData(pTransRSPL1Item))
    {
        TransRSPL2ProcessRecvFrame();
    }
}


int TransRSPL2::TransRSPL2ProcessRecvData(TransRSPL1* pTransRSPL1Item)
{
    static int			bIsSearchingHeader	= TRUE;
    QRingBuffer* 		pBuff 				= pTransRSPL1Item->psTransL1RXBuffer;
    unsigned char		ucHeaderCRC;
    unsigned char*		pucRecvFrame		= pu8RxTempBuff;
    unsigned char*		pucRecvData			= &pucRecvFrame[RSP_FRM_IDX_DATA0];
    static unsigned int	uiRecvDataCount		= 0;

    unsigned char 		ucTmp 				= 0;
    uint16_t			u16Dlen				= 0;

    while(pBuff->BufferGetCount() > 0)
    {
        // Layer 2 Starts processing received data from Layer 1 by searching Header
        if(bIsSearchingHeader)
        {
            // Start receiving only if received at least a header
            if(pBuff->BufferGetCount() < RSP_FRM_HDR_SIZE)
            {
                break;
            }

            // search for RSP_SOF
            pBuff->BufferPop(&ucTmp);
            // Seek for a valid preamble
            if(ucTmp != RSP_SOF_PREAMBLE)
            {
                continue;	// Keep looking for a valid preamble
            }
            pBuff->BufferPop(&ucTmp);
            if(ucTmp != RSP_SOF_PREAMBLE)
            {
                continue;
            }

            // Found 2 continous byte seems to be a RSP_SOF

            // Try to get a full header for checking a valid one
            pBuff->BufferPopStream( &pucRecvFrame[2], RSP_FRM_HDR_SIZE-2);
            // Calculate CRC of received header
            ucHeaderCRC = CalCRC8(&pucRecvFrame[2], RSP_FRM_HDR_SIZE-3);

            // Checking CRC is correct or not
            if(ucHeaderCRC != pucRecvFrame[RSP_FRM_IDX_CRCH])
            {
                // If CRC is not matched, this header is invalid, we need to push back taken out bytes to
                // the received buffer to continuously search preamble at the position right after above preamble
                if (!pBuff->BufferPushBack(RSP_FRM_HDR_SIZE))
                {
//					LREPFast("\r\nL1 cannot push back");
//                    DBG_PutString("\r\nL1 cannot push back");
                }


                continue;	// Keep looking for a valid preamble
            }

            // CRC matched means we already got a valid header.

            // Check the data length for getting data field.
            // If data length is zero, this frame is command then return immediately
            // If there is data field then switch the machine to "Search Data" state
            u16Dlen = *(uint16_t*)&pucRecvFrame[RSP_FRM_IDX_DLEN];
            if( u16Dlen != 0)
            {
                bIsSearchingHeader = FALSE;

                continue;	// Continue to get data field
            }

            // Frame has no data in the case of command frame
            return TRUE;

        }		// End of searching header
        else	// Start getting data field
        {
            unsigned int uiPopLength = pBuff->BufferGetCount();

            // Limit, if the receive buffer count is greater than data length of this frame then we just
            // get enough data byte for it
            if (uiPopLength > (*(uint16_t*)&pucRecvFrame[RSP_FRM_IDX_DLEN]- uiRecvDataCount + 2))
            {
                uiPopLength = *(uint16_t*)&pucRecvFrame[RSP_FRM_IDX_DLEN] - uiRecvDataCount + 2;
            }

            // Correct the position of the data receiving pointer
            pucRecvData = &pucRecvFrame[RSP_FRM_IDX_DATA0 + uiRecvDataCount];

            // Pop out data bytes from TransL1 RX buffer & store into TransL2 RX Frame
//            BufferPopStream(pBuff, pucRecvData, uiPopLength);
            pBuff->BufferPopStream(pucRecvData, uiPopLength);
            // Count up the number of received data for the current frame
            uiRecvDataCount += uiPopLength;

            // If we didn't get enough data bytes, continue to check, do not switch to "Search header" state & return TRUE
            if (uiRecvDataCount < *(uint16_t*)&pucRecvFrame[RSP_FRM_IDX_DLEN])
            {
                continue;
            }

            // Got a complete frame then switch the machine to "Search Header" state
            bIsSearchingHeader	= TRUE;
            uiRecvDataCount		= 0;

            return TRUE;
        }	// End of getting data

    }	// End of while loop

    return FALSE;
}

void TransRSPL2::TransRSPL2ProcessRecvFrame()
{
    unsigned char* 	pucRecvFrame	= pu8RxTempBuff;
    unsigned char* 	pucRecvData		= &pucRecvFrame[RSP_FRM_IDX_DATA0];
    uint16_t        u16DstAddr     = *(uint16_t*)&pucRecvFrame[RSP_FRM_IDX_DSTADDR];

//	// Validate destination address
    if (u16DstAddr != u16MyAddr)
    {
        qDebug() << "u16DstAddr: " << u16DstAddr << ", u16NodeID:" << u16MyAddr;
        return;
    }

    // Validate data length
    if ((*(uint16_t*)&pucRecvFrame[RSP_FRM_IDX_DLEN] > RSP_FRM_DATA_MAX_SIZE) && (*(uint16_t*)&pucRecvFrame[RSP_FRM_IDX_DSTADDR] != RSP_ADDR_BROADCAST))
    {
        if (IS_ACK_REQ(pucRecvFrame[RSP_FRM_IDX_FLAGS]) && (*(uint16_t*)&pucRecvFrame[RSP_FRM_IDX_DSTADDR] != RSP_ADDR_BROADCAST))
        {
            // Fire event to upper layer to add NACK frame to queue
            TransRSPL2ProcessEvent(ERR_TRANSL2_INVALID_DLEN);

            qDebug() << "Invalid DLEN!";
        }

        return;
    }
#if TRANS_RSP_L2_DEBUG_ENABLE
    QString msg;
    msg.sprintf("[DBG-L2]Calculate CRC_D, rcv: %.2x, cal: %.2x\r\n",
                    pucRecvFrame[*(uint16_t*)&pucRecvFrame[RSP_FRM_IDX_DLEN] + RSP_FRM_HDR_SIZE],
                    CalCRC8(pucRecvData, *(uint16_t*)&pucRecvFrame[RSP_FRM_IDX_DLEN]));

    qDebug() << msg;

#endif
    // Check CRC for data
    if (	(*(uint16_t*)&pucRecvFrame[RSP_FRM_IDX_DLEN] != 0) &&
            (pucRecvFrame[*(uint16_t*)&pucRecvFrame[RSP_FRM_IDX_DLEN] + RSP_FRM_HDR_SIZE] != CalCRC8(pucRecvData, *(uint16_t*)&pucRecvFrame[RSP_FRM_IDX_DLEN])))
    {
        TransRSPL2ProcessEvent(ERR_TRANSL2_INVALID_CRC_D);
#if TRANS_RSP_L2_DEBUG_ENABLE
        qDebug() << "Invalid CRC_D";
#endif
        // Wrong CRC --> Send NACK
        if( IS_ACK_REQ(pucRecvFrame[RSP_FRM_IDX_FLAGS]) && (*(uint16_t*)&pucRecvFrame[RSP_FRM_IDX_DSTADDR] != RSP_ADDR_BROADCAST))
        {
            // Fire event to upper layer to add NACK frame to queue
//            TransRSPL2SendNack();
        }

        return;
    }
    pucRecvFrame[0] = pucRecvFrame[1] = RSP_SOF_PREAMBLE;
    emit evtTransRSPL2FrameReceived(pucRecvFrame);

    if( IS_ACK_REQ(pucRecvFrame[RSP_FRM_IDX_FLAGS]) && (*(uint16_t*)&pucRecvFrame[RSP_FRM_IDX_DSTADDR] != RSP_ADDR_BROADCAST))
    {
        // Send ACK to notify sender
        TransRSPL2SendAck();
    }

    if(IS_ACK_FRAME(pucRecvFrame[RSP_FRM_IDX_FLAGS]))
    {
//        emit evtTransRSPL2AckFrameReceived();
    }

    if(IS_NACK_FRAME(pucRecvFrame[RSP_FRM_IDX_FLAGS]))
    {
//        emit evtTransRSPL2AckFrameReceived();
    }



//    // Process DATA frame
//    if (IS_DATA_FRM(pucRecvFrame[RSP_FRM_IDX_FLAGS]))
//    {

//        //TODO: [manhbt] Foward this data to CAN bus
////		DBG_PutString("[manhbt] Foward this data to CAN bus\r\n");
////        TransRSPProcessDataPacket();

//#if TRANS_RSP_L2_DEBUG_ENABLE
//        qDebug() << "[manhbt] Foward this data to CAN bus";
//#endif

//    }

//    // Process COMMAND frame
//    else if(IS_CMD_FRM(pucRecvFrame[RSP_FRM_IDX_FLAGS]))
//    {

//        //TODO: [manhbt] This is a configuration packet, will update this config now;
////		DBG_PutString("[manhbt] This is a configuration packet\r\n");
////		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
////        TransRSPProcessCommandPacket();
//#if TRANS_RSP_L2_DEBUG_ENABLE
//        qDebug() << "[manhbt] This is a configuration packet";
//#endif

//    }

}

void           TransRSPL2::TransRSPL2ProcessEvent(uint8_t u8EventCode)
{

}

#if 0
int    TransRSPL2::TransRSPL2Send(uint8_t u8Ctrl, uint8_t *pu8Data, uint16_t u16Len)
{
    uint8_t* pu8RSPFrame = new uint8_t[RSP_FRM_HDR_SIZE + u16Len + 1];
    if(pu8RSPFrame == NULL)
    {
        qDebug() << "Cannot allocate memory for RSP Frame!";
        return FALSE;
    }
    TransRSPFrame frameData;
    //clsMsg tmpMsg              = message as clsMsg;
    frameData.u16Preamble      = RSP_SOF_VALUE;
    frameData.u16Dlen          = u16Len;
    frameData.u8Flags          = u8Ctrl;
    frameData.u16DstAddr       = RSP_ADDR_PC;
    frameData.u16SrcAddr       = RSP_ADDR_PC;

//    frameData.pu8DataPayload   = new uint8_t[u16Dlen];
//    memcpy(frameData.pu8DataPayload, pu8Data, u16Dlen);
//    free(pu8Data);

    frameData.u8CRC_D           = CalCRC8(pu8Data, u16Len);
    frameData.u8CRC_H           = CalCRC8((uint8_t*)&frameData + RSP_FRM_IDX_DLEN, RSP_FRM_HDR_SIZE - 3 );
    pu8RSPFrame[RSP_FRM_IDX_DATA0+u16Len] = frameData.u8CRC_D;
    memcpy(pu8RSPFrame, (uint8_t*)&frameData, RSP_FRM_HDR_SIZE);
    memcpy((uint8_t*)&pu8RSPFrame[RSP_FRM_IDX_DATA0], pu8Data, u16Len);

    if(pTransRSPL1Instance->TransRSPL1Send2Device(pu8RSPFrame, RSP_FRM_HDR_SIZE+u16Len+1) != ERR_TRANSL1_NO_ERROR )
    {
        qDebug() << "L1 send Error!";
        return FALSE;
    }
    return TRUE;

}
#endif

int    TransRSPL2::TransRSPL2SendAck()
{
    uint8_t* pu8RSPFrame = new uint8_t[RSP_FRM_HDR_SIZE + 1];
    if(pu8RSPFrame == NULL)
    {
        qDebug() << "Cannot allocate memory for RSP Frame!";
        return FALSE;
    }
    TransRSPFrame frameData;
    //clsMsg tmpMsg              = message as clsMsg;
    frameData.u16Preamble      = RSP_SOF_VALUE;
    frameData.u16Dlen          = 0;
    frameData.u8Flags          = RSP_FRM_TYPE_CMD |  RSP_CMD_ACK;
    frameData.u16DstAddr       = RSP_ADDR_PC;
    frameData.u16SrcAddr       = u16MyAddr;

    frameData.u8CRC_D           = CalCRC8(nullptr, 0);
    frameData.u8CRC_H           = CalCRC8((uint8_t*)&frameData + RSP_FRM_IDX_DLEN, RSP_FRM_HDR_SIZE - 3 );

    pu8RSPFrame[RSP_FRM_IDX_DATA0] = frameData.u8CRC_D;
    memcpy(pu8RSPFrame, (uint8_t*)&frameData, RSP_FRM_HDR_SIZE);


    if(pTransRSPL1Instance->TransRSPL1Send2Device(pu8RSPFrame, RSP_FRM_HDR_SIZE+1) != ERR_TRANSL1_NO_ERROR )
    {
        qDebug() << "SendACK: L1 send Error!";
        return FALSE;
    }
    return TRUE;

}

int    TransRSPL2::TransRSPL2SendNack()
{
    uint8_t* pu8RSPFrame = new uint8_t[RSP_FRM_HDR_SIZE + 1];
    if(pu8RSPFrame == NULL)
    {
        qDebug() << "Cannot allocate memory for RSP Frame!";
        return FALSE;
    }
    TransRSPFrame frameData;
    //clsMsg tmpMsg              = message as clsMsg;
    frameData.u16Preamble      = RSP_SOF_VALUE;
    frameData.u16Dlen          = 0;
    frameData.u8Flags          = RSP_FRM_TYPE_CMD |  RSP_CMD_NACK;
    frameData.u16DstAddr       = RSP_ADDR_PC;
    frameData.u16SrcAddr       = u16MyAddr;

    frameData.u8CRC_D           = CalCRC8(nullptr, 0);
    frameData.u8CRC_H           = CalCRC8((uint8_t*)&frameData + RSP_FRM_IDX_DLEN, RSP_FRM_HDR_SIZE - 3 );

    pu8RSPFrame[RSP_FRM_IDX_DATA0] = frameData.u8CRC_D;
    memcpy(pu8RSPFrame, (uint8_t*)&frameData, RSP_FRM_HDR_SIZE);


    if(pTransRSPL1Instance->TransRSPL1Send2Device(pu8RSPFrame, RSP_FRM_HDR_SIZE+1) != ERR_TRANSL1_NO_ERROR )
    {
        qDebug() << "SendNACK: L1 send Error!";
        return FALSE;
    }
    return TRUE;

}

int    TransRSPL2::TransRSPL2SendCmd(uint8_t *pu8Data, uint16_t u16Len, int bAckRequired)
{
    uint8_t* pu8RSPFrame = new uint8_t[RSP_FRM_HDR_SIZE + u16Len + 1];
    if(pu8RSPFrame == NULL)
    {
        qDebug() << "Cannot allocate memory for RSP Frame!";
        return FALSE;
    }
    TransRSPFrame frameData;
    //clsMsg tmpMsg              = message as clsMsg;
    frameData.u16Preamble      = RSP_SOF_VALUE;
    frameData.u16Dlen          = u16Len;
    frameData.u8Flags          = RSP_FRM_TYPE_CMD | ( bAckRequired ? RSP_FRM_ACKREQ_REQUIRED : RSP_FRM_ACKREQ_NOT_REQUIRED);
    frameData.u16DstAddr       = RSP_ADDR_PC;
    frameData.u16SrcAddr       = u16MyAddr;

    frameData.u8CRC_D           = CalCRC8(pu8Data, u16Len);
    frameData.u8CRC_H           = CalCRC8((uint8_t*)&frameData + RSP_FRM_IDX_DLEN, RSP_FRM_HDR_SIZE - 3 );
    pu8RSPFrame[RSP_FRM_IDX_DATA0+u16Len] = frameData.u8CRC_D;
    memcpy(pu8RSPFrame, (uint8_t*)&frameData, RSP_FRM_HDR_SIZE);
    memcpy((uint8_t*)&pu8RSPFrame[RSP_FRM_IDX_DATA0], pu8Data, u16Len);

    if(pTransRSPL1Instance->TransRSPL1Send2Device(pu8RSPFrame, RSP_FRM_HDR_SIZE+u16Len+1) != ERR_TRANSL1_NO_ERROR )
    {
        qDebug() << "SendCMD: L1 send Error!";
        return FALSE;
    }
    return TRUE;

}

int    TransRSPL2::TransRSPL2SendData(uint8_t *pu8Data, uint16_t u16Len, int bAckRequired)
{
    uint8_t* pu8RSPFrame = new uint8_t[RSP_FRM_HDR_SIZE + u16Len + 1];
    if(pu8RSPFrame == NULL)
    {
        qDebug() << "Cannot allocate memory for RSP Frame!";
        return FALSE;
    }
    TransRSPFrame frameData;
    //clsMsg tmpMsg              = message as clsMsg;
    frameData.u16Preamble      = RSP_SOF_VALUE;
    frameData.u16Dlen          = u16Len;
    frameData.u8Flags          = RSP_FRM_TYPE_DATA| ( bAckRequired ? RSP_FRM_ACKREQ_REQUIRED : RSP_FRM_ACKREQ_NOT_REQUIRED);
    frameData.u16DstAddr       = RSP_ADDR_PC;
    frameData.u16SrcAddr       = u16MyAddr;

    frameData.u8CRC_D           = CalCRC8(pu8Data, u16Len);
    frameData.u8CRC_H           = CalCRC8((uint8_t*)&frameData + RSP_FRM_IDX_DLEN, RSP_FRM_HDR_SIZE - 3 );
    pu8RSPFrame[RSP_FRM_IDX_DATA0+u16Len] = frameData.u8CRC_D;
    memcpy(pu8RSPFrame, (uint8_t*)&frameData, RSP_FRM_HDR_SIZE);
    memcpy((uint8_t*)&pu8RSPFrame[RSP_FRM_IDX_DATA0], pu8Data, u16Len);

    if(pTransRSPL1Instance->TransRSPL1Send2Device(pu8RSPFrame, RSP_FRM_HDR_SIZE+u16Len+1) != ERR_TRANSL1_NO_ERROR )
    {
        qDebug() << "SendData: L1 send Error!";
        return FALSE;
    }
    return TRUE;

}

uint8_t* TransRSPL2::EncodeRSPFrame(uint8_t u8Flags, uint16_t u16DstAddr, uint16_t u16SrcAddr, uint8_t* pu8Data, uint16_t u16Dlen)
{
    uint8_t* pu8RSPEncodedFrame = (uint8_t*)malloc(RSP_FRM_HDR_SIZE+u16Dlen+1);

//    pu8

    TransRSPFrame frameData;
    //clsMsg tmpMsg              = message as clsMsg;
    frameData.u16Preamble      = RSP_SOF_VALUE;
    frameData.u16Dlen          = u16Dlen;
    frameData.u8Flags          = u8Flags;
    frameData.u16DstAddr       = u16DstAddr;
    frameData.u16SrcAddr       = u16SrcAddr;

//    frameData.pu8DataPayload   = new uint8_t[u16Dlen];
//    memcpy(frameData.pu8DataPayload, pu8Data, u16Dlen);
//    free(pu8Data);

    frameData.u8CRC_D           = CalCRC8(pu8Data, u16Dlen);
    frameData.u8CRC_H           = CalCRC8((uint8_t*)&frameData + RSP_FRM_IDX_DLEN, RSP_FRM_HDR_SIZE - 3 );

    return pu8RSPEncodedFrame;
}
// Decode Frame
TransRSPFrame TransRSPL2::DecodeRSPFrame(uint8_t* pu8Frame)
{
    TransRSPFrame frameData;
    return frameData;
}


