#include "testfpga.h"
#include <iostream>
#include <protocol/client_msg/msg.pb.h>
#include <isc/utils.h>

using namespace cppframework;
/**
 * @brief TestFpga::TestFpga create all ui element,
 *                  load configuration and create connection
 * @param parent
 */

TestFpga::TestFpga(Controller *controller, TestBase *parent) :
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
 * @brief TestFpga::~TestFpga
 */
TestFpga::~TestFpga()
{

}

void TestFpga::initVariable()
{
    /**
     * Delay must large enough prevent TCP appends two frames into one package
     */

    waitFpgaInMs = 1000;    
    testTrackerFile = CONFIG_TEST_TRACK_FPGA;
    outputFileName = FILENAME_RES_FPGA;
    LoadFpgaConfig();
    LoadTestTracker();
    LoadGenConfig();
    InitAllTestName();
    isSaveCfg = false;


}

void TestFpga::createUiElem()
{    
    groupConfig = new QGroupBox(tr("CÀI ĐẶT"));

    labelInstrIp = new QLabel("ĐỊA CHỈ SIGNAL GEN");
    editInstrIp = new QLineEdit;
    btnConnectInstr = new QPushButton("KẾT NỐI");

    tableView = new QTableView(this);
    mainLayout = new QVBoxLayout;
    settingLayout = new QFormLayout;
    hLayout = new QHBoxLayout;

    labelHeader = new QLabel("ĐO KIỂM TỰ ĐỘNG TÍNH NĂNG MẠCH SỐ");
    btnTest = new QPushButton("Test");
    btnStartTest = new QPushButton("BẮT ĐẦU");
    checkKeepTest = new QCheckBox;
    editSerial = new QLineEdit;

    checkRetestIfFailed = new QCheckBox;
    checkPauseTest = new QCheckBox;
    editWhoTest = new QLineEdit;

    manLayout = new QFormLayout;
    mainSettingLayout = new QVBoxLayout;

    groupSetting = new QGroupBox("CÀI ĐẶT");
    groupMan = new QGroupBox("THAO TÁC");

    editInstrPort = new QLineEdit;
    labelInstrStatus = new QLabel("KHÔNG KẾT NỐI");

    labelTestRunNum = new QLabel(" ");
    labelTestPassNum = new QLabel(" ");
}

void TestFpga::createLayout()
{

    settingLayout->addItem(new QSpacerItem(0, 10));
    settingLayout->addRow(labelInstrIp, editInstrIp);
    settingLayout->addRow("CỔNG TCP", editInstrPort);
    settingLayout->addRow("TRẠNG THÁI", labelInstrStatus);
    labelInstrStatus->setStyleSheet("QLabel {color : red; }");
    settingLayout->addRow("SIGNAL GENERATOR", btnConnectInstr);
    settingLayout->addItem(new QSpacerItem(0, 10));
    settingLayout->addRow("TIẾP TỤC NẾU FAILED", checkKeepTest);
    settingLayout->addRow("TEST LẠI NẾU FAILED", checkRetestIfFailed);
    settingLayout->addRow("TẠM DỪNG KẾT NỐI", checkPauseTest);

    manLayout->addRow("SỐ LƯỢNG TEST", labelTestRunNum);
    manLayout->addRow("SỐ LƯỢNG PASS", labelTestPassNum);
    manLayout->addRow("NGƯỜI TEST", editWhoTest);
    manLayout->addRow("SERIAL", editSerial);
    manLayout->addWidget(btnStartTest);
    manLayout->addWidget(btnTest);

    settingLayout->setHorizontalSpacing(1);
    btnStartTest->setFixedHeight(40);
    editWhoTest->setFixedHeight(30);

    settingLayout->setAlignment(checkKeepTest, Qt::AlignCenter);
    settingLayout->setAlignment(checkRetestIfFailed, Qt::AlignCenter);
    settingLayout->setAlignment(checkPauseTest, Qt::AlignCenter);


    labelHeader->setAlignment(Qt::AlignCenter);
    labelHeader->setStyleSheet(QLatin1String("font: 18pt \"Times New Roman\";"));
    QPalette palette;
    palette.setColor(QPalette::WindowText, QColor(Qt::white));
    labelHeader->setPalette(palette);

    groupSetting->setLayout(settingLayout);
    groupMan->setLayout(manLayout);

    mainSettingLayout->addWidget(groupSetting, 0, Qt::AlignTop);
    mainSettingLayout->addWidget(groupMan, 1, Qt::AlignTop);

    groupSetting->setFixedWidth(300);
    groupMan->setFixedWidth(300);
    hLayout->addWidget(tableView);
    hLayout->addLayout(mainSettingLayout, Qt::AlignRight);
    mainLayout->addWidget(labelHeader);
    mainLayout->addLayout(hLayout);
    setLayout(mainLayout);
}

void TestFpga::createElemContent()
{
    createTableViewHeader();


    editInstrIp->setAlignment(Qt::AlignCenter);
    editInstrPort->setAlignment(Qt::AlignCenter);
    editInstrPort->setFixedWidth(50);
    labelInstrStatus->setAlignment(Qt::AlignCenter);


    editInstrIp->setText(QString(m_fpgaConfig.fpgaIp.c_str()));
    editInstrPort->setText(QString::number(m_fpgaConfig.fpgaPort));

    labelTestRunNum->setText(QString::number(testTracker.testRun));
    labelTestPassNum->setText(QString::number(testTracker.testPass));
    labelTestRunNum->setAlignment(Qt::AlignCenter);
    labelTestPassNum->setAlignment(Qt::AlignCenter);

    editSerial->setText("VI0989681001");
    editSerial->setAlignment(Qt::AlignCenter);
    editSerial->setFixedHeight(30);    
    editSerial->setStyleSheet(QLatin1String("font: 12pt;"));

    editWhoTest->setText("Trương Văn Toán");
    editWhoTest->setAlignment(Qt::AlignCenter);

    checkKeepTest->setChecked(m_fpgaConfig.keepTestIfFaled);
    checkRetestIfFailed->setChecked(m_fpgaConfig.reTestIfFailed);
    checkPauseTest->setChecked(m_fpgaConfig.pauseTest);

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


}

void TestFpga::createTableViewHeader()
{
    tableView->setWordWrap(true);
    QStringList header;

    header << "Bài kiểm tra" << "Trạng thái" << "Thông tin";
    model->setHorizontalHeaderLabels(header);

    tableView->setModel(model);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setColumnWidth(0, 350);
    tableView->setColumnWidth(1, 300);
    tableView->setColumnWidth(2, 750);
}

void TestFpga::createConnection()
{
    /**
     * @brief button connection
     */
    connect(btnStartTest, SIGNAL(clicked(bool)), this, SLOT(on_btnStartTestClicked()));    
    connect(btnConnectInstr, SIGNAL(clicked(bool)), this, SLOT(on_btnConnectFpgaClicked()));

    /**
     * @brief test
     */
    connect(btnTest, SIGNAL(clicked(bool)), this, SLOT(on_btnTestClicked()));    

    /**
     * @brief user edit parameter update
     */
    connect(editInstrIp, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(editInstrPort, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(checkKeepTest, SIGNAL(clicked(bool)), this, SLOT(on_updateUserSetting()));
    connect(checkRetestIfFailed, SIGNAL(clicked(bool)), this, SLOT(on_updateUserSetting()));
    connect(checkPauseTest, SIGNAL(clicked(bool)), this, SLOT(on_updateUserSetting()));


    connect(this, SIGNAL(setSerialNumbser(QString)), this, SLOT(on_setSerialNumber(QString)));
}


void TestFpga::InitTestResult()
{
    if(GetTestProgress() == Progress_First_Time) {
        LoadGenConfig();
        clearAllResultAndFailed();
    } else {
        LREP("Retest failed point\n");
        //loadRetestParamToUi();
        clearAllResult();
    }
    LoadFpgaConfig();
    control->Fpga_SendCommand(Command_Read_Fpga_Serial, NULL, 0);
}


void TestFpga::ControlFpga(TestBase::ComParam &param)
{
    Sensor_Command cmd = Command_Test_Max;
    if (param.name == FPGA_TEST_EHTERNET_10G_23) {
        cmd = Command_Test_Ethernet_23_10G;
        LREP("TEST ETHERNET 10G\n");
        currLineResult = 20;
    } else if (param.name == FPGA_TEST_PS_RAM) {
        cmd = Command_Test_Ps_Ram;
        currLineResult = 21;
        LREP("TEST PS RAM\n");
    } else if (param.name == FPGA_TEST_PL_RAM) {
        cmd = Command_Test_Pl_Ram;
        currLineResult = 22;
        LREP("TEST PL RAM\n");
    } else if (param.name == FPGA_TEST_ADC) {
        cmd = Command_Test_ADC;
        currLineResult = 23;
        LREP("TEST ADC \n");
    } else if (param.name == FPGA_TEST_SSD_1) {
        cmd = Command_Test_SSD_1;
        currLineResult = 24;
        LREP("TEST SSD 1\n");
    } else if (param.name == FPGA_TEST_SSD_2) {
        if(m_fpgaConfig.pauseTest) {
            m_confirmInfo = false;
            emit showInfoDialog("Tắt nguồn zig test->gắn cáp SATA sang cổng số 2\n"
                                "->bật nguồn zig -> tắt hộp thoại này -> bấm 'kết nối' -> bấm 'tiếp tục'");
            uint32_t count = 1000;
            while(!m_confirmInfo &&  count > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                count--;
            }
            SetTestState(TestState_Pause);
            btnStartTest->setText("TIẾP TỤC");
            PauseTest();
        }
        cmd = Command_Test_SSD_2;
        currLineResult = 25;
        LREP("TEST SSD 2");
    } else if (param.name == FPGA_TEST_SSD_3) {

        if(m_fpgaConfig.pauseTest) {
            m_confirmInfo = false;
            emit showInfoDialog("Tắt nguồn zig test->gắn cáp SATA sang cổng số 3\n"
                                "->bật nguồn zig -> tắt hộp thoại này -> bấm 'kết nối' -> bấm 'tiếp tục'");
            uint32_t count = 1000;
            while(!m_confirmInfo &&  count > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                count--;
            }

            SetTestState(TestState_Pause);
            btnStartTest->setText("TIẾP TỤC");
            PauseTest();
        }
        cmd = Command_Test_SSD_3;
        currLineResult = 26;
        LREP("TEST SSD 3");
    } else if (param.name == FPGA_TEST_SSD_4) {
        if(m_fpgaConfig.pauseTest) {
            m_confirmInfo = false;
            emit showInfoDialog("Tắt nguồn zig test->gắn cáp SATA sang cổng số 4\n"
                                "->bật nguồn zig -> tắt hộp thoại này -> bấm 'kết nối' -> bấm 'tiếp tục'");
            uint32_t count = 1000;
            while(!m_confirmInfo &&  count > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                count--;
            }
            SetTestState(TestState_Pause);
            btnStartTest->setText("TIẾP TỤC");
            PauseTest();
        }
        cmd = Command_Test_SSD_4;
        currLineResult = 27;
        LREP("TEST SSD 4");
    } else if (param.name == FPGA_TEST_IFRF_1) {
        cmd = Command_Test_Ifrf_1;
        currLineResult = 28;
        LREP("TEST IFRF 1\n");
    } else if (param.name == FPGA_TEST_IFRF_2) {
        cmd = Command_Test_Ifrf_2;
        currLineResult = 29;
        LREP("TEST IFRF 2\n");
    } else if (param.name == FPGA_TEST_GPSDO) {
        cmd = Command_Test_GpsDo_Interface;
        currLineResult = 30;
        LREP("TEST GPSDO\n");
    } else if (param.name == FPGA_TEST_EXTEN) {
        cmd = Command_Test_Exten_Interface;
        currLineResult = 31;
        LREP("TEST EXEN INTERFACE\n");
    } else if (param.name == FPGA_TEST_FLASH) {
        cmd = Command_Test_Flash;
        currLineResult = 32;
        LREP("TEST FLASH\n");
    }

    if(cmd != Command_Test_Max) { // Nếu bài đo được chọn
        control->Fpga_SendCommand(cmd, NULL, 0); // Gửi lệnh điều khiển đo tương ứng
        uint32_t delay = 50;
        while(GetTestState() == TestState_Running && (delay > 0) && !getBoardResponseByName(param.name)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            delay--;
        }

        LREP("DELAY {}\n", delay);
        if(delay <= 0) {
            emit updateStatusBar(QString("Không nhận được kết quả bài kiểm tra %1").arg(currLineIdx + 1));
        } else  {
            emit updateStatusBar(QString("Nhận được kết quả bài kiểm tra %1").arg(currLineIdx + 1));
        }

    }
}

void TestFpga::InitAllTestName()
{
    m_listTestName.push_back(FPGA_TEST_EHTERNET_10G_23);
    m_listTestName.push_back(FPGA_TEST_PS_RAM);
    m_listTestName.push_back(FPGA_TEST_PL_RAM);
    m_listTestName.push_back(FPGA_TEST_ADC);
    m_listTestName.push_back(FPGA_TEST_SSD_1);
    m_listTestName.push_back(FPGA_TEST_SSD_2);
    m_listTestName.push_back(FPGA_TEST_SSD_3);
    m_listTestName.push_back(FPGA_TEST_SSD_4);
    m_listTestName.push_back(FPGA_TEST_IFRF_1);
    m_listTestName.push_back(FPGA_TEST_IFRF_2);
    m_listTestName.push_back(FPGA_TEST_GPSDO);
    m_listTestName.push_back(FPGA_TEST_EXTEN);
    m_listTestName.push_back(FPGA_TEST_FLASH);
}


/**
 * @brief TestFpga::DoTestSuiteFunction
 */
void TestFpga::DoTestSuiteFunction()
{

    bool ret = false;
    while(!doTestSuiteTerm) {

        if(IsKeepgoingOnTest()) {
            InitTestResult();
            LREP("/--------------------------------------/\n");
            emit clearColumData(STATUS_IN_COLUM, testHead.size() + 1, 0); // Clear include TOTAL result
            std::map<int, ComParam>::iterator iter = testHead.begin();
            currLineIdx = 0;
            totalResIdx = testHead.size();
            while(iter != testHead.end()) {
                if(!IsKeepgoingOnTest())
                    break;
                std::pair<int, ComParam> test = *iter;
                emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");
                //emit updateStatusBar(QString("Đang kiểm tra dòng %1").arg(currLineIdx + 1));
                test.second.result.curPassed = false;
                ControlFpga(test.second);
                ret = getPassFaildByName(test.second.name);
                //LREP("Check: {} - {}\n", test.second.name, ret);
                if(ret) {
                    displayPassedCase(currLineIdx);
                    WriteRowResult("ĐẠT", "PASSED");
                } else {
                    displayFailedCase(currLineIdx);
                    WriteRowResult("KHÔNG ĐẠT", "FAILED");
                }

                if((!m_fpgaConfig.keepTestIfFaled) && (!ret)) {
                    break;
                }

                iter++; // Go to next test point
                currLineIdx++;                
            }
            if(GetTestState() == TestState_Running) {
                if(checkTotalPassed()) {
                    SetPassed();
                } else {
//                    if(checkRetestIfFailed->isChecked()) {
//                        QMessageBox::StandardButton answer = QMessageBox::question(
//                            this,
//                            tr("TEST FAILED"),
//                            tr("Bạn muốn chạy lại ?"),
//                            QMessageBox::Yes | QMessageBox::No
//                        );

//                        if(answer == QMessageBox::Yes)
//                            continue;
//                    }
                    SetFailed();
                }
                emit updateStatusBar("ĐÃ KẾT THÚC BÀI ĐO");
            } else {
                emit updateStatusBar("ĐÃ DỪNG CHƯƠNG TRÌNH ");
                SetFailed();
            }
            EnableSettingPanel(true);
            labelTestPassNum->setText(QString::number(testTracker.testPass));
            labelTestRunNum->setText(QString::number(testTracker.testRun));
            btnStartTest->setText("BẮT ĐẦU");
            btnStartTest->setEnabled(true);
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void TestFpga::on_updateUserSetting()
{
    GetUserConfig();
    SaveFpgalConfig();
    isSaveCfg = true;
}


void TestFpga::on_btnTestClicked()
{

}

void TestFpga::on_btnStartTestClicked()
{
    if(GetTestState() == TestState_Stop) {
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

        if(control->Fpga_GetStatus() != communication::Event_Connected) {
            QMessageBox::warning(this, "Lỗi", "Chưa kết nối board fpga !");
            return;
        }

        if(editSerial->text().length() > 20) {
            QMessageBox::warning(this, "Lỗi", "Serial không hợp lệ (độ dài " + QString::number(editSerial->text().length()) + ")");
            return;
        }

        StartAllTest(editSerial->text(), editWhoTest->text());

    } else if(GetTestState() == TestState_Running) {
        totalTestRes = "_FAIL";
        SetTestState(TestState_RequestStop);
        btnStartTest->setText("ĐANG DỪNG");
        btnStartTest->setEnabled(false);
    } else if(GetTestState() == TestState_Pause) {
        SetTestState(TestState_Running);
        btnStartTest->setText("DỪNG");
    }

}


void TestFpga::on_btnConnectFpgaClicked()
{
    if(control->Fpga_GetStatus() == communication::Event_Connected ||
            control->Fpga_GetStatus() == communication::Event_Connecting) {
        control->Fpga_Stop();
    } else {
        ConfigController();
        control->Fpga_Start();
    }
}


void TestFpga::on_FpgaConnectEvent(int evt)
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
        LREP("Event Disconnected to server\r\n");
        btnConnectInstr->setText("KẾT NỐI");
        labelInstrStatus->setText("KHÔNG KẾT NỐI");
        //StopAllTest(false);
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
        control->Fpga_Stop();
        //StopAllTest(false);
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy board !");
        break;
    default:
        break;

    }
}

void TestFpga::on_FpgaDataEvent(uint8_t *data, int len)
{
    (void)len;
    Sensor_Command cmd = (Sensor_Command)data[5];
    Sensor_Result res = (Sensor_Result)data[7];

    bool pass = (res == Sensor_Passed) ? true : false;

    switch(cmd) {
    case Command_Write_Type :
        break;
    case Command_Read_Type:
        break;
    case Command_Write_Ip:
        break;
    case Command_Read_Ip:
        break;
    case Command_Write_Fpga_Serial:

        break;
    case Command_Read_Fpga_Serial:
    {
        data[7 + data[6]] = 0;
        std::string serial((const char*)&data[7]);
        this->editSerial->setText(QString(serial.c_str()));
    }
        break;
    case Command_Write_Ifrf_Serial:
        break;
    case Command_Read_Ifrf_Serial: {
            data[7 + data[6]] = 0;
            std::string serial((const char*)&data[7]);
            emit setSerialNumber(QString(serial.c_str()));
        }
        break;
    case Command_Test_Ethernet_23_10G:        
        ASSERT(setPassFaildByName(FPGA_TEST_EHTERNET_10G_23, pass));
        break;
    case Command_Test_Ps_Ram:
        ASSERT(setPassFaildByName(FPGA_TEST_PS_RAM, pass));
        break;
    case Command_Test_Pl_Ram:
        ASSERT(setPassFaildByName(FPGA_TEST_PL_RAM, pass));
        break;
    case Command_Test_ADC:
        ASSERT(setPassFaildByName(FPGA_TEST_ADC, pass));
        break;
    case Command_Test_SSD_1:
        ASSERT(setPassFaildByName(FPGA_TEST_SSD_1, pass));
        break;
    case Command_Test_SSD_2:
        ASSERT(setPassFaildByName(FPGA_TEST_SSD_2, pass));
        break;
    case Command_Test_SSD_3:
        ASSERT(setPassFaildByName(FPGA_TEST_SSD_3, pass));
        break;
    case Command_Test_SSD_4:
        ASSERT(setPassFaildByName(FPGA_TEST_SSD_4, pass));
        break;
    case Command_Test_Ifrf_1:
        ASSERT(setPassFaildByName(FPGA_TEST_IFRF_1, pass));
        break;
    case Command_Test_Ifrf_2:
        ASSERT(setPassFaildByName(FPGA_TEST_IFRF_2, pass));
        break;
    case Command_Test_GpsDo_Interface:
        ASSERT(setPassFaildByName(FPGA_TEST_GPSDO, pass));
        break;
    case Command_Test_Exten_Interface:
        ASSERT(setPassFaildByName(FPGA_TEST_EXTEN, pass));
        break;
    case Command_Test_Flash:
        ASSERT(setPassFaildByName(FPGA_TEST_FLASH, pass));
        break;
    default:
        break;
    }
}

void TestFpga::on_setSerialNumber(QString serial)
{
    editSerial->setText(serial);
}


bool TestFpga::loadTestParam(const CSVFile::CsvVector &data)
{
    if(!data.size())
      return false;
    ComParam head;
    //LREP("Clear all test param before load the new !");
    clearInputParam();

    CSVFile::CsvVector::const_iterator iter;
    for(iter = data.begin(); iter != data.end(); ++iter){
        std::vector<std::string> row = *iter;
            if(SearchTestName(row.at(1)) && (row.size() >= 4)) {
                head.name = row.at(1);
                head.enable = (row.at(2) == "TRUE" || row.at(2) == "true") ? true : false;

                if(head.enable) {
                    int order = cppframework::str::Util::convert<int>(row.at(3), 1);
                    addTestCase(order, head);
                }
        }
    }



    return true;
}

void TestFpga::clearInputParam()
{
    testHead.clear();
}

/*
 *
 *
 *
*/
void TestFpga::on_btnLoadTestParamClicked()
{
    LoadTestConfigFromFile();
    isTestParmLoaded = true;
}

/*
 *
 *
 *
*/
void TestFpga::LoadTestConfigFromFile()
{
    modeLoaded = "";
    std::string          externalFile;

    externalFile = genConfig.inputDir +  "/board/fpga_thuong.csv";
    if(loadTestConfig(externalFile)) {
        loadTestParam(loader->rows());
        loadTestParamToUi();
    } else {
        LREP("Load failed\n");
    }
    loader.reset();
}


void TestFpga::loadTestParamToUi()
{
    model->clear();
    createTableViewHeader();
    QList<QStringList> rows = QList<QStringList>();
    std::map<int, ComParam>::iterator iter = testHead.begin();
    std::pair<int, ComParam> content;
    while(iter != testHead.end()) {
        content = *iter;
        rows << (QStringList() << QString(content.second.name.c_str()) << " " << " ");
        iter++;
    }

    foreach (QStringList row, rows) {
        QList<QStandardItem *> items;
        QStringList::iterator iter = row.begin();
        QString text = *iter;
        QStandardItem *item = new QStandardItem(text);
        items.append(item);
        iter++;
        while(iter != row.end()) {
            QString text = *iter;
            QStandardItem *item = new QStandardItem(text);
            item->setTextAlignment(Qt::AlignCenter);
            items.append(item);
            iter++;
        }
        model->appendRow(items);
    }

    QStringList res;
    res << "TOÀN BỘ" << " ";
    AppendRowTable(res);
}

void TestFpga::AppendRowTable(QStringList &row)
{
    int index = 0;
    QList<QStandardItem *> items;
    QStringList::iterator iter = row.begin();
    //LREP("Row size: {}", row.size());
    while(iter != row.end()) {
        QString text = *iter;
        QStandardItem *item = new QStandardItem(text);
        if(index >= 1) {
            item->setTextAlignment(Qt::AlignCenter);
        }

        items.append(item);
        index++;
        iter++;
    }

    model->appendRow(items);
}

void TestFpga::ConfigController()
{
    /**
     * @brief connection event
     */
    control->disconnectAllConnection();
    control->addConnection(connect(control, SIGNAL(sigFpgaStatus(int)), SLOT(on_FpgaConnectEvent(int))));
    control->addConnection(connect(control, SIGNAL(sigFpgaRecvData(uint8_t*,int)), SLOT(on_FpgaDataEvent(uint8_t*,int))));
    if(control) {
        LREP("IP: {} PORT {}\n", m_fpgaConfig.fpgaIp, m_fpgaConfig.fpgaPort);
        control->ConfigFpga(m_fpgaConfig.fpgaIp, m_fpgaConfig.fpgaPort);
    }
}

void TestFpga::EnableSettingPanel(bool en)
{
    //btnConnectInstr->setEnabled(en);
    editSerial->setEnabled(en);
}


void TestFpga::PrintGeneralConfig()
{
    LREP("keep test: {}\n", m_fpgaConfig.keepTestIfFaled);
    LREP("auto open result: {}\n", m_fpgaConfig.reTestIfFailed);
    LREP("fpga ip: {}\n", m_fpgaConfig.fpgaIp);
    LREP("fpga port: {}\n", m_fpgaConfig.fpgaPort);
}

void TestFpga::LoadFpgaConfig()
{
    m_fpgaConfig = UiConfig::getInstance()->getFpgaConfig();
}

void TestFpga::SaveFpgalConfig()
{
    UiConfig::getInstance()->saveFpgaKeepTestIfFailed(m_fpgaConfig.keepTestIfFaled);
    UiConfig::getInstance()->saveFpgaReTestIfFailed(m_fpgaConfig.reTestIfFailed);
    UiConfig::getInstance()->saveFpgaPauseTest(m_fpgaConfig.pauseTest);
    UiConfig::getInstance()->saveFpgaFpgaIp(m_fpgaConfig.fpgaIp);
    UiConfig::getInstance()->saveFpgaFpgaPort(m_fpgaConfig.fpgaPort);
}


void TestFpga::GetUserConfig()
{
    m_fpgaConfig.keepTestIfFaled = checkKeepTest->isChecked();
    m_fpgaConfig.reTestIfFailed = checkRetestIfFailed->isChecked();
    m_fpgaConfig.pauseTest = checkPauseTest->isChecked();
    m_fpgaConfig.fpgaIp = editInstrIp->text().toStdString();
    m_fpgaConfig.fpgaPort = editInstrPort->text().toUShort();
}

void TestFpga::StopAllTest(bool save)
{
    StopTestSuite(save);
    labelTestPassNum->setText(QString::number(testTracker.testPass));
    labelTestRunNum->setText(QString::number(testTracker.testRun));
    control->SigGen_DeSetCombo();
    EnableSettingPanel(true);
}

void TestFpga::StartAllTest(const QString &serial, const QString &who)
{
    StartTestSuite(TEMPLATE_FPGA_THUONG, serial, who);
    SetTestState(TestState_Running);
    EnableSettingPanel(false);
    btnStartTest->setText("DỪNG");
}

