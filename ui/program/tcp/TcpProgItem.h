#ifndef TCPPROGITEM_H
#define TCPPROGITEM_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QStandardPaths>
#include <QThread>
#include "TcpProgWorker.h"


class TcpProgItem : public QObject
{
    Q_OBJECT
public:
    explicit TcpProgItem(QObject *parent = nullptr);
    ~TcpProgItem();
    QString getFileName() {return m_szFileName;}
    QString getServerName() {return m_szServerName;}
    quint32 getServerPort() {return m_nServerPort;}
    void Stop();

private:
    QString         m_szFileName;
    QString         m_szServerName;
    quint32         m_nServerPort;
    quint32         m_SensorId;
    bool            m_FwdOpt;
    TcpProgWorker*          pProgWorker;
    QThread*                pProgThread;
    bool                    bIsProgramming;
//    QString                 path;
    QTime                   m_Time;
    int                     m_fPercent;
    int                     m_fSpeed;

private slots:
    // From QML --> C++
    void            on_ProgFinished(int uiErrCode);
    void            on_Error(QString szErrorMsg);

public slots:
    void            process();
    void            on_Update(int fPercent, int fSpeed);
    void            setFileName(QString strName)            {qDebug() << "filename changed: " << strName; m_szFileName = strName;}
    void            setServerName(QString strName)          {qDebug() << "Address changed: " << strName; m_szServerName = strName;}
    void            setServerPort(QString szPortNumber)     {qDebug() << "Port changed: " << szPortNumber; if(szPortNumber.length()) m_nServerPort = stoul(szPortNumber.toStdString(), NULL, 10);}
    void            setSensorId(QString strId)              {qDebug() << "Sensor ID:" << strId; if(strId.length()) m_SensorId = stoul(strId.toStdString(), NULL, 10);}
    void            setFwdOpt(bool opt)                     {qDebug() << "Forwarder option:" << opt; m_FwdOpt=opt;}
signals:
    void            update(int fPercent, int fSpeed);
    void            finished(QString szResult, QString szDetails);
    void            error(QString szErrorMsg);

};


#endif // FRMPROGITEM_H
