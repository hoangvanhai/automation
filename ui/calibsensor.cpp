#include "calibsensor.h"
#include <iostream>
#include <protocol/client_msg/msg.pb.h>
#include <isc/utils.h>

using namespace cppframework;
/**
 * @brief CalibSensor::CalibSensor create all ui element,
 *                  load configuration and create connection
 * @param parent
 */
CalibSensor::CalibSensor(Controller *controller, TestBase *parent) :
    TestBase(controller, parent)
{
    initVariable();
    createUiElem();
    createLayout();
    createElemContent();
    createConnection();
    startTestFrame();
    on_btnLoadTestParamClicked();
}

/**
 * @brief CalibSensor::~CalibSensor
 */
CalibSensor::~CalibSensor()
{
    //if(isSaveCfg)
}

void CalibSensor::initVariable()
{

    changeMiss = true;
    testTrackerFile = CONFIG_TEST_TRACK_SENSOR;
    outputFileName = "CALIB_RESULT";
    LoadCalibConfig();
    LoadTestTracker();
    LoadGenConfig();
    isSaveCfg = false;
}

void CalibSensor::createUiElem()
{

    groupConfig = new QGroupBox(tr("CÀI ĐẶT"));

    labelInstrIp = new QLabel("ĐỊA CHỈ SIGNAL GEN");
    editInstrIp = new QLineEdit;
    labelServerIp = new QLabel("ĐỊA CHỈ SERVER");
    editServerIp = new QLineEdit;
    btnConnectInstr = new QPushButton("KẾT NỐI");
    btnConnectServer = new QPushButton("KẾT NỐI");

    comCalibMode = new QComboBox;

    tableView = new QTableView(this);
    mainLayout = new QVBoxLayout;
    settingLayout = new QFormLayout;
    hLayout = new QHBoxLayout;

    labelHeader = new QLabel("CALB CÔNG SUẤT TỰ ĐỘNG SENSOR");
    btnTest = new QPushButton("Xóa log");
    btnStartTest = new QPushButton("BẮT ĐẦU");

    labelSerial = new QLabel("SERIAL");
    editSerial = new QLineEdit;


    labelWhoTest = new QLabel("NGƯỜI TEST");
    editWhoTest = new QLineEdit;

    labelResult = new QLabel("TRẠNG THÁI");
    manLayout = new QFormLayout;
    mainSettingLayout = new QVBoxLayout;

    groupSetting = new QGroupBox("CÀI ĐẶT");
    groupMan = new QGroupBox("THAO TÁC");

    editInstrPort = new QLineEdit;
    editServerPort  = new QLineEdit;
    editServerUdpPort = new QLineEdit;

    labelSslStatus = new QLabel("KHÔNG KẾT NỐI");
    labelInstrStatus = new QLabel("KHÔNG KẾT NỐI");

    labelProgress = new QLabel("TIẾN TRÌNH");
    progressCalib = new QProgressBar;

    editTest = new QTextEdit;

}

void CalibSensor::createLayout()
{

    settingLayout->addRow(labelInstrIp, editInstrIp);
    settingLayout->addRow("CỔNG TCP", editInstrPort);
    settingLayout->addRow("TRẠNG THÁI", labelInstrStatus);
    labelInstrStatus->setStyleSheet("QLabel {color : red; }");
    settingLayout->addRow("SIGNAL GENERATOR", btnConnectInstr);
    settingLayout->addItem(new QSpacerItem(0, 10));
    settingLayout->addRow(labelServerIp, editServerIp);
    settingLayout->addRow("CỔNG TCP", editServerPort);
    //settingLayout->addRow("CỔNG UDP", editServerUdpPort);
    settingLayout->addRow("TRẠNG THÁI", labelSslStatus);
    labelSslStatus->setStyleSheet("QLabel {color : red; }");
    settingLayout->addRow("SERVER", btnConnectServer);
    settingLayout->addItem(new QSpacerItem(0, 10));
    //manLayout->addRow(labelWhoTest, editWhoTest);
    manLayout->addRow("CHẾ ĐỘ CALIB", comCalibMode);
    manLayout->addRow(labelSerial, editSerial);
    manLayout->addWidget(btnStartTest);
    manLayout->addWidget(labelProgress);
    manLayout->addRow(progressCalib);
    manLayout->addRow(editTest);
    manLayout->addWidget(btnTest);


    settingLayout->setHorizontalSpacing(1);
    btnStartTest->setFixedHeight(40);


    labelHeader->setAlignment(Qt::AlignCenter);
    labelHeader->setStyleSheet(QLatin1String("font: 18pt \"Times New Roman\";"));
    QPalette palette;
    palette.setColor(QPalette::WindowText, QColor(Qt::white));
    labelHeader->setPalette(palette);

    groupSetting->setLayout(settingLayout);
    groupMan->setLayout(manLayout);

    mainSettingLayout->addWidget(groupSetting);
    mainSettingLayout->addWidget(groupMan);

    groupSetting->setFixedWidth(300);
    groupMan->setFixedWidth(300);
    hLayout->addWidget(tableView);
    hLayout->addLayout(mainSettingLayout, Qt::AlignRight);
    mainLayout->addWidget(labelHeader);
    mainLayout->addLayout(hLayout);
    setLayout(mainLayout);
}

void CalibSensor::createElemContent()
{
    createTableViewHeader();

    comCalibMode->addItem(tr("NHIỆT ĐỘ THƯỜNG"));
    comCalibMode->addItem(tr("NHIỆT ĐỘ NÓNG"));
    comCalibMode->addItem(tr("NHIỆT ĐỘ LẠNH"));

    //comCalibMode->setMinimumHeight(25);
    comCalibMode->setEditable(true);
    comCalibMode->lineEdit()->setReadOnly(true);
    comCalibMode->lineEdit()->setAlignment(Qt::AlignCenter);
    for(int i = 0; i < comCalibMode->count(); i++) {
        comCalibMode->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    editInstrIp->setAlignment(Qt::AlignCenter);
    editInstrPort->setAlignment(Qt::AlignCenter);
    editInstrPort->setFixedWidth(50);
    labelInstrStatus->setAlignment(Qt::AlignCenter);

    editServerIp->setAlignment(Qt::AlignCenter);
    editServerPort->setAlignment(Qt::AlignCenter);
    editServerUdpPort->setAlignment(Qt::AlignCenter);
    editServerPort->setFixedWidth(50);
    editServerUdpPort->setFixedWidth(50);
    labelSslStatus->setAlignment(Qt::AlignCenter);

    editInstrIp->setText(QString(m_calibSenCfg.SigGenIp.c_str()));
    editInstrPort->setText(QString::number(m_calibSenCfg.siggenPort));
    editServerIp->setText(QString(m_calibSenCfg.ServerIp.c_str()));
    editServerPort->setText(QString::number(m_calibSenCfg.sslPort));
    editServerUdpPort->setText(QString::number(m_calibSenCfg.udpPort));

    editSerial->setText("VI0989681001");
    editSerial->setAlignment(Qt::AlignCenter);
    editSerial->setFixedHeight(30);
    labelSerial->setFixedHeight(30);
    editSerial->setStyleSheet(QLatin1String("font: 12pt;"));

    editWhoTest->setText("Trương Văn Toán");
    editWhoTest->setAlignment(Qt::AlignCenter);

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    progressCalib->setMaximum(100);
    editTest->setText("Log data");
}

void CalibSensor::createTableViewHeader()
{
    tableView->setWordWrap(true);
    QStringList header;

    header << "Công suất máy phát (dBm)" << "Tần số máy phát (Hz)" << "Công suất thu được (dBm)" << "Tần số thu được (Hz)" << "Thông tin";
    model->setHorizontalHeaderLabels(header);

    tableView->setModel(model);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setColumnWidth(0, 200);
    tableView->setColumnWidth(1, 200);
    tableView->setColumnWidth(2, 200);
    tableView->setColumnWidth(3, 200);
    tableView->setColumnWidth(4, 200);
}

void CalibSensor::createConnection()
{
    /**
     * @brief button connection
     */
    connect(btnStartTest, SIGNAL(clicked(bool)), this, SLOT(on_btnStartTestClicked()));
    connect(btnConnectServer, SIGNAL(clicked(bool)), this, SLOT(on_btnConnectServerClicked()));
    connect(btnConnectInstr, SIGNAL(clicked(bool)), this, SLOT(on_btnConnectSignalGenClicked()));

    /**
     * @brief test
     */
    connect(btnTest, SIGNAL(clicked(bool)), this, SLOT(on_btnTestClicked()));

    connect(this, SIGNAL(displayRow(QStringList)), this, SLOT(AppendRowTable(QStringList)));

    /**
     * @brief user edit parameter update
     */
    connect(editServerIp, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(editServerPort, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(editServerUdpPort, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(editInstrIp, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(editInstrPort, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));        

    connect(this, SIGNAL(updateProgress(int)), this, SLOT(ShowProgress(int)));
}



/**
 * @brief CalibSensor::StartTestSuite
 */


/**
 * @brief CalibSensor::GetTestState
 * @return
 */


void CalibSensor::InitTestResult()
{
    LoadGenConfig();
    control->Server_SetNoiseFloor(0, 15);
    control->Server_SetServerOperationMode(Server_Normal);
    //control->Server_SetServerOperationMode(Server_Calibration);
    testResult.calibResult.clear();
    lineCalib = 0;    
    model->setRowCount(0);
    if(comCalibMode->currentText() == "NHIỆT ĐỘ THƯỜNG") {
        calibMode = Calib_Mode_Normal;
        labelHeader->setText("CALIB TỰ ĐỘNG SENSOR NHIỆT ĐỘ THƯỜNG");
    } else if(comCalibMode->currentText() == "NHIỆT ĐỘ NÓNG")  {
        calibMode = Calib_Mode_Hot;
        labelHeader->setText("CALIB TỰ ĐỘNG SENSOR NHIỆT ĐỘ NÓNG");
    } else if(comCalibMode->currentText() == "NHIỆT ĐỘ LẠNH")  {
        calibMode = Calib_Mode_Cool;
        labelHeader->setText("CALIB TỰ ĐỘNG SENSOR NHIỆT ĐỘ LẠNH");
    }
    emit updateProgress(0);

    maxLine = 0;
    for(auto test : testHead) {
        if(test.first ==  1) {
            maxLine += int((FREQ_END_FREQ - FREQ_START_FREQ) / testParam.line1.step + 1);
        } else if(test.first ==  2) {
            maxLine += int((FREQ_END_FREQ - FREQ_START_FREQ) / testParam.line2.step + 1);
        } else if(test.first ==  3) {
            maxLine += int((FREQ_END_FREQ - FREQ_START_FREQ) / testParam.line3.step + 1);
        }
    }
    LREP("MAX LINE: {}\n", maxLine);
}

/**
 * @brief CalibSensor::DoTestLine
 */
void CalibSensor::DoTestLine(CalibParam &param)
{
    double freq = FREQ_START_FREQ;
    double currentMiss;
    FreqPoint prev;

    control->SigGen_SetCombo(freq, Freq_Mhz,
                            param.power, Power_dBm,
                            1.0, Freq_Khz,
                            genConfig.siggenDelay);

    control->Server_SetGain(0, 31.5);
    currentMiss = freq + 40;
    control->Server_SetRecvFreq(freq, BW_40_MHZ, 0);

    while(freq <= FREQ_END_FREQ && IsKeepgoingOnTest()) {
        emit updateStatusBar("Đang calib tần: " +
                             QString::number(freq, 'g', 10) + " Mhz" +
                             " công suất " + QString::number(param.power, 'g', 10) );
        control->SigGen_SetRFFreq(freq, Freq_Mhz, genConfig.siggenDelay);
        control->Server_ClearSignaListReceived();
        control->SigGen_SetRFSignalOut(true, genConfig.siggenDelay);
        control->currFreqExp = freq * 1E6;
        if(changeMiss) {
            control->Server_SetRecvFreq(freq, BW_40_MHZ, 0);
        } else {
            if(freq >= currentMiss) {
                currentMiss = freq + 40.0;
                control->Server_SetRecvFreq(currentMiss - 20.0, BW_40_MHZ, 0);
            }
        }

        FreqPoint check = {0, 1000.0};
        if (CALIB_RESET_VAL) {
            TestSuiteDelay(genConfig.serverDelay);
            check.point = freq * 1E6;
            check.value = param.power;
        } else {
            uint32_t count = genConfig.serverDelay / 100;
            do {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                check = control->Server_CheckCalibSignal((uint64_t(freq * 1E6)), 1000);
            }while(IsKeepgoingOnTest() && (count--) && check.value == 1000.0);
        }
        if(check.value != 1000.0) {
            displayLineValue(param.power, freq * 1E6, check.value, check.point);
            check.value = param.power - check.value;
            testResult.calibResult.push_back(check);
            prev = check;
        } else {
            displayNA(param.power, freq * 1E6);
            testResult.calibResult.push_back(prev);
        }
        lineCalib++;
        freq += param.step;
        control->SigGen_SetRFSignalOut(false, genConfig.siggenDelay);
        emit updateProgress(lineCalib);
    }
}


/**
 * @brief CalibSensor::DoTestSuiteFunction
 */
void CalibSensor::DoTestSuiteFunction()
{
    while(!doTestSuiteTerm) {
        if(IsKeepgoingOnTest()) {
            InitTestResult();
            LREP("/--------------------------------------/\n");
            //emit clearColumData(STATUS_IN_COLUM, testHead.size() + 1, 0); // Clear include TOTAL result
            std::map<int, ComParam>::iterator iter = testHead.begin();
            LREP("testSize: {}\n\n", testHead.size());
            currLineResult = 20;
            while(iter != testHead.end()) {
                if(!IsKeepgoingOnTest())
                    break;
                std::pair<int, ComParam> test = *iter;                
                if(test.second.name == CALIB_STR_TEST_1 && test.second.enable == true ) {
                    LREP("__________ TEST LINE1 _________\n");
                    DoTestLine(testParam.line1);
                } else if(test.second.name == CALIB_STR_TEST_2 && test.second.enable == true ) {
                    LREP("__________ TEST LINE2 _________\n");
                    DoTestLine(testParam.line2);
                } else if(test.second.name == CALIB_STR_TEST_3 && test.second.enable == true ) {
                    LREP("__________ TEST LINE3_________\n");
                    DoTestLine(testParam.line3);
                }                
                iter++; // Go to next test point
            }
            if(GetTestState() == TestState_Running) {
                StopAllTest();                
                LREP("ĐÃ KẾT THÚC BÀI ĐO\n");
                if(testResult.calibResult.size() == (size_t)maxLine) {
                    //control->Server_SaveCalibTable(calibMode, testResult.calibResult);
                    emit updateStatusBar("ĐÃ KẾT THÚC CALIB ĐỦ TẦN SỐ");
                } else {
                    emit updateStatusBar("ĐÃ KẾT THÚC CALIB -> THIẾU TẦN SỐ !!!");
                }
                //emit updateProgress(maxLine);
            } else {
                LREP("TEST TERMINATED BY EXTERNAL\n");
                emit updateStatusBar("ĐÃ DỪNG CALIB ");
                StopAllTest();
            }
            btnStartTest->setText("BẮT ĐẦU");
            btnStartTest->setEnabled(true);
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}


void CalibSensor::StopAllTest(bool save)
{    
    StopTestSuite(save);
    control->SigGen_DeSetCombo();
    EnableSettingPanel(true);
    control->Server_SetServerOperationMode(Server_Normal);
}

void CalibSensor::StartAllTest(const QString &serial, const QString &who)
{
    control->SigGen_InitDevice();
    StartTestSuite("CALIB_SENSOR_TEMPLATE.xlsx", serial, who);
    SetTestState(TestState_Running);
    EnableSettingPanel(false);
    btnStartTest->setText("DỪNG");
}


void CalibSensor::displayNA(double genPower, uint64_t genFreq)
{
    QStringList row;
    QString col2;

    col2 = InsertDot(genFreq);

    row << QString::number(genPower, 'g', 10) << col2 << "N/A" << "N/A";
    emit displayRow(row);
}

void CalibSensor::displayLineValue(double genPower, uint64_t genFreq, float recPower, uint64_t recFreq)
{

    QStringList row;
    QString col2, col4;

    col2 = InsertDot(genFreq);
    col4 = InsertDot(recFreq);

    row << QString::number(genPower, 'g', 10) << col2 <<
           QString::number(recPower, 'g', 10) << col4;
    emit displayRow(row);
    if(!resFile)
        return;

    resFile->write("A" + QString::number(currLineResult), QString::number(currLineResult - 20));
    resFile->write("B" + QString::number(currLineResult), QString::number(genPower, 'g', 10));
    resFile->write("D" + QString::number(currLineResult), col2);
    resFile->write("E" + QString::number(currLineResult), QString::number(recPower, 'g', 10));
    resFile->write("F" + QString::number(currLineResult), col4);
    currLineResult++;
}



void CalibSensor::on_updateUserSetting()
{
    GetUserConfig();
    SaveCalibConfig();
    isSaveCfg = true;
}


void CalibSensor::on_btnTestClicked()
{
    editTest->clear();


//    if(editTest->toPlainText() == "0") {
//        control->SigGen_InitDevice();
//    } else if(editTest->toPlainText() == "1") {
//        control->SigGen_SetTwoTone(1484, Freq_Mhz, 2, Freq_Mhz, -30, Power_dBm, genConfig.siggenDelay);
//    }
}



void CalibSensor::on_btnStartTestClicked()
{
    if(GetTestState() == TestState_Stop){
        if(!isTestParmLoaded) {
            QMessageBox::warning(this, "Lỗi", "Lỗi nạp tham số calib\nkiểm tra lại file đầu vào !");
            return;
        }

//        if(control->SigGen_GetStatus() != communication::Event_Connected) {
//            QMessageBox::warning(this, "Lỗi", "Chưa kết nối máy signal generator !");
//            return;
//        }

//        if(control->Server_GetStatus() != communication::Event_Connected) {
//            QMessageBox::warning(this, "Lỗi", "Chưa kết nối server !");
//            return;
//        }

        StartAllTest(editSerial->text(), editWhoTest->text());
        if(comCalibMode->currentText() == "NHIỆT ĐỘ THƯỜNG") modeLoaded = "_THUONG";
        else if(comCalibMode->currentText() == "NHIỆT ĐỘ NÓNG") modeLoaded = "_NONG";
        else if(comCalibMode->currentText() == "NHIỆT ĐỘ LẠNH") modeLoaded = "_LANH";

    } else if(GetTestState() == TestState_Running) {
        totalTestRes = "_FAIL";
        SetTestState(TestState_RequestStop);
        btnStartTest->setText("ĐANG DỪNG");
        btnStartTest->setEnabled(false);
    } else {
        LREP("Request stop\n");
    }
}

void CalibSensor::on_btnConnectServerClicked()
{
    if(control->Server_GetStatus() == communication::Event_Connected ||
            control->Server_GetStatus() == communication::Event_Connecting) {

        LREP("USER Stop ssl client\n");
        control->Server_StopSslClient();        
    } else {
        ConfigController();
        LREP("USER Start ssl client\n");
        control->Server_StartSslClient();
    }

}

void CalibSensor::on_btnConnectSignalGenClicked()
{

    if(control->SigGen_GetStatus() == communication::Event_Connected ||
            control->SigGen_GetStatus() == communication::Event_Connecting) {
        LREP("USER Stop instr\r\n");
        control->SigGen_Stop();
    } else {
        ConfigController();
        LREP("USER Start instr\r\n");
        control->SigGen_Start();
    }
}



void CalibSensor::on_SslClientConnectEvent(int evt)
{
    if(evt == communication::Event_Connected) {
        labelSslStatus->setStyleSheet("QLabel {color : green; }");
    }else {
        labelSslStatus->setStyleSheet("QLabel {color : red; }");
    }
    switch(evt) {
        case communication::Event_Connected:
        LREP("Event Connected to server\r\n");
        btnConnectServer->setText("NGẮT KẾT NỐI");
        labelSslStatus->setText("ĐÃ KẾT NỐI");
        break;
    case communication::Event_Disconnected:
        LREP("Event Disconnected to server\r\n");
        btnConnectServer->setText("KẾT NỐI");
        labelSslStatus->setText("KHÔNG KẾT NỐI");
        StopAllTest(false);
        break;
    case communication::Event_Connecting:
        LREP("Event Connecting to server\r\n");
        labelSslStatus->setText("ĐANG THỬ KẾT NỐI");
        btnConnectServer->setText("NGẮT KẾT NỐI");
        break;
    case communication::Event_Network_Down:
        LREP("Event break connection with server\r\n");
        labelSslStatus->setText("KHÔNG KẾT NỐI");
        btnConnectServer->setText("KẾT NỐI");
        control->Server_StopSslClient();
        //control->Server_StopUdpClient();
        StopAllTest(false);
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy server !");
        break;
    case communication::Event_Error:
        LREP("Event Connection error \r\n");
        labelSslStatus->setText("LỖI");
        QMessageBox::warning(this, "Lỗi", "Lỗi hệ thống !");
        break;

    default:
        break;

    }
}




void CalibSensor::on_SiggenConnectEvent(int evt)
{
    if(evt == communication::Event_Connected) {
        labelInstrStatus->setStyleSheet("QLabel {color : green; }");
    }else {
        labelInstrStatus->setStyleSheet("QLabel {color : red; }");
    }
    switch(evt) {
        case communication::Event_Connected:
        LREP("Event Connected to server\r\n");
        btnConnectInstr->setText("NGẮT KẾT NỐI");
        labelInstrStatus->setText("ĐÃ KẾT NỐI");
        break;
    case communication::Event_Disconnected:
        LREP("Event Disconnected to siggen\r\n");
        btnConnectInstr->setText("KẾT NỐI");
        labelInstrStatus->setText("KHÔNG KẾT NỐI");
        StopAllTest(false);
        break;
    case communication::Event_Connecting:
        LREP("Event Agilent5182 connecting\r\n");
        labelInstrStatus->setText("ĐANG THỬ KẾT NỐI");
        btnConnectInstr->setText("NGẮT KẾT NỐI");
        break;
    case communication::Event_Network_Down:
        LREP("Event Network Down to server\r\n");
        btnConnectInstr->setText("KẾT NỐI");
        labelInstrStatus->setText("KHÔNG KẾT NỐI");
        control->SigGen_Stop();
        StopAllTest(false);
        QMessageBox::warning(this, "Lỗi", "Mất kết nối máy Sigal generator !");
        break;
    default:
        break;

    }
}

void CalibSensor::on_DataReceived(quint64 data)
{
    quint64 high, low;
    QString result = "";
    high = data / 1000000;
    low = data % 1000000;
    if(high > 0) {
        result = QString::number(high) + ".";
    }
    result = result + QString::number(low);
    editTest->insertPlainText(result + " ");
    QTextCursor c = editTest->textCursor();
    c.movePosition(QTextCursor::End);
    editTest->setTextCursor(c);
}


bool CalibSensor::loadTestParam(const CSVFile::CsvVector &data)
{    
    if(!data.size())
      return false;

    ComParam head;
    //LREP("Clear all test param before load the new !\n");
    clearInputParam();

    for(auto row : data) {
        if(row.size() < 6) {
            return false;
        }
    }

    CSVFile::CsvVector::const_iterator iter;
    for(iter = data.begin(); iter != data.end(); ++iter){
        std::vector<std::string> row = *iter;
        if(row.size() > 0) {
            if(row.at(1) == CALIB_STR_TEST_1) {
                head.name = CALIB_STR_TEST_1;
                head.enable = (row.at(2) == "TRUE" || row.at(2) == "true") ? true : false;
                if(head.enable) {
                    int order = cppframework::str::Util::convert<int>(row.at(3), 1);
                    addTestCase(order, head);
                    testParam.line1.power = str::Util::convert<double>(row.at(4), 0);
                    testParam.line1.step = str::Util::convert<double>(row.at(5), 0);
                }
            }else if(row.at(1) == CALIB_STR_TEST_2) {
                head.name = CALIB_STR_TEST_2;
                head.enable = (row.at(2) == "TRUE" || row.at(2) == "true") ? true : false;
                if(head.enable) {
                    int order = cppframework::str::Util::convert<int>(row.at(3), 1);
                    addTestCase(order, head);
                    testParam.line2.power = str::Util::convert<double>(row.at(4), 0);
                    testParam.line2.step = str::Util::convert<double>(row.at(5), 0);
                }
            }else if(row.at(1) == CALIB_STR_TEST_3) {
                head.name = CALIB_STR_TEST_3;
                head.enable = (row.at(2) == "TRUE" || row.at(2) == "true") ? true : false;
                if(head.enable) {
                    int order = cppframework::str::Util::convert<int>(row.at(3), 1);
                    addTestCase(order, head);
                    testParam.line3.power = str::Util::convert<double>(row.at(4), 0);
                    testParam.line3.step = str::Util::convert<double>(row.at(5), 0);
                }
            }
        }
    }
    return true;
}

void CalibSensor::clearInputParam()
{
    testHead.clear();
}


/*
 *
 *
 *
*/
void CalibSensor::on_btnLoadTestParamClicked()
{
    isTestParmLoaded = LoadTestConfigFromFile();
}

/*
 *
 *
 *
*/
bool CalibSensor::LoadTestConfigFromFile()
{
    bool ret = false;
    modeLoaded = "";
    std::string          externalFile = genConfig.inputDir;

    externalFile += ("/sensor/calibsensor.csv");
    if(loadTestConfig(externalFile)) {        
        if(loadTestParam(loader->rows())) {
            ret =  true;
        } else {
            QMessageBox::warning(this, "Lỗi", "Nội dung file không hợp lệ: " + QString(externalFile.c_str()));
            ret = false;
        }
        //loadTestParamToUi();
    } else {
        QMessageBox::warning(this, "Lỗi mở file", "Không tìm thấy file" + QString(externalFile.c_str()));
        ret = false;
    }
    loader.reset();
    return ret;
}

void CalibSensor::AppendRowTable(QStringList row)
{
    int index = 0;
    QList<QStandardItem *> items;
    QStringList::iterator iter = row.begin();    
    while(iter != row.end()) {
        QString text = *iter;
        QStandardItem *item = new QStandardItem(text);
        if(index == 1 || index == 3)
        {
            item->setTextAlignment(Qt::AlignRight);
        } else {
            item->setTextAlignment(Qt::AlignCenter);
        }

        items.append(item);
        index++;
        iter++;
    }

    model->appendRow(items);    

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    tableView->scrollToBottom();

}

void CalibSensor::ShowProgress(int value)
{    
    progressCalib->setValue(((float)value / maxLine) *100);
    if(progressCalib->value() == 100) {
        if(testResult.calibResult.size() == (size_t)maxLine) {
            QMessageBox::information(this, "Thông báo", "Kết thúc calib");
        } else {
            QMessageBox::information(this, "Thông báo", "Kết thúc calib thiếu tần số");
        }
    }
}

void CalibSensor::ConfigController()
{
    /**
     * @brief connection event
     */
    control->addConnection(connect(control, SIGNAL(sigServerStatus(int)), this, SLOT(on_SslClientConnectEvent(int))));
    control->addConnection(connect(control, SIGNAL(sigSigGenStatus(int)), this, SLOT(on_SiggenConnectEvent(int))));
    control->addConnection(connect(control, SIGNAL(sigSignalRecv(quint64)),this, SLOT(on_DataReceived(quint64))));

    GeneralConfig genConfig = UiConfig::getInstance()->getGeneralConfig();

    if(control) {
        control->ConfigSslClient(m_calibSenCfg.ServerIp, m_calibSenCfg.sslPort);
        control->ConfigUdp(m_calibSenCfg.ServerIp, m_calibSenCfg.udpPort);
        control->ConfigSigGen(m_calibSenCfg.SigGenIp, m_calibSenCfg.siggenPort);
        if(genConfig.localIp != "") {
            //LREP("Setup this machine ip: {}\n", genConfig.localIp);
            control->SetLocalIp(genConfig.localIp);
        } else {
            LREP_WARN("Setup this machine ip: DEFAULT_LOCAL_IP\n");
            control->SetLocalIp(DEFAULT_LOCAL_IP);
        }

        control->SetSigenType((SigGenType)genConfig.sigGenType);
        control->SetSpectType((SpectrumType)genConfig.spectType);
        control->SetPowerType((PowerType)genConfig.powerType);
    }
}

void CalibSensor::EnableSettingPanel(bool en)
{
    btnConnectInstr->setEnabled(en);
    btnConnectServer->setEnabled(en);
    editSerial->setEnabled(en);
    comCalibMode->setEnabled(en);
}

void CalibSensor::PrintGeneralConfig()
{
    LREP("server ip: {}\n", m_calibSenCfg.ServerIp);
    LREP("server port: {}\n", m_calibSenCfg.sslPort);
    LREP("server udp port: {}\n", m_calibSenCfg.udpPort);
    LREP("instr ip: {}\n", m_calibSenCfg.SigGenIp);
    LREP("instr port: {}\n", m_calibSenCfg.siggenPort);
}

void CalibSensor::LoadCalibConfig()
{
    m_calibSenCfg = UiConfig::getInstance()->getCalibSenConfig();
}

void CalibSensor::SaveCalibConfig()
{    
    UiConfig::getInstance()->saveCalibSensorServerAddress(m_calibSenCfg.ServerIp);
    UiConfig::getInstance()->saveCalibSensorServerSslPort(m_calibSenCfg.sslPort);
    UiConfig::getInstance()->saveCalibSensorServerUdpPort(m_calibSenCfg.udpPort);
    UiConfig::getInstance()->saveCalibSensorSigGenIp(m_calibSenCfg.SigGenIp);
    UiConfig::getInstance()->saveCalibSensorSigGenPort(m_calibSenCfg.siggenPort);
}


void CalibSensor::GetUserConfig()
{
    m_calibSenCfg.SigGenIp = editInstrIp->text().toStdString();
    m_calibSenCfg.siggenPort = editInstrPort->text().toUShort();
    m_calibSenCfg.ServerIp = editServerIp->text().toStdString();
    m_calibSenCfg.sslPort = editServerPort->text().toUShort();
    m_calibSenCfg.udpPort = editServerUdpPort->text().toUShort();
}

