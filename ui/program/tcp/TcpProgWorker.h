#ifndef TCPSERVER_H
#define TCPSERVER_H



#include <QObject>
#include <QDebug>
#include <QThread>
#include <QTime>
#include <QTimer>
#include <QTcpSocket>
#include <fstream>
#include <string>
#include "program/common/debug.h"
#include "program/common/vrec.h"
#include "program/common/convert.h"

using namespace std;

#define VREC_PROG_FINISH_OK                 0
#define VREC_PROG_FINISH_PROG_ERR           1
#define VREC_PROG_FINISH_OPEN_FILE_ERR      2
#define VREC_PROG_FINISH_OPEN_PORT_ERR      3
#define VREC_PROG_FINISH_FORMAT_ERR         4

// da test
#define VREC_PROG_COMM_WRITE_BOOT_TIME_OUT_MS       1000
#define VREC_PROG_COMM_WRITE_DATA_TIME_OUT_MS       2000
#define VREC_PROG_COMM_READ_BOOT_TIME_OUT_MS        1000
#define VREC_PROG_COMM_READ_DATA_TIME_OUT_MS        1000
#define VREC_PROG_COMM_READ_BYTE_TIME_OUT_MS        1

class TcpProgWorker : public QObject
{
    Q_OBJECT

public:
    explicit TcpProgWorker();
    ~TcpProgWorker();
    void setServerName(QString szServerName) {m_szServerName = szServerName;}
    void setServerPort(quint32 nServerPort) {m_nServerPort = nServerPort;}
    void setFileName(QString szFileName)    {m_szFileName = szFileName;}
    void setSensorId(quint32 nSensorId)     {m_SensorId = nSensorId;}
    void setFwdOpt(bool opt)                {m_FwdOpt = opt;}
    bool isRunning();
//    void start();
//    void stop();

signals:
    void finished(int);                 // end of programming
//    void percent(int);                  // percentage of finishing
//    void speed(float);
    void update(int fPercent, int fSpeed);
    void receivedData(QString str);     // string received from serialPort
    void error(QString str);          // Indicate the error message while decode VREC
public slots:
    void stop();
    void process();

private:
//    QLabel *pStatus;
//    Ui::MainWindow *ui;
//    Socket *socket;
//    QTcpServer *tcpServer;
    QString m_szServerName;
    quint32 m_nServerPort;
    quint32 m_SensorId;
    bool    m_FwdOpt;
    QString m_szFileName;
    bool    m_isConnected;
    bool    m_bRunning;
    float   m_fPercent;
    bool    m_bStopped;

    QTcpSocket *tcpClientSocket;


    quint8 pu8RxBuffer[512];
    quint8 pu8RxDecodeBuffer[512];
    quint16 u16RxCount, u16RxLen;
    quint8 u8CurrentCMD;
    S_VREC_INFO sVrecInfo;

    uint8_t GetRespond(QTcpSocket* pSocket, string vrecStr, string strStage, bool isBootHook = false);
    uint8_t GetVRECLine(QTcpSocket * pSocket, uint8_t* pRxBuffer, uint16_t* pFrameLength, int iTimeOutMS);
//    quint8 getVrecLine(quint8* pRxBuffer, quint8 u8RxByte);
    quint8 processVrecLine(quint8 *pRxBuffer, uint8_t u8Ret);
    void var_dump(quint8* data, quint16 len);
};


#endif // TCPSERVER_H
