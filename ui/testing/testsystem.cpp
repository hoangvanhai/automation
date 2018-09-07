#include "testsystem.h"
#include <iostream>
#include <protocol/client_msg/msg.pb.h>
#include <isc/utils.h>

using namespace cppframework;
/**
 * @brief TestSystem::TestSystem create all ui element,
 *                  load configuration and create connection
 * @param parent
 */
TestSystem::TestSystem(Controller *controller, TestBase *parent) :
    TestBase(controller, parent)
{
    initVariable();
    createUiElem();
    createLayout();
    createElemContent();
    createConnection();
    startTestFrame();
}

/**
 * @brief TestSystem::~TestSystem
 */
TestSystem::~TestSystem()
{
    if(m_mapView != Q_NULLPTR) {
        m_mapView->activateWindow();
        on_mapClose();
   }
}

void TestSystem::initVariable()
{
    testTrackerFile = CONFIG_TEST_TRACK_SYSTEM;
    outputFileName = FILENAME_RES_SYSTEM;
    LoadSystemConfig();
    LoadTestTracker();
    LoadGenConfig();
    isSaveCfg = false;
    m_mapView = Q_NULLPTR;
}

void TestSystem::createUiElem()
{
    groupConfig = new QGroupBox(tr("CÀI ĐẶT"));
    comboTestMode   = new QComboBox;
    labelTestMode = new QLabel("CHỌN CHẾ ĐỘ");

    editServerIp = new QLineEdit;
    btnConnectRfDelay = new QPushButton("KẾT NỐI");
    btnConnectServer = new QPushButton("KẾT NỐI");

    tableView = new QTableView(this);
    mainLayout = new QVBoxLayout;
    settingLayout = new QFormLayout;
    hLayout = new QHBoxLayout;

    labelHeader = new QLabel("ĐO KIỂM TỰ ĐỘNG CHỈ TIÊU HỆ THỐNG");
    btnLoadMap =  new QPushButton("BẢN ĐỒ");
    btnLoadTestParam = new QPushButton("NẠP THAM SỐ ĐO");
    btnTest = new QPushButton("Xóa log");
    btnStartTest = new QPushButton("BẮT ĐẦU");
    checkKeepTest = new QCheckBox;
    labelCheckKeep = new QLabel("TIẾP TỤC NẾU FAIL");

    labelSerial = new QLabel("SERIAL");
    editSerial = new QLineEdit;

    checkRetestIfFailed = new QCheckBox;

    labelWhoTest = new QLabel("NGƯỜI TEST");
    editWhoTest = new QLineEdit;

    manLayout = new QFormLayout;
    mainSettingLayout = new QVBoxLayout;

    groupSetting = new QGroupBox("CÀI ĐẶT");
    groupMan = new QGroupBox("THAO TÁC");

    comSerialList = new QComboBox;

    editServerPort  = new QLineEdit;
    editServerUdpPort = new QLineEdit;

    labelSslStatus = new QLabel("KHÔNG KẾT NỐI");

    labelTestRunNum = new QLabel(" ");
    labelTestPassNum = new QLabel(" ");

    editTest = new QTextEdit;

    progS0 = new QProgressBar;
    progS1 = new QProgressBar;
    progS2 = new QProgressBar;
    progS3 = new QProgressBar;

    labelS0 = new QLabel("Trạng thái");
    labelS1 = new QLabel("Trạng thái");
    labelS2 = new QLabel("Trạng thái");
    labelS3 = new QLabel("Trạng thái");

}

void TestSystem::createLayout()
{
    settingLayout->addRow(btnLoadMap);
    settingLayout->addRow(btnLoadTestParam);
    settingLayout->addItem(new QSpacerItem(0, 10));
    settingLayout->addRow("KẾT NỐI RFDELAY", comSerialList);
    settingLayout->addRow("RFDELAY", btnConnectRfDelay);
    settingLayout->addItem(new QSpacerItem(0, 10));
    settingLayout->addRow("ĐỊA CHỈ SERVER", editServerIp);
    settingLayout->addRow("CỔNG TCP", editServerPort);
    settingLayout->addRow("CỔNG UDP", editServerUdpPort);
    settingLayout->addRow("TRẠNG THÁI", labelSslStatus);
    labelSslStatus->setStyleSheet("QLabel {color : red; }");
    settingLayout->addRow("SERVER", btnConnectServer);
    settingLayout->addItem(new QSpacerItem(0, 10));
    settingLayout->addRow(labelCheckKeep, checkKeepTest);
    settingLayout->addRow("CHẠY LẠI NẾU FAIL", checkRetestIfFailed);

    manLayout->addRow("SỐ LƯỢNG TEST", labelTestRunNum);
    manLayout->addRow("SỐ LƯỢNG PASS", labelTestPassNum);
    manLayout->addRow(labelWhoTest, editWhoTest);
    manLayout->addRow(labelSerial, editSerial);
    manLayout->addWidget(btnStartTest);

    manLayout->addRow(new QLabel("SENSOR 0"));
    manLayout->addRow(labelS0, progS0);

    manLayout->addRow(new QLabel("SENSOR 1"));
    manLayout->addRow(labelS1, progS1);

    manLayout->addRow(new QLabel("SENSOR 2"));
    manLayout->addRow(labelS2, progS2);

    manLayout->addRow(new QLabel("SENSOR 3"));
    manLayout->addRow(labelS3, progS3);

    settingLayout->setHorizontalSpacing(1);
    btnStartTest->setFixedHeight(40);

    settingLayout->setAlignment(checkKeepTest, Qt::AlignCenter);
    settingLayout->setAlignment(checkRetestIfFailed, Qt::AlignCenter);


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

void TestSystem::createElemContent()
{
    createTableViewHeader();

    editServerIp->setAlignment(Qt::AlignCenter);
    editServerPort->setAlignment(Qt::AlignCenter);
    editServerUdpPort->setAlignment(Qt::AlignCenter);
    editServerPort->setFixedWidth(50);
    editServerUdpPort->setFixedWidth(50);
    labelSslStatus->setAlignment(Qt::AlignCenter);

    editServerIp->setText(QString(m_systemConfig.ServerIp.c_str()));
    editServerPort->setText(QString::number(m_systemConfig.sslPort));
    editServerUdpPort->setText(QString::number(m_systemConfig.udpPort));

    labelTestRunNum->setText(QString::number(testTracker.testRun));
    labelTestPassNum->setText(QString::number(testTracker.testPass));
    labelTestRunNum->setAlignment(Qt::AlignCenter);
    labelTestPassNum->setAlignment(Qt::AlignCenter);

    editSerial->setText("VI0989681001");
    editSerial->setAlignment(Qt::AlignCenter);
    editSerial->setFixedHeight(30);
    labelSerial->setFixedHeight(30);
    editSerial->setStyleSheet(QLatin1String("font: 12pt;"));

    editWhoTest->setText("Trương Văn Toán");
    editWhoTest->setAlignment(Qt::AlignCenter);

    checkKeepTest->setChecked(m_systemConfig.keepTestIfFaled);
    checkRetestIfFailed->setChecked(m_systemConfig.reTestIfFailed);

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    editTest->setText("Log data");


    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QString s = info.portName();
        comSerialList->addItem(s);
    }

    comSerialList->setEditable(true);
    comSerialList->lineEdit()->setReadOnly(true);
    comSerialList->lineEdit()->setAlignment(Qt::AlignCenter);
    for(int i = 0; i < comSerialList->count(); i++) {
        comSerialList->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    comSerialList->setCurrentIndex(comSerialList->count() - 1);
}

void TestSystem::createTableViewHeader()
{
    tableView->setWordWrap(true);
    QStringList header;

    header << "Bài kiểm tra" << "Trạng thái" << "Giá trị (mét)" << "Số lần chạy" << "Chỉ tiêu (mét)" << "Thông tin";
    model->setHorizontalHeaderLabels(header);

    tableView->setModel(model);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setColumnWidth(0, 300);
    tableView->setColumnWidth(1, 250);
    tableView->setColumnWidth(2, 120);
    tableView->setColumnWidth(3, 120);
    tableView->setColumnWidth(4, 120);
    tableView->setColumnWidth(5, 750);
}

void TestSystem::createConnection()
{
    /**
     * @brief button connection
     */
    connect(btnLoadMap, SIGNAL(clicked(bool)), this, SLOT(on_btnLoadMapClicked()));
    connect(btnLoadTestParam, SIGNAL(clicked(bool)), this, SLOT(on_btnLoadTestParamClicked()));
    connect(btnStartTest, SIGNAL(clicked(bool)), this, SLOT(on_btnStartTestClicked()));    
    connect(btnConnectServer, SIGNAL(clicked(bool)), this, SLOT(on_btnConnectServerClicked()));
    connect(btnConnectRfDelay, SIGNAL(clicked(bool)), this, SLOT(on_btnConnectRfDelayClicked()));
    connect(comSerialList, SIGNAL(activated(const QString &)), this, SLOT(on_selectComClicked()));
    /**
     * @brief test
     */
    connect(btnTest, SIGNAL(clicked(bool)), this, SLOT(on_btnTestClicked()));    

    /**
     * @brief user edit parameter update
     */
    connect(editServerIp, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(editServerPort, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(editServerUdpPort, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));    
    connect(checkKeepTest, SIGNAL(clicked(bool)), this, SLOT(on_updateUserSetting()));
    connect(checkRetestIfFailed, SIGNAL(clicked(bool)), this, SLOT(on_updateUserSetting()));

    connect(this, SIGNAL(updateResultLocation(double,double,bool)), this, SLOT(on_UpdateLocationResult(double,double,bool)));
}



/**
 * @brief TestSystem::StartTestSuite
 */


/**
 * @brief TestSystem::GetTestState
 * @return
 */


void TestSystem::InitTestResult()
{
    if(GetTestProgress() == Progress_First_Time) {
        LoadGenConfig();
        clearAllResultAndFailed();
    } else {
        LREP("Retest failed point\n");
        emit sigLoadRetestParamToUi();
        clearAllResult();
    }

    control->SigGen_InitDevice();
    control->Server_SetServerOperationMode(Server_Normal);
    control->Server_SetNoiseFloor(0, 10);
    control->Server_ClearSignalDataBase();
}

/**
 * @brief TestSystem::DoTestTdoa
 *
 *
 *
 * 0. Lựa chọn vị trí sensor và nguồn phát trên bản đồ
 * 1. Điều khiển RF Delay chọn tần số phát và chế độ phát
   2. Điều khiển Server vào mission ứng với tần số phát
   3. Gửi tọa độ của 3 sensor cho server
   4. Đợi signal list đúng với tần số phát
   5. Gửi bản tin TDOA cho server
   6. Kiểm tra kết quả TDOA (Pass/Failed + tọa độ)
   7. Hiển thị thông tin lên bản đồ
 *
 *
 */


void TestSystem::DoTestTdoa(ComParam &param)
{

    if(param.input.freqTestList.size() == 0)
        return;

    control->Server_SetGain(0, param.input.gain);
    control->Server_SetNoiseFloor(0, param.input.noisefloor);
    emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");




    if(GetTestState() == TestState_Pause) {
        emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
        PauseTest();
        control->SigGen_InitDevice();
    }

    std::vector<double>::iterator iter  = param.input.freqTestList.begin();
    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {
        double freq = *iter;
        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
        }

        emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");
        emit updateStatusBar("Đang kiểm tra TDOA tại: " +
                             QString::number(freq, 'g', 10) + " Mhz ...");
        control->currFreqExp = freq * 1E6;

        //1
        control->Dev_RFDLSendCommand(RFDL_SET_FREQ, NULL, 0);
        //2
        control->Server_SetRecvFreq(freq, BW_40_MHZ, 0);

        //3 Gui toa do 3 hoac 4 sensor cho server
        control->Server_SendSensorInfo(Sensor0.m_lat, Sensor0.m_long, Sensor1.m_lat,
                                       Sensor1.m_long, Sensor2.m_lat, Sensor2.m_long,
                                       Sensor3.m_lat, Sensor3.m_long, int(m_mapView->GetNumSensor()));


        LREP("WAIT SERVER SEND TDOA STATUS\n");
        external::client::Signal signal;
        signal.set_power(0);
        uint32_t count = genConfig.serverDelay / 100;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            signal = control->Server_GetSignalHasPower(uint64_t(freq * 1E6), param.input.ferr);
        }while(IsKeepgoingOnTest() && (count--) && (signal.power() == 0));

        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;


        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }

        if(SYSTEM_RESET_VAL) {
            signal.set_power(-110);
        }

        LREP("CHECK SIGNAL LIST TDOA\n");
        //4 Kiem tra signal list
        if(signal.power() < 0) {
            //5 Gui ban tin yeu cau TDOA
            control->Server_SendTdoaMessage(signal,
                                            external::client::geolocation::Request::Mode::Request_Mode_HIGH_PERFORMANCE);

            //6 Kiem tra ket qua TDOA
            uint32_t count = genConfig.serverDelay / 100;
            signal.set_power(0);
            do {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                signal = control->Server_GetSignalTdoa(uint64_t(freq * 1E6), param.input.ferr);
            }while(IsKeepgoingOnTest() && (count--) && (signal.power() == 0));

            if(SYSTEM_RESET_VAL) {
                signal.set_power(-110);
            }

            if(signal.power() < 0) {

                const ::external::client::Signal_Geolocation& geo = signal.geolocation();
                const ::external::client::Location getLoc = geo.location();

                if(SYSTEM_RESET_VAL) {
                    int lat_val = GetRand(-10, 10);
                    int long_val = GetRand(-10, 10);
                    double err_lat = double(lat_val) / 10000.0;
                    double err_lon = double(long_val) / 10000.0;
                    param.result.currValue = 1000 * MapView::distanceEarth(txLocation.m_lat - err_lat, txLocation.m_long - err_lon,
                                                                txLocation.m_lat, txLocation.m_long);
                    emit updateResultLocation(txLocation.m_lat - err_lat, txLocation.m_long - err_lon, true);
                } else {
                    param.result.currValue = 1000 * MapView::distanceEarth(getLoc.latitude(), getLoc.longitude(),
                                                                txLocation.m_lat, txLocation.m_long);
                    emit updateResultLocation(getLoc.latitude(), getLoc.longitude(), true);
                }



                testPoint.value = param.result.currValue;

                if(param.result.currValue <= param.input.max ) {
                    testPoint.passed = true;

                    displayAndWriteResultRow(testPoint, true);
                }else {
                    testPoint.passed = false;
                    displayAndWriteResultRow(testPoint, false);
                }

                // Show value is readed
                displayValueOfFreq(param.result.currValue);

            } else {

                displayAndWriteResultRow(testPoint, QString("N/A"));
                displayValueOfFreq("N/A");

                emit updateStatusBar("Không nhận được kết quả TDOA tại: " +
                                     QString::number(freq, 'g', 10) + " Mhz !!!", QColor(Qt::red));
            }
        } else {
            displayAndWriteResultRow(testPoint, QString("N/A"));
            displayValueOfFreq("N/A");

            emit updateStatusBar("Không nhận được signal list tại: " +
                                 QString::number(freq, 'g', 10) + " Mhz !!!", QColor(Qt::red));
        }

        if(!testPoint.passed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
        }



        param.result.listResult.push_back(testPoint);
        if((!m_systemConfig.keepTestIfFaled) && (!testPoint.passed)) {
            break;
        }

        iter++;
    }

}

void TestSystem::LoadSystemConfig()
{
    m_systemConfig = UiConfig::getInstance()->getSystemConfig();
}

void TestSystem::SaveSystemConfig()
{
    UiConfig::getInstance()->saveSystemKeepTestIfFailed(m_systemConfig.keepTestIfFaled);
    UiConfig::getInstance()->saveSystemReTestIfFailed(m_systemConfig.reTestIfFailed);
    UiConfig::getInstance()->saveSystemServerAddress(m_systemConfig.ServerIp);
    UiConfig::getInstance()->saveSystemServerSslPort(m_systemConfig.sslPort);
    UiConfig::getInstance()->saveSystemServerUdpPort(m_systemConfig.udpPort);
}


/**
 * @brief TestSystem::DoTestSuiteFunction
 */
void TestSystem::DoTestSuiteFunction()
{
    while(!doTestSuiteTerm) {
        if(IsKeepgoingOnTest()) {
            InitTestResult();
            LREP("/--------------------------------------/\n");
            emit clearColumData(STATUS_IN_COLUM, totalResIdx + 1, 0); // Clear include TOTAL result
            emit clearColumData(VALUE_IN_COLUM, totalResIdx + 1, 0); // Clear include TOTAL result            
            currLineIdx = 1;
            currLineResult = 20;
            for(auto &test : testHead) {
                if(!IsKeepgoingOnTest())
                    break;

                test.second.input.freqTestList.clear();
                test.second.input.reTestingList.clear();
                if(GetTestProgress() == Progress_First_Time) {
                    for(auto var : test.second.input.freqList) {
                        test.second.input.freqTestList.push_back(var);
                    }
                } else {
                    for(auto var : test.second.input.failFreqList) {
                        test.second.input.freqTestList.push_back(var.freq);
                        test.second.input.reTestingList.push_back(var);
                    }
                    test.second.input.failFreqList.clear();
                }

                if(test.second.input.freqTestList.size() == 0)
                    continue;

                if(test.second.name == SYSTEM_STR_TEST_TDOA) {
                    DoTestTdoa(test.second);
                    test.second.result.curPassed =
                            CheckTestCaseResult(test.second.result.listResult);
                    currLineIdx++;
                }
            }
            if(GetTestState() == TestState_Running) {
                if(checkTotalPassed()) {
                    SetPassed();
                } else {
                    if(m_systemConfig.reTestIfFailed) {
                        userAct = User_Wait_Select;
                        emit showQuesDialog();
                        while(userAct == User_Wait_Select) {
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                        }

                        if(userAct == User_Select_Yes) {
                            SaveResultForContinueTest(editSerial->text(), editWhoTest->text());
                            SetTestProgress(Progress_Retest_Failed_Point);
                            continue;
                        }
                    }
                    SetFailed();
                }
                emit updateStatusBar("ĐÃ KẾT THÚC BÀI ĐO");
            } else {
                LREP("TEST TERMINATED BY EXTERNAL\n");
                emit updateStatusBar("ĐÃ DỪNG CHƯƠNG TRÌNH ");
                SetFailed();
            }
            EnableSettingPanel(true);
            labelTestPassNum->setText(QString::number(testTracker.testPass));
            labelTestRunNum->setText(QString::number(testTracker.testRun));
            btnStartTest->setText("BẮT ĐẦU");
            btnStartTest->setEnabled(true);
            if(GetTestProgress() == Progress_Retest_Failed_Point) {
                isTestParmLoaded = false;
            }

        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}


void TestSystem::StopAllTest(bool save)
{
    StopTestSuite(save);
    labelTestPassNum->setText(QString::number(testTracker.testPass));
    labelTestRunNum->setText(QString::number(testTracker.testRun));
    control->SigGen_DeSetCombo();
    EnableSettingPanel(true);
}

void TestSystem::StartAllTest(const QString &serial, const QString &who, bool createResult)
{
    ASSERT(control->SigGen_InitDevice());
    StartTestSuite(TEMPLATE_SENSOR_THUONG, serial, who);


    if(createResult) {
        std::map<int, ComParam>::iterator iter = testHead.begin();
        currLineResult = 20;
        while(iter != testHead.end()) {
            std::pair<int, ComParam> test = *iter;
            if(test.second.name == SYSTEM_STR_TEST_TDOA) {
                resFile->write("B" + QString::number(currLineResult), "TDOA TỰ ĐỘNG");
                resFile->write("E" + QString::number(currLineResult), "≤ " + QString::number(test.second.input.max) + " Mét");

            }
            CreateResultLine(test.second);
            iter++; // Go to next test point
        }
    }


    SetTestState(TestState_Running);    
    EnableSettingPanel(false);
    btnStartTest->setText("DỪNG");
}



void TestSystem::on_updateUserSetting()
{
    GetUserConfig();
    SaveSystemConfig();
    isSaveCfg = true;
}


void TestSystem::on_btnTestClicked()
{
    editTest->clear();
}



void TestSystem::on_btnStartTestClicked()
{
    if(GetTestState() == TestState_Stop){
        if(!isTestParmLoaded) {
            QMessageBox::warning(this, "Lỗi", "Nạp bài đo và bắt đầu !");
            return;
        }
        if(editSerial->text() == "") {
            QMessageBox::warning(this, "Lỗi", "Chưa nhập serial !");
            return;
        }
        if(editWhoTest->text() == "") {
            QMessageBox::warning(this, "Lỗi", "Chưa nhập tên người đo !");
            return;
        }

//        if(!control->Dev_GetStatus()) {
//            QMessageBox::warning(this, "Lỗi", "Chưa kết nối RFDELAY !");
//            return;
//        }

//        if(control->Server_GetStatus() != communication::Event_Connected) {
//            QMessageBox::warning(this, "Lỗi", "Chưa kết nối server !");
//            return;
//        }

        if(editSerial->text().length() > 20) {
            QMessageBox::warning(this, "Lỗi", "Serial không hợp lệ (độ dài " + QString::number(editSerial->text().length()) + ")");
            return;
        }


        if(m_mapView) {
            txLocation = m_mapView->getPoint(4);
            Sensor0 = m_mapView->getPoint(0);
            Sensor1 = m_mapView->getPoint(1);
            Sensor2 = m_mapView->getPoint(2);


            if(m_mapView->GetNumSensor() == System_Four_Sensor) {
                Sensor3 = m_mapView->getPoint(3);
                if(Sensor0.m_distance <= 0 || Sensor1.m_distance <= 0 ||
                        Sensor2.m_distance <= 0 || Sensor3.m_distance <= 0) {
                    QMessageBox::warning(this, "Lỗi", "Thiết lập các sensor và nguồn phát không hợp lệ !");
                    return;
                }

            } else {
                if(Sensor0.m_distance <= 0 || Sensor1.m_distance <= 0 ||
                        Sensor2.m_distance <= 0) {
                    QMessageBox::warning(this, "Lỗi", "Thiết lập các sensor và nguồn phát không hợp lệ !");
                    return;
                }
            }
        } else {
            QMessageBox::warning(this, "Lỗi", "Chưa nhập dữ liệu từ bản đồ\nMở bản đồ, chọn vị trí sensor và nguồn phát");
            return;
        }


        StartAllTest(editSerial->text(), editWhoTest->text(), true);

    } else if(GetTestState() == TestState_Running) {
        totalTestRes = "_FAIL";
        SetTestState(TestState_RequestStop);
        btnStartTest->setText("ĐANG DỪNG");
        btnStartTest->setEnabled(false);
    } else {
        LREP("Request stop\n");
    }
}

void TestSystem::on_btnConnectServerClicked()
{
    if(control->Server_GetStatus() == communication::Event_Connected ||
            control->Server_GetStatus() == communication::Event_Connecting) {

        LREP("USER Stop ssl client\n");
        control->Server_StopSslClient();
        //control->Server_StopUdpClient();
    } else {
        ConfigController();
        LREP("USER Start ssl client\n");
        control->Server_StartSslClient();
        //control->Server_StartUdpClient();
    }

}

void TestSystem::on_btnConnectRfDelayClicked()
{
    ConfigController();

    if(control->Dev_GetStatus()) {
        control->Dev_Stop();
        btnConnectRfDelay->setText("KẾT NỐI");
        comSerialList->setEnabled(true);
        LREP("Disconnected\n");
    } else {
        LREP("Try to connect\n");
        control->Dev_Start();
    }
}


void TestSystem::on_mapClose()
{
    if(m_mapView != Q_NULLPTR) {
        disconnect(m_mapView, SIGNAL(close()), this, SLOT(on_mapClose()));
        delete m_mapView;
        m_mapView = Q_NULLPTR;
    }
}

void TestSystem::on_selectComClicked()
{
    QList<QSerialPortInfo> lst = QSerialPortInfo::availablePorts();
    if(lst.count() != comSerialList->count())
        comSerialList->clear();

    foreach (const QSerialPortInfo &info, lst) {
        QString s = info.portName();
        if(FindText(s) == false)
            comSerialList->addItem(s);
    }

}

void TestSystem::on_SslClientConnectEvent(int evt)
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
        control->Server_StopUdpClient();
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




void TestSystem::on_SiggenConnectEvent(int evt)
{
    (void)evt;

}

void TestSystem::on_DataReceived(quint64 data)
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

void TestSystem::on_RfDelayConnEvent(int evt)
{
    switch(evt) {
        case communication::Event_Connected:
        LREP("Event Connected to RFDelay\r\n");
        btnConnectRfDelay->setText("NGẮT KẾT NỐI");
        break;
    case communication::Event_Disconnected:
        btnConnectRfDelay->setText("KẾT NỐI");
        SetTestState(TestState_Stop);
        EnableSettingPanel(true);
        QMessageBox::warning(this, "Lỗi", "Không mở được cổng \"" +
                             comSerialList->currentText() + "\" cổng đang bận hoặc không có quyền!");
        break;

    default:
        break;

    }
}

void TestSystem::on_ServerRecvTdoaStatus(external::client::geolocation::Status status)
{
    for(int i = 0; i < status.sensor_size(); i++) {
        if(status.sensor(i).id() == 0) {
            labelS0->setText(QString::number(status.signal().frequency()));
            progS0->setValue(100.0 * double(status.sensor(i).received_sample()) /
                             double(status.sensor(i).total_sample()));

        } else if(status.sensor(i).id() == 1){
            labelS0->setText(QString::number(status.signal().frequency()));
            progS1->setValue(100.0 * double(status.sensor(i).received_sample()) /
                             double(status.sensor(i).total_sample()));

        } else if(status.sensor(i).id() == 2){
            labelS0->setText(QString::number(status.signal().frequency()));
            progS2->setValue(100.0 * double(status.sensor(i).received_sample()) /
                             double(status.sensor(i).total_sample()));

        } else if(status.sensor(i).id() == 3){
            labelS0->setText(QString::number(status.signal().frequency()));
            progS3->setValue(100.0 * double(status.sensor(i).received_sample()) /
                             double(status.sensor(i).total_sample()));
        }
    }
}

void TestSystem::on_UpdateLocationResult(double lat, double lon, bool show)
{
    m_mapView->setResultLocation(lat, lon, show);
}



bool TestSystem::loadTestParam(const CSVFile::CsvVector &data)
{
    int order;
    if(!data.size())
      return false;

    m_rows.clear();

    //LREP("Clear all test param before load the new !");
    clearAllParam();

    CSVFile::CsvVector::const_iterator iter;
    for(iter = data.begin(); iter != data.end(); ++iter){
    std::vector<std::string> row = *iter;
        if(row.at(1) == SYSTEM_STR_TEST_TDOA && (row.size() >= 15)) {
            ComParam head;
            head.name = row.at(1);
            QString cont;
            head.enable = (row.at(2) == "TRUE" || row.at(2) == "true") ? true : false;
            if(head.enable) {
                order = cppframework::str::Util::convert<int>(row.at(3), 1);
                head.input.min = str::Util::convert<double>(row.at(5), 0);
                head.input.max = str::Util::convert<double>(row.at(6), 0);
                head.input.ferr = str::Util::convert<uint64_t>(row.at(11), 0);
                head.input.gain = str::Util::convert<double>(row.at(12), 0);
                head.input.noisefloor = str::Util::convert<double>(row.at(13), 0);
                head.input.changeMiss = (row.at(14) == "TRUE" || row.at(14) == "true") ? true : false;

                if((row.at(7) == "TRUE" || row.at(7) == "true")) {
                    double step = str::Util::convert<double>(row.at(10), 1);
                    double start = str::Util::convert<double>(row.at(8), 20);
                    double stop = str::Util::convert<double>(row.at(9), 100);

                    for(double idx = start; idx <= stop; idx += step) {
                        head.input.freqList.push_back(idx);
                    }
                    cont = "FREQ START: <" + QString::number(start, 'g', 10) +
                            " Mhz> - STEP: <" + QString::number(step, 'g', 10) +
                            " Mhz> - STOP: <" + QString::number(stop, 'g', 10) + " Mhz> ERR: " +
                            QString::number(head.input.ferr) + " Hz NF: " +
                            QString::number(head.input.noisefloor) + " GAIN: " +
                            QString::number(head.input.gain, 'g', 10);
                } else {
                    convertVectStrToDouble(row.at(4), head.input.freqList);
                    cont = "Freq list: [" + QString(row.at(4).c_str()) + "]  MHz ERR:" +
                            QString::number(head.input.ferr, 'g', 10) + " Hz";
                }

                m_rows << (QStringList() << QString(head.name.c_str()).toUpper() << " " << " " << " " << " " << cont);

                for(auto var : head.input.freqList) {
                    m_rows << (QStringList() << "Freq: " + QString::number(var, 'g', 10) + " Mhz" << " " << " " <<
                             QString::number(head.input.min) <<
                             QString::number(head.input.max));
                }


                addTestCase(order, head);
            }
        }
    }

    return true;

}


/**
 * @brief TestSystem::on_btnSettingClicked
 */
void TestSystem::on_btnLoadMapClicked()
{
    if(m_mapView == Q_NULLPTR) {
        m_mapView = new MapView;
        m_mapView->showNormal();
        LREP("Create new mapview\n");
    } else {
        m_mapView->show();
        if(!m_mapView->isActiveWindow()) {
            m_mapView->activateWindow();
        }
    }
}

/*
 *
 *
 *
*/
void TestSystem::on_btnLoadTestParamClicked()
{
    LoadTestConfigFromFile();
    isTestParmLoaded = true;
}

/*
 *
 *
 *
*/
void TestSystem::LoadTestConfigFromFile()
{
    modeLoaded = "";
    std::string          externalFile = genConfig.inputDir;

    externalFile += ("/system/tdoa.csv");

    if(loadTestConfig(externalFile)) {
        loadTestParam(loader->rows());
        loadTestParamToUi();
    } else {

    }
    loader.reset();
}



void TestSystem::ConfigController()
{
    /**
     * @brief connection event
     */
    control->disconnectAllConnection();
    control->addConnection(connect(control, SIGNAL(sigServerStatus(int)), this, SLOT(on_SslClientConnectEvent(int))));
    control->addConnection(connect(control, SIGNAL(sigSigGenStatus(int)), this, SLOT(on_SiggenConnectEvent(int))));

    control->addConnection(connect(control, SIGNAL(sigServerTdoa(external::client::geolocation::Status)),
                                   this, SLOT(on_ServerRecvTdoaStatus(external::client::geolocation::Status))));

    control->addConnection(connect(control, SIGNAL(sigSerialDevStatus(int)), this, SLOT(on_RfDelayConnEvent(int))));

    if(control) {
        control->ConfigSslClient(m_systemConfig.ServerIp, m_systemConfig.sslPort);
        control->ConfigIsc(comSerialList->currentText().toStdString(), 115200);
    }
}

void TestSystem::EnableSettingPanel(bool en)
{
    btnConnectRfDelay->setEnabled(en);
    btnConnectServer->setEnabled(en);
    btnLoadTestParam->setEnabled(en);
    btnLoadMap->setEnabled(en);
    editSerial->setEnabled(en);
    if(m_mapView)
        m_mapView->EnablePanelButton(en);
}

void TestSystem::GetUserConfig()
{
    m_systemConfig.keepTestIfFaled = checkKeepTest->isChecked();
    m_systemConfig.reTestIfFailed = checkRetestIfFailed->isChecked();
    m_systemConfig.ServerIp = editServerIp->text().toStdString();
    m_systemConfig.sslPort = editServerPort->text().toUShort();
    m_systemConfig.udpPort = editServerUdpPort->text().toUShort();
}



bool TestSystem::FindText(QString &s)
{
    for(int i = 0; i < comSerialList->count(); i++) {
        if(comSerialList->itemText(i) == s) {
            return true;
        }
    }
    return false;
}

int TestSystem::GetRand(int min, int max)
{
   static bool first = true;
   if (first)
   {
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

