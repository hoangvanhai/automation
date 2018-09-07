#include "TcpProgItem.h"



TcpProgItem::TcpProgItem(QObject *parent) : QObject(parent),
    bIsProgramming(false)
{
//    InitializeLayout();
}
TcpProgItem::~TcpProgItem()
{

}

void TcpProgItem::Stop()
{
    pProgWorker->stop();
}

void TcpProgItem::process()
{
    if (bIsProgramming) {
        qDebug()<<"prog process is running";
        pProgWorker->stop();
        return;
    }

    // new VrecProg API
    bIsProgramming = true; // turn on isProgramming
    pProgWorker = new TcpProgWorker();
    pProgThread = new QThread;

    pProgWorker->setFileName(m_szFileName);
    pProgWorker->setServerName(m_szServerName);
    pProgWorker->setServerPort(m_nServerPort);
    pProgWorker->setSensorId(m_SensorId);
    pProgWorker->setFwdOpt(m_FwdOpt);

    // connect signals slots
    pProgWorker->moveToThread(pProgThread);

    connect(pProgThread, SIGNAL(started()), pProgWorker, SLOT(process()));
    connect(pProgWorker, SIGNAL(finished(int)), pProgThread, SLOT(quit()));
    connect(pProgWorker, SIGNAL(finished(int)), pProgWorker, SLOT(deleteLater()));
    connect(pProgWorker, SIGNAL(finished(int)), this, SLOT(on_ProgFinished(int)));
    connect(pProgThread, SIGNAL(finished()), pProgThread, SLOT(deleteLater()));
    connect(pProgWorker, SIGNAL(update(int,int)), this, SLOT(on_Update(int,int)));
//    connect(pProgWorker, SIGNAL(onError(QString)), this, SLOT(on_Error(QString)));

    // start thread
    pProgThread->start();
    //m_Time.start();
}

void TcpProgItem::on_ProgFinished(int errCode)
{
    QString szProgResult, szProgInfo;

    qDebug()<<"on_ProgFinished errCode" << errCode;
    if (errCode == VREC_PROG_FINISH_PROG_ERR) {
        szProgResult = "Thất bại";
    } else if (errCode == VREC_PROG_FINISH_OK){
        szProgResult = "Thành công";
    } else if (errCode == VREC_PROG_FINISH_OPEN_FILE_ERR) {
        szProgResult = "Thất bại";
        szProgInfo = "Lỗi mở file";
    } else if (errCode == VREC_PROG_FINISH_OPEN_PORT_ERR) {
        szProgResult = "Thất bại";
        szProgInfo = "Không thể kết nối tới board";
    }
    else {
        szProgResult = "Thất bại";
    }

    emit finished(szProgResult, szProgInfo);

    bIsProgramming = false;

}

void TcpProgItem::on_Error(QString str)
{
//    QMessageBox::critical(this, "Error", str, QMessageBox::Ok);
    qDebug() << str;
    emit error(str);
}

void TcpProgItem::on_Update(int fPercent, int fSpeed)
{
    m_fPercent = fPercent;
    m_fSpeed = fSpeed;
    emit update(m_fPercent, m_fSpeed);
}
