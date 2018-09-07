#include "flashfpga.h"
#include "debug.h"
#include <QNetworkInterface>
#ifdef _MSC_VER
#include <pcap/pcap.h>
#endif

FlashFpga::FlashFpga(QWidget *parent) :
    QWidget(parent)
{
    initVariable();
    createUiElem();
    createLayout();
    createContent();
    createConnection();
}

FlashFpga::~FlashFpga()
{
    m_control->Ether_Stop();
    delete m_control;
}

void FlashFpga::initVariable()
{
    m_lastFilePath = "";
    m_tcpProg = new TcpProgItem;
    m_programming = false;    
    m_control = new Controller();
}

void FlashFpga::createUiElem()
{
    mainLayout      = new QVBoxLayout;
    formMain = new QFormLayout;
    groupConfigFpga = new QGroupBox("ĐỌC GHI CẤU HÌNH FPGA HOẶC SENSOR");
    gridConfigFpga = new QGridLayout;
    comNetworkCard = new QComboBox;
    comSensorType = new QComboBox;
    editFpgaIp = new QLineEdit;
    editFpgaPort = new QLineEdit;
    btnWriteFpgaType = new QPushButton("GHI LOẠI SENSOR");
    btnReadFpgaType=   new QPushButton("ĐỌC LOẠI SENSOR");
    btnWriteFpgaIp = new QPushButton("GHI ĐỊA CHỈ IP");
    btnReadFpgaIp =  new QPushButton("ĐỌC ĐỊA CHỈ IP");

    groupProgramFpga   = new QGroupBox("NẠP CHƯƠNG TRÌNH FPGA HOẶC IFRF");
    formProgramFpga    = new QFormLayout;

    editFilePath = new QLineEdit(this);
    prgProgramFpga = new QProgressBar;
    editSensorAddr = new QLineEdit;
    editSensorPort = new QLineEdit;
    editSensorId = new QLineEdit;
    checkUseForwarder = new QCheckBox;
    btnBrowseFile   = new QPushButton("CHỌN");
    btnStartStop    = new QPushButton("NẠP");
    labelStatus = new QLabel("SẴN SÀNG");


    groupSerialFpga = new QGroupBox("GHI - ĐỌC SERIAL FPGA");
    formSerialFpga  = new QFormLayout;
    editFpgaSerial  = new QLineEdit;
    btnWriteFpgaSerial = new QPushButton("GHI SERIAL");
    btnReadFpgaSerial = new QPushButton("ĐỌC SERIAL");


    groupSerialIfrf = new QGroupBox("GHI - ĐỌC SERIAL IFRF");
    formSerialIfrf  = new QFormLayout;
    editIfrfSerial  = new QLineEdit;
    btnWriteIfrfSerial = new QPushButton("GHI SERIAL IFRF");
    btnReadIfrfSerial = new QPushButton("ĐỌC SERIAL IFRF");


//    groupTestReadWrite = new QGroupBox("TEST READ WRITE INSTRUMENT");
//    formTestReadWrite = new QFormLayout;

//    btnSendCommand = new QPushButton("SEND SET COMMAND");
//    editSendCommand = new QLineEdit;
//    editRecvCommand = new QLineEdit;

    status = new QStatusBar(this);
}

void FlashFpga::createLayout()
{
    groupConfigFpga->setLayout(gridConfigFpga);
    gridConfigFpga->addWidget(new QLabel("NETWORK CARD"), 0, 0, Qt::AlignRight);
    gridConfigFpga->addWidget(comNetworkCard, 0, 1, Qt::AlignLeft);

    gridConfigFpga->addWidget(new QLabel("ĐỊA CHỈ IP"), 1, 0, Qt::AlignRight);
    gridConfigFpga->addWidget(editFpgaIp, 1, 1, Qt::AlignLeft);
    gridConfigFpga->addWidget(btnReadFpgaIp, 1, 2);
    editFpgaIp->setFixedWidth(230);
    gridConfigFpga->addWidget(new QLabel("CỔNG TCP"), 2, 0, Qt::AlignRight);
    gridConfigFpga->addWidget(editFpgaPort, 2, 1, Qt::AlignLeft);
    gridConfigFpga->addWidget(btnWriteFpgaIp, 2, 2);
    editFpgaPort->setFixedWidth(60);

    gridConfigFpga->addWidget(new QLabel("LOẠI SENSOR"), 3, 0, Qt::AlignRight);
    gridConfigFpga->addWidget(comSensorType, 3, 1, Qt::AlignLeft);
    gridConfigFpga->addWidget(btnReadFpgaType, 3, 2);

    gridConfigFpga->addWidget(btnWriteFpgaType, 4, 2);

    groupProgramFpga->setLayout(formProgramFpga);
    formProgramFpga->addRow("IP ADDRESS", editSensorAddr);
    editSensorAddr->setFixedWidth(150);
    formProgramFpga->addRow("TCP PORT", editSensorPort);
    editSensorPort->setFixedWidth(60);
    formProgramFpga->addRow("NẠP QUA FORWARDER", checkUseForwarder);    
    formProgramFpga->addRow("CHỌN FILE NẠP CHO FPGA HOẶC IFRF",editFilePath);
    formProgramFpga->addRow(btnBrowseFile);
    formProgramFpga->setAlignment(btnBrowseFile, Qt::AlignRight);    
    formProgramFpga->addRow(prgProgramFpga);
    formProgramFpga->addRow(labelStatus, btnStartStop);
    formProgramFpga->setAlignment(btnStartStop, Qt::AlignRight);

    prgProgramFpga->setMaximum(100);    

    formMain->addRow(groupConfigFpga, groupProgramFpga);

    groupSerialFpga->setLayout(formSerialFpga);
    formSerialFpga->addRow("Nhập Serial", editFpgaSerial);
    formSerialFpga->addRow(btnReadFpgaSerial, btnWriteFpgaSerial);



    groupSerialIfrf->setLayout(formSerialIfrf);
    formSerialIfrf->addRow("Nhập Serial", editIfrfSerial);
    formSerialIfrf->addRow(btnReadIfrfSerial, btnWriteIfrfSerial);    

    formMain->addRow(groupSerialFpga, groupSerialIfrf);

//    groupTestReadWrite->setLayout(formTestReadWrite);
//    formTestReadWrite->addWidget(new QLabel("SEND COMMAND"));
//    formTestReadWrite->addRow(editSendCommand, btnSendCommand);
//    formTestReadWrite->addWidget(new QLabel("RECEIVED COMMAND"));
//    formTestReadWrite->addRow(editRecvCommand);

//    editSendCommand->setFixedWidth(300);

//    formMain->addWidget(groupTestReadWrite);

    mainLayout->addLayout(formMain);
    status->setMaximumHeight(20);    
    mainLayout->addWidget(status, 0, Qt::AlignBottom);

    setLayout(mainLayout);
    status->showMessage("Cài đặt các tham số chung");

}

void FlashFpga::createContent()
{

    editFpgaIp->setText("192.168.1.11");
    editFpgaPort->setText("1567");
    editSensorAddr->setText("192.168.1.101");
    editSensorPort->setText("7");
    labelStatus->setAlignment(Qt::AlignCenter);
    labelStatus->setStyleSheet("QLabel {color : green; }");

#ifdef __linux__
    foreach (const QNetworkInterface &info,  QNetworkInterface::allInterfaces()) {
        QString s = info.name();
        if(s != "lo")
            comNetworkCard->addItem(s);
    }
#else
    pcap_if_t *alldevs = 0;
    pcap_if_t *d = 0;
    uint8_t errbuf[PCAP_ERRBUF_SIZE];
    if (pcap_findalldevs(&alldevs, (char*)errbuf) != -1){
        for (d = alldevs; d != NULL; d = d->next){
            if (d->name){
                comNetworkCard->addItem(QString(d->name));
            }
        }
    }
    pcap_freealldevs(alldevs);
#endif

    comNetworkCard->setEditable(true);
    comNetworkCard->lineEdit()->setReadOnly(true);
    comNetworkCard->lineEdit()->setAlignment(Qt::AlignCenter);
    for(int i = 0; i < comNetworkCard->count(); i++) {
        comNetworkCard->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }


    comSensorType->addItem(tr("LOCAL"));
    comSensorType->addItem(tr("REMOTE 1"));
    comSensorType->addItem(tr("REMOTE 2"));
    comSensorType->addItem(tr("REMOTE 3"));

    comSensorType->setEditable(true);
    comSensorType->lineEdit()->setReadOnly(true);
    comSensorType->lineEdit()->setAlignment(Qt::AlignCenter);
    for(int i = 0; i < comSensorType->count(); i++) {
        comSensorType->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    groupConfigFpga->setMinimumWidth(QApplication::desktop()->screenGeometry(this).width() / 3);
    groupSerialFpga->setMinimumWidth(QApplication::desktop()->screenGeometry(this).width() / 3);

    btnReadIfrfSerial->setMaximumWidth(btnWriteIfrfSerial->width());
}

void FlashFpga::createConnection()
{
    connect(btnBrowseFile, SIGNAL(clicked(bool)), this, SLOT(on_btnBrowseFileClicked()));
    connect(btnStartStop, SIGNAL(clicked(bool)), this, SLOT(on_btnStartProgClicked()));
    connect(btnWriteFpgaType, SIGNAL(clicked(bool)), this, SLOT(on_btnWriteSensorTypeClicked()));
    connect(btnReadFpgaType, SIGNAL(clicked(bool)), this, SLOT(on_btnReadSensorTypeClicked()));
    connect(btnWriteFpgaIp, SIGNAL(clicked(bool)), this, SLOT(on_btnWriteSensorIpClicked()));
    connect(btnReadFpgaIp, SIGNAL(clicked(bool)), this, SLOT(on_btnReadSensorIpClicked()));
    connect(m_control, SIGNAL(sigEtherRecvData(uint8_t*,int)), this, SLOT(on_etherDataEvent(uint8_t*,int)));
    //connect(btnSendCommand, SIGNAL(clicked(bool)), this, SLOT(on_btnSendCommandClicked()));

    //m_control->ConfigSpectrum("192.168.1.12", 5025);
    //m_control->Spect_Start();
    //LREP("Spect started: {}\n", m_control->SigGen_GetStatus());
}

void FlashFpga::startProg()
{
    if(editFilePath->text() != "") {
        m_tcpProg->setFileName(editFilePath->text());

    } else {
        QMessageBox::warning(this, "Lỗi", "File nạp không hợp lệ !");
        return;
    }

    if(editSensorAddr->text() != "") {
        m_tcpProg->setServerName(editSensorAddr->text());
    } else {
        QMessageBox::warning(this, "Lỗi", "Địa chỉ sensor không hợp lệ !");
        return;
    }

    if(editSensorPort->text() != "") {
        m_tcpProg->setServerPort(editSensorPort->text());
    } else {
        QMessageBox::warning(this, "Lỗi", "Cổng nạp không hợp lệ !");
        return;
    }

    m_tcpProg->setSensorId(editSensorId->text());
    m_tcpProg->setFwdOpt(checkUseForwarder->isChecked());


    connect(m_tcpProg, SIGNAL(finished(QString,QString)), this, SLOT(on_finishProg(QString,QString)));
    connect(m_tcpProg, SIGNAL(update(int,int)), this, SLOT(on_updateProgProgess(int,int)));
    connect(m_tcpProg, SIGNAL(error(QString)), this, SLOT(on_errorProg(QString)));

    m_tcpProg->process();
    labelStatus->setStyleSheet("QLabel {color : green; }");
    labelStatus->setText("ĐANG NẠP ...");
    m_programming = true;
}

void FlashFpga::stopProg()
{
    m_tcpProg->Stop();
    m_programming = false;
}

void FlashFpga::on_btnStartProgClicked()
{
    if(!m_programming) {
        startProg();
        btnStartStop->setText("DỪNG");
    } else {
        stopProg();
        btnStartStop->setText("NẠP");
    }
}

void FlashFpga::on_btnBrowseFileClicked()
{
    QString filePath;
    if(m_lastFilePath == "") {
        filePath = QFileDialog::getOpenFileName(this, tr("Tìm file nạp"), QDir::homePath(), tr("Vrec files (*.vrec) ;; All files (*.*)"));
        m_lastFilePath = QFileInfo(filePath).path();
    } else {
        filePath = QFileDialog::getOpenFileName(this, tr("Tìm file nạp"), m_lastFilePath, tr("Vrec files (*.vrec) ;; All files (*.*)"));
    }

    if(filePath != "") {
        //LREP("filepath: {}\n", filePath.toStdString());
        editFilePath->setText(filePath);

    }
}

void FlashFpga::on_finishProg(QString result, QString detail)
{
    if(result == "Thành công") {
        labelStatus->setStyleSheet("QLabel {color : green; }");
        labelStatus->setText("NẠP THÀNH CÔNG");
    } else {

        labelStatus->setStyleSheet("QLabel {color : red; }");
        if(detail != "") {
            labelStatus->setText("NẠP THẤT BẠI: " + detail);
        } else {
            labelStatus->setText("NẠP THẤT BẠI: lỗi ");
        }
    }
    m_programming = false;
    btnStartStop->setText("NẠP");
}

void FlashFpga::on_updateProgProgess(int fPercent, int fSpeed)
{
    (void)fSpeed;
    double value = fPercent / 100.0;
    prgProgramFpga->setValue(value);
}

void FlashFpga::on_errorProg(QString error)
{
    LREP("LOI {}\n", error.toStdString());
    //QMessageBox::warning(this, "Lỗi", error);
}

void FlashFpga::on_btnWriteSensorTypeClicked()
{
    if(m_control->Ether_GetStatus() == communication::Event_Disconnected) {
        std::string name = comNetworkCard->currentText().toStdString();
        if(!m_control->Ether_Start(name)) {
            QMessageBox::warning(this, "Lỗi", "Không có quyền sử dụng Network card " +
                                 comNetworkCard->currentText());
            return;
        }
    }

    LREP("Set sensor type\n");
    m_control->Ether_SetSensorType((Sensor_Type_List)comSensorType->currentIndex());
}

void FlashFpga::on_btnWriteSensorIpClicked()
{
    if(m_control->Ether_GetStatus() == communication::Event_Disconnected) {
        std::string name = comNetworkCard->currentText().toStdString();
        if(!m_control->Ether_Start(name)) {
            QMessageBox::warning(this, "Lỗi", "Không có quyền sử dụng Network card " +
                                 comNetworkCard->currentText());
            return;
        }
    }
    LREP("Set sensor Ip\n");
    m_control->Ether_SetSensorIp(editFpgaIp->text().toStdString(), editFpgaPort->text().toInt());
}

void FlashFpga::on_btnReadSensorTypeClicked()
{
    if(m_control->Ether_GetStatus() == communication::Event_Disconnected) {
        std::string name = comNetworkCard->currentText().toStdString();
        if(!m_control->Ether_Start(name)) {
            QMessageBox::warning(this, "Lỗi", "Không có quyền sử dụng Network card " +
                                 comNetworkCard->currentText());
            return;
        }
    }
    LREP("Get sensor Type\n");
    m_control->Ether_GetSensorType();
}

void FlashFpga::on_btnReadSensorIpClicked()
{
    if(m_control->Ether_GetStatus() == communication::Event_Disconnected) {
        std::string name = comNetworkCard->currentText().toStdString();
        if(!m_control->Ether_Start(name)) {
            QMessageBox::warning(this, "Lỗi", "Không có quyền sử dụng Network card " +
                                 comNetworkCard->currentText());
            return;
        }
    }
    LREP("Get sensor IP\n");
    m_control->Ether_GetSensorIp();
}

void FlashFpga::on_etherDataEvent(uint8_t *data, int len)
{
    (void)len;
    switch(data[0]) {
        case Auto_Reset_Sensor:
        break;
        case Auto_Debug_Sensor:
        break;
        case Auto_Config_Sensor:
        switch (data[5])
        {
            case Command_Write_Type:
            {
                QString type;
                if(data[7] == 0) {type = "Local";}
                else if(data[7] == 1) {type = "Remote 1";}
                else if(data[7] == 2) {type = "Remote 2";}
                else if(data[7] == 3) {type = "Remote 3";}
                QMessageBox::information(this, "Thông báo", "Cấu hình sensor \"" + type + "\" thành công !");
            }
                break;
            case Command_Read_Type: {
                QString type;
                int idx = data[7];
                idx = idx < 0 ? 0 : idx;
                idx = idx > 3 ? 3 : idx;
                if(data[7] == 0) {type = "Local";}
                else if(data[7] == 1) {type = "Remote 1";}
                else if(data[7] == 2) {type = "Remote 2";}
                else if(data[7] == 3) {type = "Remote 3";}
                comSensorType->setCurrentIndex(idx);
                QMessageBox::information(this, "Thông báo", "Lấy thông tin sensor \"" + type + "\"thành công !");
                }
                break;

            case Command_Write_Ip:
                QMessageBox::information(this, "Thông báo", "Cấu hình ip sensor thành công !");
                break;

            case Command_Read_Ip:  {
                uint16_t port;
                QString ip;
                port  = data[11] << 8 | data[12];
                ip = QString::number(int(data[7])) + "." +
                        QString::number(int(data[8])) + "." +
                        QString::number(int(data[9])) + "." +
                        QString::number(int(data[10]));
                LREP("Recv ip: {}:{}\n", ip.toStdString(), port);
                editFpgaIp->setText(ip);
                editFpgaPort->setText(QString::number(port));
                QMessageBox::information(this, "Thông báo", "Lấy ip sensor thành công !");
            }
                break;

            default:
                break;
        }
        break;
    default:
        LREP("Ether sensor message {} not handled\n", data[0]);
        break;
    }
}


bool FlashFpga::FindText(QString &s)
{
    for(int i = 0; i < comNetworkCard->count(); i++) {
        if(comNetworkCard->itemText(i) == s) {
            return true;
        }
    }
    return false;
}



