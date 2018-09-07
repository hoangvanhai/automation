#include "TcpProgWorker.h"
//#include "ui_mainwindow.h"

TcpProgWorker::TcpProgWorker() :
    QObject()
{
    m_bRunning = false;
    m_fPercent = 0.0;
    m_bStopped = false;

    u16RxCount = 0;
    u16RxLen = 5;
}

TcpProgWorker::~TcpProgWorker()
{
//    delete ui;
}

bool TcpProgWorker::isRunning() {
    //QMutexLocker locker(&m_Mutex);
    return m_bRunning;
}

void TcpProgWorker::stop()
{
    //qDebug()<<"VrecProg::stop is called from thread "<<QThread::currentThread();
    if (isRunning()) {
        //QMutexLocker locker(&m_Mutex);
        m_bStopped = true;

    }
}

void TcpProgWorker::process()
{
    qDebug()<<"process ";
    //////////////////////////////////////////////////////////////////////////////////////////////////
    if (!isRunning())
    {
        //m_Mutex.lock();
        m_bRunning = true;
        m_bStopped = false;
        //m_Mutex.unlock();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // is Running here check if m_bStopped then stop the programming
    // initialize finished code to emit before finsihed
    int                                         iFinishedCode = VREC_PROG_FINISH_PROG_ERR;
    // Programming target
    /* Load Vrec File */
    string                                      line;
    int                                         iLineIdx = 0;
    S_VREC_INFO                                 vrecInfo;
    vrecInfo.pu8Data = new uint8_t[512];
    uint32_t                                    dataSize;
    int                                         retDecode;
    uint16_t                                    u16NumberProgs;
    uint16_t                                    u16DeviceId;
    uint16_t                                    u16NodeId;
    uint32_t                                    u32HeaderLine;
    uint8_t                                     vrecBuf[1024];
    int                                         iDataLength = 0;
    int                                         iFrameLength;
    uint8_t                                     u8CRC;
    uint32_t                                    u32NVrecLines = 0;
    //iFrameLength = 6 + 2 * iDataLength;
    std::vector<string>                         vStrBootHooks;  ///< number of vrec line of each program
    std::string                                 strNodeSelect;
    std::vector<uint32_t>                       vu32HeaderLine;	///< line number of Header;
    std::vector<uint32_t>                       vu32VrecLens; 	///< number of vrec line of each program
    string                                      strBootHook;
    int                                         iHeader = 0;
    uint8_t u8Ret = BOOT_ERR_NONE;
    uint32_t u32ProgrammedNlines = 0; // number of program that has been programmed

    // local variables declaration/ opens
//    bool bSerialPortReady = false;
    bool bFileReady = false;
    // open tcp socket, connect to server
#if EW_DEBUG_ENABLE
    qDebug() << "[tcpProgWorker] " << "Server IP: " << m_szServerName;
    qDebug() << "[tcpProgWorker] " << "Server Port: " << m_nServerPort;
    qDebug() << "[tcpProgWorker] " << "File Path: " << m_szFileName;
#endif
    QTcpSocket* pSocket = new QTcpSocket();

    pSocket->connectToHost(m_szServerName, m_nServerPort);
    pSocket->waitForConnected(3000);

    if(this->m_FwdOpt) {
        qDebug("Use forwarder!!!");
        uint8_t ping_msg[] = {0x00, 0x00, 0x00, 0x08, 0x00, 0x0F, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01};
        pSocket->write((char*) ping_msg, 12);
    }

    //open vrec file
    //QFile qFile;
    fstream inFile;
    inFile.open(m_szFileName.toStdString().c_str(), fstream::in);
    bFileReady = inFile.is_open();
    QTime sPreviosTime, sCurrentTime;
    quint16 deltaTimeMS = 0;
    float fSpeed_kbps= 0.0;
    quint32 u32ByteSent = 0;

    // Check if serial port and file is open OK
    if (bFileReady && (pSocket->state() == QAbstractSocket::ConnectedState))
    {
#if 1
        sPreviosTime = QTime::currentTime();

        qDebug("Start transfer");
        while(!getline(inFile, line).eof())
        {

            //********************************************************************************//
            // Check if thread is stopped externally
            if (m_bStopped) {
                iFinishedCode = VREC_PROG_FINISH_PROG_ERR;
                break;
            }
            //********************************************************************************//
            // Update the completed percent
            //calculate the transfer speed (byte per second)
            sCurrentTime = QTime::currentTime();
            deltaTimeMS = (sCurrentTime.second() - sPreviosTime.second())*1000 + sCurrentTime.msec() - sPreviosTime.msec();
//            sPreviosTime = sCurrentTime;
            u32ByteSent+= line.length();

            fSpeed_kbps = (float)u32ByteSent/deltaTimeMS * 0.9765625;

            if (u32NVrecLines != 0)
            {
                m_fPercent = ((float)u32ProgrammedNlines / (float)u32NVrecLines * 100);
//                qDebug()<<"\r\n percent "<< m_fPercent <<"%, speed: " << fSpeed_kbps;
            }
            else {
                m_fPercent = 1;
//                qDebug()<<"\r\n percent "<< m_fPercent <<"%, speed: " << fSpeed_kbps;
            }
//            emit percent(m_fPercent);
//            emit speed(fSpeed_kbps);
//            if(iLineIdx %2)
                emit update(int(m_fPercent*100), (int)(fSpeed_kbps*100));

            // Previous Vrec Process error
            if (u8Ret != BOOT_ERR_NONE)
            {
                qDebug()<<"\r\nEnd Programming Flash";
                iFinishedCode = VREC_PROG_FINISH_FORMAT_ERR;
                break;
            }


            //********************************************************************************//
            // Decode Vrec line
            iLineIdx ++;
            retDecode = VREC_Decode((uint8_t*)line.c_str(), &vrecInfo, &dataSize, VREC_RAW_FORMAT);
#if EW_DEBUG_ENABLE
            uint8_t u8crc4 = CalculateCRC4(vrecInfo.pu8Data, vrecInfo.u8DataLength);

            qDebug() << "Line: "<< QString::fromStdString(line) <<", CRC: " << u8crc4;
#endif
            if (retDecode != VREC_ERR_NONE) {
                qDebug("\r\nVrec Line [%d] error: 0x%X",iLineIdx, retDecode);
                QString text;
                text.sprintf("Vrec Line index [%d] error: 0x%X",iLineIdx, retDecode);
                emit error(text);
//                pTransferSpeed->setText(text);
//                QMessageBox::critical(NULL, "Error", text, QMessageBox::Ok);
                iFinishedCode = VREC_PROG_FINISH_FORMAT_ERR;
                break;
            }
            // Get a correct Vrecline here
            switch (vrecInfo.u8Type)
            {
            case VREC_TYPE_FILE_INFO:
                //********************Making BOOT HOOK**********************
                u16NumberProgs = (uint16_t) vrecInfo.sAddress.Value;
                qDebug("\r\n Number of Progs = %d", u16NumberProgs);
                vrecBuf[VREC_PREAMBLE_IDX] = VREC_PREAMBLE;
                vrecBuf[VREC_TYPE_IDX] = VREC_TYPE_BOOT_HOOK;
                iDataLength = 2;
                U8ToHexChar(iDataLength,&vrecBuf[VREC_LENGTH_IDX]);
                iFrameLength = 6 + 2 * iDataLength;
                u16DeviceId = (uint16_t) vrecInfo.sAddress.Value;
                qDebug()<<"\r\n VREC_TYPE_FILE_MAP u16DevID = "<<u16DeviceId;
                U16ToHexChar(u16DeviceId, &vrecBuf[VREC_DATA_IDX]);
                u8CRC = VREC_CalculateCRC(&vrecBuf[1], iFrameLength - 3, 1);
                U8ToHexChar(u8CRC, &vrecBuf[iFrameLength - 2]);
                vrecBuf[iFrameLength] = '\0';
                vStrBootHooks.push_back(string((char*)vrecBuf));
                //			vStrBootHooks.push_back(string("!B0200020E"));
                //			vStrBootHooks.push_back(string("!B0200010B"));

                break;
            case VREC_TYPE_FILE_MAP:
                u32HeaderLine = HexCharToU32((uint8_t*)line.c_str()+8);
                vu32HeaderLine.push_back(u32HeaderLine);
                u32NVrecLines = HexCharToU32((uint8_t*)line.c_str()+16);
                vu32VrecLens.push_back(u32NVrecLines);
                break;
            case VREC_TYPE_HEADER:

                qDebug()<<"\r\n VREC_TYPE_HEADER ";
                strBootHook = vStrBootHooks[iHeader];
                u32NVrecLines = vu32VrecLens[iHeader];

                qDebug()<<"\r\nCorresponding Boot Hooks = "<< QString::fromStdString(strBootHook) <<" nVrecLines = "<< u32NVrecLines;
                u32ProgrammedNlines = 1;

                //************** Making Boot Node Select*******************
                vrecBuf[VREC_PREAMBLE_IDX] = VREC_PREAMBLE;
                vrecBuf[VREC_TYPE_IDX] = VREC_TYPE_SELECT_NODE;
                iDataLength = 2;
                U8ToHexChar(iDataLength,&vrecBuf[VREC_LENGTH_IDX]);
                iFrameLength = 6 + 2 * iDataLength;
                u16NodeId = (uint16_t) vrecInfo.sAddress.Value;
                qDebug()<<"\r\nu16NodeId = "<<u16NodeId;

                U16ToHexChar(u16NodeId, &vrecBuf[VREC_DATA_IDX]);
                u8CRC = VREC_CalculateCRC(&vrecBuf[1], iFrameLength - 3, 1);
                U8ToHexChar(u8CRC, &vrecBuf[iFrameLength - 2]);
                vrecBuf[iFrameLength] = '\0';
                qDebug()<<"\r\n Boot Node Select = " << (char*) vrecBuf;
                strNodeSelect = std::string((char*)vrecBuf, iFrameLength);

                //********************Send Boot Hook***************************
                u8Ret = GetRespond(pSocket, strBootHook, "Stage Hook", true);
                if (u8Ret != BOOT_ERR_NONE) {
                    qDebug()<< "\r\n Error Boot Hook";
                    break;
                }
                else {
                    qDebug("\r\n Boot hooked");
                }

                //*********************Send Node Select**************************
                u8Ret = GetRespond(pSocket, strNodeSelect, "Stage Node Select", false);
                if (u8Ret != BOOT_ERR_NONE) {
                    qDebug() <<"\r\nError Node Select";
                    break;
                }
                else {
                    qDebug("\r\n Node selected");
                }

                //********************Send Header Line**************************
                u8Ret = GetRespond(pSocket, line, "Stage Header");
                if (u8Ret != BOOT_ERR_NONE) {
                    qDebug() <<"\r\nError Node Select";
                    break;
                }
                else {
                    qDebug("\r\n Node selected");
                }
                iHeader++;
                // Send Boot Node Select
                break;
            case VREC_TYPE_FILE_DATA16:
            case VREC_TYPE_FILE_DATA24:
            case VREC_TYPE_FILE_DATA32:
                u32ProgrammedNlines++;
                u8Ret = GetRespond(pSocket, line, "Stage Data Prog");
                if (u8Ret != BOOT_ERR_NONE) {
                    qDebug() << "\r\nError Program Data";
                    break;
                }
                else {
                    //qDebug("\r\nACK PROG DATA lines %d", u32ProgrammedNlines);
                }
                // Just forward
                break;
            case VREC_TYPE_END_PROGRAM16:
            case VREC_TYPE_END_PROGRAM24:
            case VREC_TYPE_END_PROGRAM32:
                u32ProgrammedNlines++;
                u8Ret = GetRespond(pSocket, line, "Stage End Prog");
                if (u8Ret != BOOT_ERR_NONE) {
                    qDebug() << "\r\nError Program End of Prog";
                    break;
                }
                else {
                    //*****************************************************
                    // Only get here if programming succeded
                    u32ProgrammedNlines = u32NVrecLines;
                    qDebug("\r\n ACK END PROG DATA lines -->PROGRAMMING SUCCEEDED %d", u32ProgrammedNlines);
                    iFinishedCode = VREC_PROG_FINISH_OK;
                    break;
                }
                // just forward
                break;
            case VREC_TYPE_END_OF_FILE:
#ifdef ENABLE_SEND_END_OF_FILE
                // just forward
                u8Ret = GetRespond(line, "Stage End File");
                if (u8Ret != BOOT_ERR_NONE) {
                    qDebug() << "\r\nError Program End of File";
                    return u8Ret;
                }
#endif
                break;
            default:
                qDebug()<<"Undefined Vrec Prog";
                u8Ret = BOOT_ERR_UNKOWN;
                iFinishedCode = VREC_PROG_FINISH_FORMAT_ERR;
                break;
            }
        } // end of while (get vrec lines)
#else
        while(!getline(inFile, line).eof())
        {
            //        pSocket->write(QByteArray::fromStdString(line));
            pSocket->write(line.c_str());
            pSocket->waitForBytesWritten(VREC_PROG_COMM_WRITE_BOOT_TIME_OUT_MS);
        }


#endif
    }
    else // end of Check if serial port and file is open OK
    {
        qDebug()<<"file or tcp socket is not opened!";
        if (!bFileReady) {
            iFinishedCode = VREC_PROG_FINISH_OPEN_FILE_ERR;
             qDebug()<<"file is not opened!";
//            emit finished(iFinishedCode);
//            emit onError("Input file is not openned!");
        }

        if (pSocket->state() != QAbstractSocket::ConnectedState) {
            iFinishedCode = VREC_PROG_FINISH_OPEN_PORT_ERR;
             qDebug()<<"tcp socket is not opened!";
//            emit finished(iFinishedCode);
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // exit programming
    if (bFileReady)
        inFile.close();
//    if (pSocket->state() == QAbstractSocket::ConnectedState)
       pSocket->disconnectFromHost();
       qDebug("Exited!");
    m_bRunning = false;
    m_bStopped = false; // restart stopped
    emit finished(iFinishedCode);
}

/* Update via forwarder - each message contains header and VREC line */
struct TcpMsgHdr{
    uint32_t MsgLen;
    uint16_t SrcID;
    uint16_t DstID;
};

#define UPDATER_ID      0x000F
#define MSG_UPDATE_ID   0xF0

#define HTONS(x) ((((x) & 0x00ffUL) << 8) | (((x) & 0xff00UL) >> 8))
#define HTONL(x) ((((x) & 0x000000ffUL) << 24) | \
                  (((x) & 0x0000ff00UL) <<  8) | \
                  (((x) & 0x00ff0000UL) >>  8) | \
                  (((x) & 0xff000000UL) >> 24))

//Update 13/12/17: indirect update
uint8_t TcpProgWorker::GetRespond(QTcpSocket* pSocket, string vrecStr, string strStage, bool isBootHook)
{
    if(this->m_FwdOpt) {
        // Send Boot Hook First
        int iNTries = 0;
        uint8_t u8Ret = BOOT_ERR_NONE;
        uint8_t pRxBuffer[512];
        memset(pRxBuffer, 0xFF, 512);
        uint16_t u16FrameLength;
        QTime qtStartTime;
        uint8_t pTxBuffer[512];

        /* 13/12 Fill Msg header */
        uint16_t VrecLen = vrecStr.length();
        struct TcpMsgHdr *pHdr = (struct TcpMsgHdr *) pTxBuffer;
        pHdr->SrcID = HTONS(UPDATER_ID);
        pHdr->DstID = HTONS(this->m_SensorId);
        pHdr->MsgLen= HTONL(VrecLen + 1 + 4);
        pTxBuffer[8] = MSG_UPDATE_ID;
        memcpy(&pTxBuffer[9], vrecStr.c_str(), VrecLen);

        if (isBootHook)
        {
            // forever loop until hooked or being forced
            while(!m_bStopped)
            {
                qtStartTime = QTime::currentTime();
                qDebug("Write boot hook");
                pSocket->write((char*)pTxBuffer, 9 + VrecLen);
                if ( pSocket->waitForBytesWritten(VREC_PROG_COMM_WRITE_BOOT_TIME_OUT_MS))
                {
                    u8Ret = GetVRECLine(pSocket, pRxBuffer, &u16FrameLength, VREC_PROG_COMM_READ_BOOT_TIME_OUT_MS);
                    if (u8Ret == BOOT_ERR_NONE)
                    {
                        break;
                    }
                }
                else
                {
                    u8Ret = BOOT_ERR_TIMEOUT;
                }
            }
        }
        else
        {
            while(iNTries++ < 10)
            {
                pSocket->write((char*)pTxBuffer, 9 + VrecLen);
                if ( pSocket->waitForBytesWritten(VREC_PROG_COMM_WRITE_DATA_TIME_OUT_MS))
                {
                    u8Ret = GetVRECLine(pSocket, pRxBuffer, &u16FrameLength, VREC_PROG_COMM_READ_DATA_TIME_OUT_MS);
                    if (u8Ret == BOOT_ERR_NONE)
                        break;
                }
                else
                {
                    u8Ret = BOOT_ERR_TIMEOUT;
                }
            }
        }
        return u8Ret;
    }
    else {
        // Send Boot Hook First
        int iNTries = 0;
        uint8_t u8Ret = BOOT_ERR_NONE;
        uint8_t pRxBuffer[512];
        memset(pRxBuffer, 0xFF, 512);
        uint16_t u16FrameLength;
        QTime qtStartTime;
        if (isBootHook)
        {
            // forever loop until hooked or being forced
            while(!m_bStopped)
            {
                qtStartTime = QTime::currentTime();
                pSocket->write(vrecStr.c_str());
                if ( pSocket->waitForBytesWritten(VREC_PROG_COMM_WRITE_BOOT_TIME_OUT_MS))
                {
                    u8Ret = GetVRECLine(pSocket, pRxBuffer, &u16FrameLength, VREC_PROG_COMM_READ_BOOT_TIME_OUT_MS);
                    if (u8Ret == BOOT_ERR_NONE)
                    {

                        break;
                    }
                }
                else
                {
                    u8Ret = BOOT_ERR_TIMEOUT;
                }
            }
        }

        else
        {
            while(iNTries++ < 10)
            {
                pSocket->write(vrecStr.c_str());
                if ( pSocket->waitForBytesWritten(VREC_PROG_COMM_WRITE_DATA_TIME_OUT_MS))
                {
                    u8Ret = GetVRECLine(pSocket, pRxBuffer, &u16FrameLength, VREC_PROG_COMM_READ_DATA_TIME_OUT_MS);
                    if (u8Ret == BOOT_ERR_NONE)
                        break;
                }
                else
                {
                    u8Ret = BOOT_ERR_TIMEOUT;
                }
            }
        }
        return u8Ret;
    }
}

//quint8 TcpProgWorker::getVrecLine(quint8 *pRxBuffer, quint8 u8RxByte)
// 13/12/17: Modify for indirect update (9 bytes header before ACK data)
uint8_t TcpProgWorker::GetVRECLine(QTcpSocket * pSocket, uint8_t* pRxBuffer, uint16_t* pFrameLength, int iTimeOutMS)
{
    if(this->m_FwdOpt) {
        uint8_t u8Ret = BOOT_ERR_UNKOWN;
        if (!m_bStopped) {
            QByteArray responseData = pSocket->readAll();
            if (pSocket->waitForReadyRead(VREC_PROG_COMM_READ_BOOT_TIME_OUT_MS)) {
                responseData += pSocket->readAll();
                emit receivedData(QString(responseData));
                int i;
                if(responseData.size() >= 17) {
                    for(i = 0; i < 17; i++) {
                        pRxBuffer[i] = responseData[i];
                    }
                    if (memcmp(pRxBuffer + 9, VREC_CommError[VREC_COMM_ERROR_ACK_IDX], 8) == 0) {
                        u8Ret = BOOT_ERR_NONE;
                        qDebug("Received ACK");
                        return u8Ret;
                    }
                }
            }
            else {
                qDebug("Response timeout!");
            }
        }
        return u8Ret;
    }
    else {
        uint8_t u8Ret = BOOT_ERR_UNKOWN;
        uint8_t u8Len = 0;
        char u8ReadByte;
        QTime* readTime = new QTime;
        readTime->start();
        while (u8Len < 8 && !m_bStopped) {
            //qDebug("elapsedTime = %d", readTime->elapsed());
            if (readTime->elapsed() > iTimeOutMS)
            {
                qDebug()<<"readTimeout";
                break;
            }

            QByteArray responseData = pSocket->readAll();
            if (pSocket->waitForReadyRead(VREC_PROG_COMM_READ_BOOT_TIME_OUT_MS)) {
                responseData += pSocket->readAll();
            }
            emit receivedData(QString(responseData));
            for (int i = 0; i < responseData.size(); i++) {
                u8ReadByte = responseData[i];
            //std::cout<<"["<<(char)u8ReadByte<<"]";fflush(stdout);
                if (VREC_IS_VALID_CHARACTER(u8ReadByte) == 1)
                {
                    if (u8Len > 0){
                        pRxBuffer[u8Len++] = u8ReadByte;
                        if (u8Len == 8) {
                            *pFrameLength = 8;
                            if (memcmp(pRxBuffer, VREC_CommError[VREC_COMM_ERROR_ACK_IDX], 8) == 0) {
                                u8Ret = BOOT_ERR_NONE;
                                //emit receivedData(" ACK ");
                            }
                            delete readTime;
                            return u8Ret;
                        }
                    }
                }
                else {
                    if (u8ReadByte == VREC_PREAMBLE)
                    {
                        //std::cout<<"\r\nPreamble ";
                        u8Len = 0;
                        pRxBuffer[u8Len++] = u8ReadByte;
                    }
                }
            }
        }
        delete readTime;
        return u8Ret;
    }
}


void TcpProgWorker::var_dump(quint8* data, quint16 len)
{
    for (quint8 i = 0; i < len; i ++)
        qDebug() << QString("%1").arg(data[i],0, 16) << "  ";
}

quint8 TcpProgWorker::processVrecLine(quint8 *pRxBuffer, uint8_t u8Ret)
{
    qDebug()<<"------------------ProcessVrecLine------------------";
    if (memcmp(pRxBuffer, VREC_CommError[VREC_COMM_NACK_IDX], 8) == 0)
    {
        qDebug()<<"NACK";
        switch(u8CurrentCMD) {
//            case MODEL_ERASE_HW_SERIAL_CMD:
//            {
//                QMessageBox msgBox;
//                msgBox.setIcon(QMessageBox::Critical);
//                msgBox.setText(tr("Xóa HW Serial thất bại"));
//                msgBox.exec();
//                break;
//            }
        }
    }
    else if (memcmp(pRxBuffer, VREC_CommError[VREC_COMM_ACK_IDX], 8) == 0)
    {
        qDebug()<<"ACK";
        switch(u8CurrentCMD) {
//            case MODEL_ERASE_HW_SERIAL_CMD:
//            {
//                QMessageBox msgBox;
//                msgBox.setText(tr("Đã xóa thành công HW Serial"));
//                msgBox.exec();
//                break;
//            }
        }
    }
    else {
        qDebug()<<"Read command come here";
        uint32_t szBufferCount;
        uint8_t u8DecodeRet = VREC_Decode(pRxBuffer, &sVrecInfo, &szBufferCount,VREC_RAW_FORMAT);

        //TODO: When receiving wrong VREC Data line
        // send a error message BOOT_CondSendNotApplicable
        if (u8DecodeRet != VREC_ERR_NONE) {
            qDebug()<<"VREC decode false";
            return BOOT_ERR_UNKOWN;
        }
        switch (sVrecInfo.u8Type) {
        case VREC_TYPE_SI3: {

            quint8* pu8Data = sVrecInfo.pu8Data;
            qDebug() << "sVrecInfo.pu8Data";
            var_dump(sVrecInfo.pu8Data, sVrecInfo.u8DataLength);
            quint8 u8Len, u8Cmd;
            u8Len = pu8Data[0];
            u8Cmd = pu8Data[1];
            qDebug()<<"Data size = "<<sVrecInfo.u8DataLength<<
                      "u8Len = "<<u8Len<<"u8CMD = "<<u8Cmd ;
            switch (u8Cmd)
            {
//                case MODEL_GET_HW_SERIAL_CMD: {
//                    QByteArray ba;
//                    bool bValidNumber = true;
//                    for (int i = 0; i < u8Len; i++) {
//                        ba.append(pu8Data[2+i]);
//                        if (isValidModelCharacter(ba[i]))
//                            qDebug("ba[%d]= 0x%X", i, (uint32_t) pu8Data[2+i]);
//                        else {
//                            qDebug("invalid character 0x%02X", pu8Data[2+i]);
//                            bValidNumber = false;
//                            break;
//                        }

//                    }
//                    if (u8Len == 0)
//                        bValidNumber = false;
//                    if (bValidNumber)
//                        pInfoLines[MODEL_HW_SERIAL_IDX]->setInfoLineText(QString(ba));
//                    else
//                    {
//                        QMessageBox msgBox;
//                        msgBox.setText(tr("Chưa có HW Serial hoặc ký tự không hợp lệ, yêu cầu xóa"));
//                        msgBox.exec();
//                    }
//                    break;
//                }
//                case MODEL_GET_HW_VERSION_CMD: {
//                    QByteArray ba;
//                    bool bValidNumber = true;
//                    for (int i = 0; i < u8Len; i++) {
//                        ba.append(pu8Data[2+i]);
//                        qDebug("ba[%d]= 0x%X", i, (uint32_t) pu8Data[2+i]);
//                        if (isValidModelCharacter(ba[i]))
//                            qDebug("ba[%d]= 0x%X", i, (uint32_t) pu8Data[2+i]);
//                        else {
//                            qDebug("invalid character 0x%02X", pu8Data[2+i]);
//                            bValidNumber = false;
//                            break;
//                        }
//                    }
//                    if (u8Len == 0)
//                        bValidNumber = false;
//                    if (bValidNumber)
//                        pInfoLines[MODEL_HW_VERSION_IDX]->setInfoLineText(QString(ba));
//                    else
//                    {
//                        QMessageBox msgBox;
//                        msgBox.setText(tr("Chưa có HW Version, hoặc ký tự không hợp lệ, yêu cầu xóa"));
//                        msgBox.exec();
//                    }
//                    break;
//                }
                default:
                    break;
            }

            break;
        }
        default:
            qDebug()<<"Nhu LOL";
            break;
        }
        return VREC_ERR_NONE;
    }
}

