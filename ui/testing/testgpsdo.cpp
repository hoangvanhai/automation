#include "testgpsdo.h"
#include <iostream>
#include <protocol/client_msg/msg.pb.h>
#include <isc/utils.h>

using namespace cppframework;
/**
 * @brief TestGpsdo::TestGpsdo create all ui element,
 *                  load configuration and create connection
 * @param parent
 */

TestGpsdo::TestGpsdo(Controller *controller, TestBase *parent) :
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
 * @brief TestGpsdo::~TestGpsdo
 */
TestGpsdo::~TestGpsdo()
{

}

void TestGpsdo::initVariable()
{
    /**
     * Delay must large enough prevent TCP appends two frames into one package
     */

    waitGpsdoInMs = 1000;
    testTrackerFile = CONFIG_TEST_TRACK_GPSDO;
    outputFileName = FILENAME_RES_GPSDO;
    LoadGpsdoConfig();
    LoadTestTracker();
    LoadGenConfig();
    InitAllTestName();
}

void TestGpsdo::createUiElem()
{
    groupConfig = new QGroupBox(tr("CÀI ĐẶT"));
    comSerialList = new QComboBox;
    btnConnectSerial = new QPushButton("KẾT NỐI");

    tableView = new QTableView(this);
    mainLayout = new QVBoxLayout;
    settingLayout = new QFormLayout;
    hLayout = new QHBoxLayout;

    labelHeader = new QLabel("ĐO KIỂM TỰ ĐỘNG TÍNH NĂNG MẠCH GPSDO");
    btnTest = new QPushButton("Test");
    btnStartTest = new QPushButton("BẮT ĐẦU");
    checkKeepTest = new QCheckBox;
    editSerial = new QLineEdit;

    checkRetestIfFailed = new QCheckBox;
    editWhoTest = new QLineEdit;

    manLayout = new QFormLayout;
    mainSettingLayout = new QVBoxLayout;

    groupSetting = new QGroupBox("CÀI ĐẶT");
    groupMan = new QGroupBox("THAO TÁC");

    labelTestRunNum = new QLabel(" ");
    labelTestPassNum = new QLabel(" ");


    editLong = new QDoubleSpinBox;
    editLat = new QDoubleSpinBox;
    editUTC = new QSpinBox;
    editTime = new QDateTimeEdit;

    btnGetParam = new QPushButton("LẤY THỜI GIAN");
    btnSetParam= new  QPushButton("GỬI THAM SỐ");

}

void TestGpsdo::createLayout()
{
    settingLayout->addItem(new QSpacerItem(0, 10));
    settingLayout->addRow("CỔNG COM", comSerialList);
    settingLayout->addWidget(btnConnectSerial);
    settingLayout->addItem(new QSpacerItem(0, 10));
    settingLayout->addRow("TIẾP TỤC NẾU FAILED", checkKeepTest);
    settingLayout->addRow("TEST LẠI NẾU FAILED", checkRetestIfFailed);

    settingLayout->addItem(new QSpacerItem(0, 10));
    settingLayout->addRow("Longitude", editLong);
    settingLayout->addRow("Latitude", editLat);
    settingLayout->addRow("UTC", editUTC);
    settingLayout->addRow("Time", editTime);
    settingLayout->addWidget(btnGetParam);
    settingLayout->addWidget(btnSetParam);

    manLayout->addRow("SỐ LƯỢNG TEST", labelTestRunNum);
    manLayout->addRow("SỐ LƯỢNG PASS", labelTestPassNum);
    manLayout->addRow("NGƯỜI TEST", editWhoTest);
    manLayout->addRow("SERIAL", editSerial);
    manLayout->addWidget(btnStartTest);

    settingLayout->setHorizontalSpacing(1);
    btnStartTest->setFixedHeight(40);
    editWhoTest->setFixedHeight(30);

    settingLayout->setAlignment(checkKeepTest, Qt::AlignCenter);
    settingLayout->setAlignment(checkRetestIfFailed, Qt::AlignCenter);


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

void TestGpsdo::createElemContent()
{
    createTableViewHeader();

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

    checkKeepTest->setChecked(m_gpsdoConfig.keepTestIfFaled);
    checkRetestIfFailed->setChecked(m_gpsdoConfig.reTestIfFailed);

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

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

    editLat->setMaximum(25);
    editLat->setMinimum(15);
    editLong->setMaximum(110);
    editLong->setMinimum(95);
    editLat->setDecimals(6);
    editLong->setDecimals(6);
    editLat->setSingleStep(0.01);
    editLong->setSingleStep(0.01);

    editUTC->setMaximum(12);
    editUTC->setMinimum(-12);
    editUTC->setSingleStep(1);

    editTime->setDisplayFormat("hh:mm - dd/MM/yyyy");
    editTime->setDateTime(QDateTime::currentDateTime());
    editLat->setValue(m_gpsdoConfig.latitude);
    editLong->setValue(m_gpsdoConfig.longitude);
    editUTC->setValue(m_gpsdoConfig.utc);

    //LREP("Load: {}-{}\n", m_gpsdoConfig.latitude, m_gpsdoConfig.longitude);
}

void TestGpsdo::createTableViewHeader()
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

void TestGpsdo::createConnection()
{
    /**
     * @brief button connection
     */
    connect(btnStartTest, SIGNAL(clicked(bool)), this, SLOT(on_btnStartTestClicked()));
    connect(btnConnectSerial, SIGNAL(clicked(bool)), this, SLOT(on_btnConnectSerialClicked()));
    connect(comSerialList, SIGNAL(activated(const QString &)), this, SLOT(on_selectComClicked()));
    connect(btnGetParam, SIGNAL(clicked(bool)), this, SLOT(on_getCurrentLocalTime()));
    connect(btnSetParam, SIGNAL(clicked(bool)), this, SLOT(on_setParamToZig()));

    /**
     * @brief test
     */
    connect(btnTest, SIGNAL(clicked(bool)), this, SLOT(on_btnTestClicked()));

    /**
     * @brief user edit parameter update
     */
    connect(checkKeepTest, SIGNAL(clicked(bool)), this, SLOT(on_updateUserSetting()));
    connect(checkRetestIfFailed, SIGNAL(clicked(bool)), this, SLOT(on_updateUserSetting()));
    connect(editUTC, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(editLat, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(editLong, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
}


void TestGpsdo::InitTestResult()
{
    if(GetTestProgress() == Progress_First_Time) {
        LoadGenConfig();
        clearAllResultAndFailed();
    } else {
        LREP("Retest failed point\n");
        //loadRetestParamToUi();
        clearAllResult();
    }
}


void TestGpsdo::ControlJigGpsdo(TestBase::ComParam &param)
{
    Gpsdo_Command cmd = Gpsdo_Cmd_Max;
    if (param.name == GPSDO_TEST_MESSAGE) {
        cmd = Gpsdo_Test_Message;
        LREP("TEST GPS MESSAGE\n");
        currLineResult = 20;
    } else if (param.name == GPSDO_TEST_PPS) {
        cmd = Gpsdo_Test_PPS;
        currLineResult = 21;
        LREP("TEST PPS\n");
    } else if (param.name == GPSDO_TEST_10M_OUT) {
        cmd = Gpsdo_Test_10Mhz;
        currLineResult = 22;
        LREP("TEST 10Mhz\n");
    }

    if(cmd != Gpsdo_Cmd_Max) {
        uint8_t sendData[10];
        sendData[0] = uint8_t(cmd);
        sendData[1] = 0;
        control->Dev_SendData(JIG_GPSDO_ID, sendData, 2, 0);
        uint32_t delay = 5000 / 100;
        while(GetTestState() == TestState_Running && (delay--) &&
              !getPassFaildByName(param.name)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void TestGpsdo::InitAllTestName()
{
    m_listTestName.push_back(GPSDO_TEST_PPS);
    m_listTestName.push_back(GPSDO_TEST_MESSAGE);
    m_listTestName.push_back(GPSDO_TEST_10M_OUT);
}


/**
 * @brief TestGpsdo::DoTestSuiteFunction
 */
void TestGpsdo::DoTestSuiteFunction()
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
                test.second.result.curPassed = false;
                ControlJigGpsdo(test.second);
                ret = getPassFaildByName(test.second.name);
                //LREP("Check: {} - {}\n", test.second.name, ret);
                if(ret) {
                    displayPassedCase(currLineIdx);
                    WriteRowResult("ĐẠT", "PASSED");
                } else {
                    displayFailedCase(currLineIdx);
                    WriteRowResult("KHÔNG ĐẠT", "FAILED");
                }

                if((!m_gpsdoConfig.keepTestIfFaled) && (!ret)) {
                    break;
                }

                iter++; // Go to next test point
                currLineIdx++;
            }
            if(GetTestState() == TestState_Running) {
                if(checkTotalPassed()) {
                    SetPassed();
                } else {
                    if(checkRetestIfFailed->isChecked()) {
                        QMessageBox::StandardButton answer = QMessageBox::question(
                            this,
                            tr("TEST FAILED"),
                            tr("Bạn muốn chạy lại ?"),
                            QMessageBox::Yes | QMessageBox::No
                        );

                        if(answer == QMessageBox::Yes)
                            continue;
                    }
                    SetFailed();
                }
                emit updateStatusBar("ĐÃ KẾT THÚC BÀI ĐO");
            } else {
                emit updateStatusBar("ĐÃ DỪNG CHƯƠNG TRÌNH ");
                SetFailed();
            }
            btnStartTest->setText("BẮT ĐẦU");
            btnStartTest->setEnabled(true);
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void TestGpsdo::on_updateUserSetting()
{
    GetUserConfig();
    SaveGpsdoConfig();
}


void TestGpsdo::on_btnTestClicked()
{

}

void TestGpsdo::on_btnStartTestClicked()
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

        if(!control->Dev_GetStatus()) {
            QMessageBox::warning(this, "Lỗi", "Chưa kết nối zig gpsdo !");
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
    }
}


void TestGpsdo::on_btnConnectSerialClicked()
{
    ConfigController();

    if(control->Dev_GetStatus()) {
        control->Dev_Stop();
        btnConnectSerial->setText("KẾT NỐI");
        comSerialList->setEnabled(true);
        LREP("Disconnected\n");
    } else {
        LREP("Try to connect\n");
        control->Dev_Start();
    }
}


void TestGpsdo::on_GpsdoDataEvent(uint8_t *data, int len)
{
    (void)len;
    Sensor_Command cmd = (Sensor_Command)data[5];
    Sensor_Result res = (Sensor_Result)data[7];

    bool pass = (res == Sensor_Passed) ? true : false;
    switch(cmd) {
    case Command_Test_Ethernet_23_10G:
        ASSERT(setPassFaildByName(GPSDO_TEST_PPS, pass));
        break;
    case Command_Test_Ps_Ram:
        ASSERT(setPassFaildByName(GPSDO_TEST_MESSAGE, pass));
        break;
    case Command_Test_Pl_Ram:
        ASSERT(setPassFaildByName(GPSDO_TEST_10M_OUT, pass));
        break;

    default:
        break;
    }
}





bool TestGpsdo::loadTestParam(const CSVFile::CsvVector &data)
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

void TestGpsdo::clearInputParam()
{
    testHead.clear();
}

/*
 *
 *
 *
*/
void TestGpsdo::on_btnLoadTestParamClicked()
{
    LoadTestConfigFromFile();
    isTestParmLoaded = true;
}

/*
 *
 *
 *
*/
void TestGpsdo::LoadTestConfigFromFile()
{
    modeLoaded = "";
    std::string          externalFile = genConfig.inputDir;

    externalFile += ("/board/gpsdo_thuong.csv");
    if(loadTestConfig(externalFile)) {
        loadTestParam(loader->rows());
        loadTestParamToUi();
    } else {
        LREP("Load failed\n");
    }
    loader.reset();
}


void TestGpsdo::loadTestParamToUi()
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

void TestGpsdo::AppendRowTable(QStringList &row)
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

void TestGpsdo::ConfigController()
{
    /**
     * @brief connection event
     */
    control->disconnectAllConnection();    
    control->addConnection(connect(control, SIGNAL(sigSerialDevStatus(int)), SLOT(on_zigTestConnectEvent(int))));
    if(control) {        
        control->ConfigIsc(comSerialList->currentText().toStdString(), 115200);
    }
}

void TestGpsdo::EnableSettingPanel(bool en)
{
    btnConnectSerial->setEnabled(en);
    comSerialList->setEnabled(en);
    editSerial->setEnabled(en);
}


void TestGpsdo::PrintGeneralConfig()
{
    LREP("keep test: {}\n", m_gpsdoConfig.keepTestIfFaled);
    LREP("auto open result: {}\n", m_gpsdoConfig.reTestIfFailed);
}

void TestGpsdo::LoadGpsdoConfig()
{
    m_gpsdoConfig = UiConfig::getInstance()->getGpsdoConfig();
}

void TestGpsdo::SaveGpsdoConfig()
{
    UiConfig::getInstance()->saveGpsdoKeepTestIfFailed(m_gpsdoConfig.keepTestIfFaled);
    UiConfig::getInstance()->saveGpsdoReTestIfFailed(m_gpsdoConfig.reTestIfFailed);
    UiConfig::getInstance()->saveGpsdoLatitude(m_gpsdoConfig.latitude);
    UiConfig::getInstance()->saveGpsdoLongitude(m_gpsdoConfig.longitude);
    UiConfig::getInstance()->saveGpsdoUTC(m_gpsdoConfig.utc);
}


void TestGpsdo::GetUserConfig()
{
    m_gpsdoConfig.keepTestIfFaled = checkKeepTest->isChecked();
    m_gpsdoConfig.reTestIfFailed = checkRetestIfFailed->isChecked();
    m_gpsdoConfig.longitude = editLong->value();
    m_gpsdoConfig.latitude = editLat->value();
    m_gpsdoConfig.utc = editUTC->text().toInt();
}

void TestGpsdo::StopAllTest(bool save)
{
    StopTestSuite(save);
    labelTestPassNum->setText(QString::number(testTracker.testPass));
    labelTestRunNum->setText(QString::number(testTracker.testRun));
    control->SigGen_DeSetCombo();
    EnableSettingPanel(true);
}

void TestGpsdo::StartAllTest(const QString &serial, const QString &who)
{
    StartTestSuite(TEMPLATE_GPSDO_THUONG, serial, who);
    EnableSettingPanel(false);
    btnStartTest->setText("DỪNG");
}


bool TestGpsdo::FindText(QString &s)
{
    for(int i = 0; i < comSerialList->count(); i++) {
        if(comSerialList->itemText(i) == s) {
            return true;
        }
    }
    return false;
}

void TestGpsdo::on_selectComClicked()
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

void TestGpsdo::on_zigTestConnectEvent(int evt)
{
    switch(evt) {
        case communication::Event_Connected:
        LREP("Event Connected to RFDelay\r\n");
        btnConnectSerial->setText("NGẮT KẾT NỐI");
        break;
    case communication::Event_Disconnected:
        btnConnectSerial->setText("KẾT NỐI");
        SetTestState(TestState_Stop);
        EnableSettingPanel(true);
        QMessageBox::warning(this, "Lỗi", "Không mở được cổng \"" +
                             comSerialList->currentText() + "\" cổng đang bận hoặc không có quyền!");
        break;

    default:
        break;

    }
}

void TestGpsdo::on_getCurrentLocalTime()
{
    editTime->setDateTime(QDateTime::currentDateTime());
}

/**
 * @brief TestGpsdo::on_setParamToZig
 *
 *                                   4       1      1     1       1       1     4     4
 * Format parameters send to zig: | year | month | day | hour | minute | UTC | lat | long |
 *
 */

void TestGpsdo::on_setParamToZig()
{
    uint8_t sendData[50];

    QDateTime dt = editTime->dateTime();
    int8_t utc = (int8_t)editUTC->text().toInt();
    float longitude, latitude;
    longitude = (float)editLong->value();
    latitude = (float)editLat->value();    

    QDate date = dt.date();
    QTime time = dt.time();

    int32_t year = date.year();
    uint8_t month = date.month(), day =date.day(),
            hour = time.hour(), minute = time.minute(), idx = 2;

    sendData[idx++] = (year >> 24) & 0xFF;
    sendData[idx++] = (year >> 16) & 0xFF;
    sendData[idx++] = (year >> 8) & 0xFF;
    sendData[idx++] = (year & 0xFF);

    sendData[idx++] = month;
    sendData[idx++] = day;
    sendData[idx++] = hour;
    sendData[idx++] = minute;
    sendData[idx++] = utc;


    Utils::Float latValue, longValue;
    latValue.num = latitude;
    longValue.num = longitude;

    sendData[idx++] = latValue.buffer[0];
    sendData[idx++] = latValue.buffer[1];
    sendData[idx++] = latValue.buffer[2];
    sendData[idx++] = latValue.buffer[3];

    sendData[idx++] = longValue.buffer[0];
    sendData[idx++] = longValue.buffer[1];
    sendData[idx++] = longValue.buffer[2];
    sendData[idx++] = longValue.buffer[3];

    sendData[1] = idx - 2;
    sendData[0] = 0x01;

    control->Dev_SendData(JIG_GPSDO_ID, sendData, idx);
}




