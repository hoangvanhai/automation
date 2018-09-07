#include "TransRSPL1.h"
#include <QCoreApplication>

TransRSPL1::TransRSPL1(QObject *parent) : QObject(parent)
{
    pDevice = new QSerialPort;
    psTransL1RXBuffer = new QRingBuffer;
    bIsSending = FALSE;
    u8Error = 0;
}

TransRSPL1::~TransRSPL1()
{
    if(pDevice)
    {
//        disconnect(pDevice, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
//        pDevice->disconnect();
        pDevice->close();
    }
}


// ---------------------------------------------------------------------------------------------------
//	@brief	: 	Initialize the TransRSPL1 layer
//
//	@param	: 	pIODevice - pointer to QIODevice
//	@return	: 	void
//	@note	:
// ---------------------------------------------------------------------------------------------------
int TransRSPL1::TransRSPL1Init(QString szPortName, uint32_t nBaudRate)
{
    bIsConnected = FALSE;
    u8Error               = ERR_TRANSL1_NO_ERROR;
    ulL1StartSendTime       = 0;
    ulL1SendTimeout 		= TRANS_RSP_L1_SEND_TIMEOUT_MS;

    pThreadTransRSPL2Notify  = new QThread;
    pWaitDataReceived = new QWaitCondition;


    pDevice->setPortName(szPortName);
    pDevice->setBaudRate(nBaudRate);
    // Init ring buffer to storage maximum 32 RSP Frame
    psTransL1RXBuffer->BufferInit(TRANS_RSP_L1_RBUFF_MAX_SIZE, NULL, NULL);
    connect(pDevice, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    if( pDevice->open(QIODevice::ReadWrite))
    {
        bIsConnected = TRUE;
        return TRUE;
    }
   return FALSE;

//    connect(pThreadTransRSPL2Notify, SIGNAL(started()), this, vTaskNotifyTransRSPL2());

//    pThreadTransRSPL2Notify->start();
}

int TransRSPL1::TransRSPL1DeInit()
{
    if( pDevice->isOpen())
    {
        pDevice->close();
        bIsConnected = FALSE;
        return TRUE;
    }
    return FALSE;
}

// ---------------------------------------------------------------------------------------------------
//	@brief	: 	Check if the Layer 1 is ready to send or not
//
//	@param	: 	None
//	@return	: 	void
//	@note	:
// ---------------------------------------------------------------------------------------------------
int TransRSPL1::TransRSPL1IsReady2Send()
{
    return (int)(bIsSending == FALSE);
}

void TransRSPL1::vTaskNotifyTransRSPL2()
{
    while (true)
    {
        mutex.lock();
            pWaitDataReceived->wait(&mutex);
        mutex.unlock();

        //Wait until have a signal

        //Notify Receive Message to L2
        if (psTransL1RXBuffer->BufferGetCount() > 0)
        {
//            _handleRecvData.OnMessageReceived(_bytesReceived);
            emit onDataReceived(this);
        }
    }
}

// Slots
// ---------------------------------------------------------------------------------------------------
//	@brief	: 	Data received event handler
//  @name   :   onReadyRead
//	@param	: 	None
//	@return	: 	void
//	@note	:
// ---------------------------------------------------------------------------------------------------
void TransRSPL1::onReadyRead()
{
    QByteArray arr =  pDevice->readAll();
#if (TRANS_RSP_L1_DEBUG_ENABLE > 0)
    qDebug() << "[DBG-L1]Rcv data: " << arr.toHex();
#endif
    psTransL1RXBuffer->BufferPushStream((void*)arr.data(), arr.size());
    // Notify to the TransRSPL2
   emit onDataReceived(this);
//    mutex.lock();
//    pWaitDataReceived->wakeAll();
//    mutex.unlock();
}

// ---------------------------------------------------------------------------------------------------
//	@brief	: 	Send Data to the hardware
//  @name   :   TransRSPL1Send2Device
//	@param	: 	pucData - pointer to the RSP Frame
//  @param  :   uiDataLength - total length of data will be sent to hardware
//	@return	: 	uint16_t - number of sent byte
//	@note	:
// ---------------------------------------------------------------------------------------------------
uint16_t TransRSPL1::TransRSPL1Send2Device(uint8_t* pucData, uint16_t uiDataLength)
{
    int16_t nByteSent = -1;

//    if(bIsSending == TRUE)
//    {
//        return ERR_TRANSL1_BUSY;
//    }

    if(pucData == NULL || uiDataLength <= 0)
    {
        return ERR_TRANSL1_PARAM_INVALID;
    }

//    bIsSending = TRUE;

    // ACK required
    if(IS_ACK_REQ(pucData[RSP_FRM_IDX_FLAGS]))
    {
        uint8_t nRetry = 0;
        u8L2Response = RSP_CMD_NONE;
        while((nRetry < (TRANS_RSP_L1_MAX_RETRY * (TRANS_RSP_L1_WAIT_ACK_TIMEOUT_MS / TRANS_RSP_L1_WAIT_ACK_STEP_MS)))
              && (!IS_ACK_FRAME(u8L2Response)) && (!IS_NACK_FRAME(u8L2Response)))
        {
            if(nRetry %((TRANS_RSP_L1_WAIT_ACK_TIMEOUT_MS / TRANS_RSP_L1_WAIT_ACK_STEP_MS)) == 0)
            {
                nByteSent = pDevice->write((char*)pucData, uiDataLength);
                if (!pDevice->waitForBytesWritten(TRANS_RSP_L1_SEND_TIMEOUT_MS))
                {

                    nByteSent = -1;
                }
            }

            // Wait for response form slave            
            if(pDevice->waitForReadyRead(TRANS_RSP_L1_WAIT_ACK_STEP_MS))
                qDebug() << "[DBG-L1] ACK received!";

            nRetry ++;
        }

        emit onSendDone(nByteSent);
        if((nByteSent > 0) && (IS_ACK_FRAME(u8L2Response)))
        {
            return ERR_TRANSL1_NO_ERROR;
        }

        u8L2Response = RSP_CMD_NONE;

        return ERR_TRANSL1_SEND_ERROR;

    }

    // ACK is not required
    else
    {
        nByteSent = pDevice->write((char*)pucData, uiDataLength);
        if (!pDevice->waitForBytesWritten(TRANS_RSP_L1_SEND_TIMEOUT_MS))
        {
            nByteSent = -1;
        }
        emit onSendDone(nByteSent);

        if(nByteSent <= 0)
            return ERR_TRANSL1_SEND_ERROR;

        return ERR_TRANSL1_NO_ERROR;
    }

}


void TransRSPL1::onTransRSPL2FrameReceived(uint8_t *pRSPFrame)
{
    u8L2Response = pRSPFrame[RSP_FRM_IDX_FLAGS];
#if TRANS_RSP_L1_DEBUG_ENABLE
    qDebug() << "[DBG-L1]Response from L2: " << u8L2Response;
#endif
}

