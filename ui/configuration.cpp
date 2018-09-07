#include "configuration.h"
#include <iostream>
#include <fstream>
#include "debug.h"

Configuration::Configuration(QWidget *parent) :
    FoldWidget(parent)
{
    setExpandedWidth(400);
    initVariable();
    createUiElem();
    createLayout();
    createContent();
    createConnection();
}

Configuration::~Configuration()
{

}

void Configuration::initVariable()
{
    genConfig = UiConfig::getInstance()->getGeneralConfig();
    isSave = false;
}

void Configuration::createUiElem()
{
    mainLayout      = new QVBoxLayout;
    groupSetting1   = new QGroupBox("CÀI ĐẶT CHUNG");
    formSetting1    = new QFormLayout;

    editLocalIp = new QLineEdit;
    listSignalGenType = new QComboBox;
    listSpectrumType = new QComboBox;
    listPowerType = new QComboBox;
    listDigitalType = new QComboBox;
    btnSetGeneral = new QPushButton("LƯU CÀI ĐẶT");

    editSiggenDelay = new QLineEdit;
    editSpectDelay = new QLineEdit;
    editServerDelay = new QLineEdit;
    editLoadFileHigh = new QLineEdit;
    editLoadFileLow = new QLineEdit;
    editBwHigh = new QLineEdit;
    editBwLow = new QLineEdit;
    editTestInput = new QLineEdit;
    editTestOutput = new QLineEdit;
    btnSelectInput = new QToolButton;
    btnSelectOutput = new QToolButton;

    btnClose = new QPushButton("ĐÓNG");
    status = new QStatusBar(this);
}

void Configuration::createLayout()
{    
    groupSetting1->setAutoFillBackground(true);    
    groupSetting1->setLayout(formSetting1);
    formSetting1->addRow("Địa chỉ IP", editLocalIp);
    editLocalIp->setAlignment(Qt::AlignCenter);
    formSetting1->addRow("Loại Signal Generator", listSignalGenType);
    formSetting1->addRow("Loại Spectrum Analyzer", listSpectrumType);
    formSetting1->addRow("Loại Nguồn", listPowerType);
    formSetting1->addRow("Signal Gen delay millisecond", editSiggenDelay);
    formSetting1->addRow("Spectrum delay millisecond", editSpectDelay);
    formSetting1->addRow("Server delay millisecond", editServerDelay);
    formSetting1->addRow("Tên file nạp ≥ 25K",  editLoadFileHigh);
    formSetting1->addRow("Tên file nạp < 15K", editLoadFileLow);
    formSetting1->addRow("Băng thông file nạp ≥ 25K", editBwHigh);
    formSetting1->addRow("Băng thông file nạp < 25K", editBwLow);
    formSetting1->addWidget(btnSelectInput);
    formSetting1->addRow("Đường dẫn file đầu vào", editTestInput);
    formSetting1->addWidget(btnSelectOutput);
    formSetting1->addRow("Đường dẫn file kết quả", editTestOutput);
    editSiggenDelay->setAlignment(Qt::AlignCenter);
    editSpectDelay->setAlignment(Qt::AlignCenter);
    editServerDelay->setAlignment(Qt::AlignCenter);
    editLoadFileHigh->setAlignment(Qt::AlignCenter);
    editLoadFileLow->setAlignment(Qt::AlignCenter);
    editBwHigh->setAlignment(Qt::AlignCenter);
    editBwLow->setAlignment(Qt::AlignCenter);

    formSetting1->addWidget(btnSetGeneral);
    mainLayout->addWidget(groupSetting1, 0, Qt::AlignTop);



    status->setMaximumHeight(20);
    mainLayout->addWidget(btnClose, 0, Qt::AlignBottom | Qt::AlignRight);
    mainLayout->addWidget(status, 0, Qt::AlignBottom);

    setLayout(mainLayout);
    status->showMessage("Cài đặt các tham số chung");
    setContentsMargins(6,6,6,6);
}

void Configuration::createContent()
{
    listSignalGenType->addItem(tr("Agilent5182B"));
    listSignalGenType->addItem(tr("Aeroflex2023"));
    listSignalGenType->setCurrentIndex((int)genConfig.sigGenType);

    listSignalGenType->setMinimumHeight(25);
    listSignalGenType->setEditable(true);
    listSignalGenType->lineEdit()->setReadOnly(true);
    listSignalGenType->lineEdit()->setAlignment(Qt::AlignCenter);
    for(int i = 0; i < listSignalGenType->count(); i++) {
        listSignalGenType->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }


    listSpectrumType->addItem(tr("RohdeSchwarzFSV"));
    listSpectrumType->addItem(tr("Aeroflex_Type1"));
    listSpectrumType->setCurrentIndex((int)genConfig.spectType);

    listSpectrumType->setMinimumHeight(25);
    listSpectrumType->setEditable(true);
    listSpectrumType->lineEdit()->setReadOnly(true);
    listSpectrumType->lineEdit()->setAlignment(Qt::AlignCenter);
    for(int i = 0; i < listSpectrumType->count(); i++) {
        listSpectrumType->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    listPowerType->addItem(tr("Agilent_Type1"));
    listPowerType->addItem(tr("Aeroflex_Type1"));
    listPowerType->setCurrentIndex((int)genConfig.powerType);

    listPowerType->setMinimumHeight(25);
    listPowerType->setEditable(true);
    listPowerType->lineEdit()->setReadOnly(true);
    listPowerType->lineEdit()->setAlignment(Qt::AlignCenter);
    for(int i = 0; i < listPowerType->count(); i++) {
        listPowerType->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }


    editLocalIp->setText(QString(genConfig.localIp.c_str()));
    editServerDelay->setText(QString::number(genConfig.serverDelay));
    editSpectDelay->setText(QString::number(genConfig.spectDelay));
    editSiggenDelay->setText(QString::number(genConfig.siggenDelay));
    editBwHigh->setText(QString::number(genConfig.bandwidthHigh));
    editBwLow->setText(QString::number(genConfig.bandwidthLow));

    editLoadFileHigh->setText(QString(genConfig.loadFileHighName.c_str()));
    editLoadFileLow->setText(QString(genConfig.loadFileLowName.c_str()));

    editTestInput->setText(QString(genConfig.inputDir.c_str()));
    editTestOutput->setText(QString(genConfig.outputDir.c_str()));

    formSetting1->setAlignment(btnSelectInput, Qt::AlignRight);
    formSetting1->setAlignment(btnSelectOutput, Qt::AlignRight);
    btnSelectInput->setText("...");
    btnSelectOutput->setText("...");
}

void Configuration::createConnection()
{
    connect(btnClose, SIGNAL(clicked(bool)), this, SLOT(on_Collap()));
    connect(btnSetGeneral, SIGNAL(clicked(bool)), this, SLOT(on_ConfirmSetting()));
    connect(btnSetGeneral, SIGNAL(clicked(bool)), this, SLOT(on_Collap()));
    connect(btnSelectInput, SIGNAL(clicked(bool)), this, SLOT(on_SelectInputPath()));
    connect(btnSelectOutput, SIGNAL(clicked(bool)), this, SLOT(on_SelectOutputPath()));
}


void Configuration::getUserConfig()
{
    genConfig.sigGenType = (SigGenType)listSignalGenType->currentIndex();
    genConfig.spectType  = (SpectrumType)listSpectrumType->currentIndex();
    genConfig.powerType  = (PowerType)listPowerType->currentIndex();
    genConfig.localIp    = editLocalIp->text().toStdString();
    genConfig.loadFileHighName = editLoadFileHigh->text().toStdString();
    genConfig.loadFileLowName = editLoadFileLow->text().toStdString();
    genConfig.siggenDelay = (editSiggenDelay->text().toUInt() >= 200 ? editSiggenDelay->text().toUInt() : 200);
    genConfig.spectDelay = (editSpectDelay->text().toUInt() >= 200 ? editSpectDelay->text().toUInt() : 200 );
    genConfig.serverDelay = (editServerDelay->text().toUInt() >= 200 ? editServerDelay->text().toUInt() : 200);
    genConfig.bandwidthHigh = editBwHigh->text().toUInt();
    genConfig.bandwidthLow = editBwLow->text().toUInt();
    genConfig.inputDir = editTestInput->text().toStdString();
    genConfig.outputDir = editTestOutput->text().toStdString();
}


void Configuration::on_Collap()
{
    setExpanded(false);
}

void Configuration::on_ConfirmSetting()
{
    getUserConfig();
    UiConfig::getInstance()->saveGeneralSigGenType(genConfig.sigGenType);
    UiConfig::getInstance()->saveGeneralSpectrumType(genConfig.spectType);
    UiConfig::getInstance()->saveGeneralPowerType(genConfig.powerType);
    UiConfig::getInstance()->saveGeneralLocalIp(genConfig.localIp);
    UiConfig::getInstance()->saveGeneralLocalPort(genConfig.localPort);
    UiConfig::getInstance()->saveGeneralFileNameHigh(genConfig.loadFileHighName);
    UiConfig::getInstance()->saveGeneralFileNameLow(genConfig.loadFileLowName);
    UiConfig::getInstance()->saveGeneralSigGenDelay(genConfig.siggenDelay);
    UiConfig::getInstance()->saveGeneralSpectrumDelay(genConfig.spectDelay);
    UiConfig::getInstance()->saveGeneralServerDelay(genConfig.serverDelay);
    UiConfig::getInstance()->saveGeneralBandwidthHigh(genConfig.bandwidthHigh);
    UiConfig::getInstance()->saveGeneralBandwidthLow(genConfig.bandwidthLow);
    UiConfig::getInstance()->saveGeneralTabUsed(genConfig.tabUsed);
    UiConfig::getInstance()->saveGeneralInputDir(genConfig.inputDir);
    UiConfig::getInstance()->saveGeneralOutputDir(genConfig.outputDir);
}

void Configuration::on_SelectInputPath()
{
    QString dir;
    if(genConfig.inputDir != "") {
        dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    QString(genConfig.inputDir.c_str()),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    } else {
        dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    QDir::homePath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    }

    if(dir != "") {
        editTestInput->setText(dir);
        genConfig.inputDir = dir.toStdString();
    }
}

void Configuration::on_SelectOutputPath()
{
    QString dir;
    if(genConfig.outputDir != "") {
        dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    QString(genConfig.outputDir.c_str()),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    } else {
        dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    QDir::homePath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    }

    if(dir != "") {
        editTestOutput->setText(dir);
        genConfig.outputDir = dir.toStdString();
    }
}


