#include "testctrlpt.h"


using namespace cppframework;
/**
 * @brief TestCtrlPt::TestCtrlPt create all ui element,
 *                  load configuration and create connection
 * @param parent
 */

TestCtrlPt::TestCtrlPt(Controller *controller, TestBase *parent) :
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
 * @brief TestCtrlPt::~TestCtrlPt
 */
TestCtrlPt::~TestCtrlPt()
{

}

void TestCtrlPt::initVariable()
{
    /**
     * Delay must large enough prevent TCP appends two frames into one package
     */

    waitCtrlPtInMs = 1000;
    testTrackerFile = CONFIG_TEST_TRACK_CTRLPT;
    outputFileName = FILENAME_RES_CTRLPT;
    LoadCtrlPtConfig();
    LoadTestTracker();
    LoadGenConfig();
    InitAllTestName();
}

void TestCtrlPt::createUiElem()
{
    groupConfig = new QGroupBox(tr("CÀI ĐẶT"));
    comSerialList = new QComboBox;
    btnConnectSerial = new QPushButton("KẾT NỐI");

    tableView = new QTableView(this);
    mainLayout = new QVBoxLayout;
    settingLayout = new QFormLayout;
    hLayout = new QHBoxLayout;

    labelHeader = new QLabel("ĐO KIỂM TỰ ĐỘNG TÍNH NĂNG MẠCH ĐIỀU KHIỂN PAN/TILT");
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
}

void TestCtrlPt::createLayout()
{
    settingLayout->addItem(new QSpacerItem(0, 10));
    settingLayout->addRow("CỔNG COM", comSerialList);
    settingLayout->addWidget(btnConnectSerial);
    settingLayout->addItem(new QSpacerItem(0, 10));
    settingLayout->addRow("TIẾP TỤC NẾU FAILED", checkKeepTest);
    settingLayout->addRow("TEST LẠI NẾU FAILED", checkRetestIfFailed);

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

void TestCtrlPt::createElemContent()
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

    checkKeepTest->setChecked(m_ctrlptConfig.keepTestIfFaled);
    checkRetestIfFailed->setChecked(m_ctrlptConfig.reTestIfFailed);

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

    comSerialList->setCurrentIndex(comSerialList->count() - 1);
}

void TestCtrlPt::createTableViewHeader()
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

void TestCtrlPt::createConnection()
{
    /**
     * @brief button connection
     */
    connect(btnStartTest, SIGNAL(clicked(bool)), this, SLOT(on_btnStartTestClicked()));
    connect(btnConnectSerial, SIGNAL(clicked(bool)), this, SLOT(on_btnConnectSerialClicked()));
    connect(comSerialList, SIGNAL(activated(const QString &)), this, SLOT(on_selectComClicked()));

    /**
     * @brief test
     */
    connect(btnTest, SIGNAL(clicked(bool)), this, SLOT(on_btnTestClicked()));

    /**
     * @brief user edit parameter update
     */
    connect(checkKeepTest, SIGNAL(clicked(bool)), this, SLOT(on_updateUserSetting()));
    connect(checkRetestIfFailed, SIGNAL(clicked(bool)), this, SLOT(on_updateUserSetting()));
}


void TestCtrlPt::InitTestResult()
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


void TestCtrlPt::ControlJigPantilt(TestBase::ComParam &param)
{
    PanTilt_Command cmd = Pantilt_Cmd_Max;

    if (param.name == CTRLPT_TEST_RS485) {
        cmd = Pantilt_Test_Rs485;
        currLineResult = 20;
        LREP("TEST RS485\n");
    } else if (param.name == CTRLPT_TEST_TILT) {
        cmd = Pantilt_Test_Tilt;
        currLineResult = 21;
        LREP("TEST TILT\n");
    } else if (param.name == CTRLPT_TEST_PAN) {
        cmd = Pantilt_Test_Pan;
        LREP("TEST PAN\n");
        currLineResult = 22;
    }

    if(cmd != Pantilt_Cmd_Max) {
        uint8_t sendData[10];
        sendData[0] = cmd;
        sendData[1] = 0;
        control->Dev_SendData(JIG_PANTILT_ID, sendData, 2);
        uint32_t delay = 5000 / 100;
        while(GetTestState() == TestState_Running && (delay--) &&
              !getPassFaildByName(param.name)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void TestCtrlPt::InitAllTestName()
{
    m_listTestName.push_back(CTRLPT_TEST_PAN);
    m_listTestName.push_back(CTRLPT_TEST_TILT);
    m_listTestName.push_back(CTRLPT_TEST_RS485);
}


/**
 * @brief TestCtrlPt::DoTestSuiteFunction
 */
void TestCtrlPt::DoTestSuiteFunction()
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
                ControlJigPantilt(test.second);
                ret = getPassFaildByName(test.second.name);
                //LREP("Check: {} - {}\n", test.second.name, ret);
                if(ret) {
                    displayPassedCase(currLineIdx);
                    WriteRowResult("ĐẠT", "PASSED");
                } else {
                    displayFailedCase(currLineIdx);
                    WriteRowResult("KHÔNG ĐẠT", "FAILED");
                }

                if((!m_ctrlptConfig.keepTestIfFaled) && (!ret)) {
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

void TestCtrlPt::on_updateUserSetting()
{
    GetUserConfig();
    SaveCtrlPtConfig();
}


void TestCtrlPt::on_btnTestClicked()
{

}

void TestCtrlPt::on_btnStartTestClicked()
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
            QMessageBox::warning(this, "Lỗi", "Chưa kết nối zig ctrl pan/tilt !");
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


void TestCtrlPt::on_btnConnectSerialClicked()
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


void TestCtrlPt::on_ctrlPtDataEvent(uint8_t *data, int len)
{
    (void)len;
    PanTilt_Command cmd = (PanTilt_Command)data[0];
    Sensor_Result res = (Sensor_Result)data[2];
    bool pass = (res == Sensor_Passed) ? true : false;
    switch(cmd) {    
    case Pantilt_Test_Pan:
        ASSERT(setPassFaildByName(CTRLPT_TEST_PAN, pass));
        break;
    case Pantilt_Test_Tilt:
        ASSERT(setPassFaildByName(CTRLPT_TEST_TILT, pass));
        break;
    case Pantilt_Test_Rs485:
        ASSERT(setPassFaildByName(CTRLPT_TEST_RS485, pass));
        break;

    default:
        break;
    }
}





bool TestCtrlPt::loadTestParam(const CSVFile::CsvVector &data)
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

void TestCtrlPt::clearInputParam()
{
    testHead.clear();
}

/*
 *
 *
 *
*/
void TestCtrlPt::on_btnLoadTestParamClicked()
{
    LoadTestConfigFromFile();
    isTestParmLoaded = true;
}

/*
 *
 *
 *
*/
void TestCtrlPt::LoadTestConfigFromFile()
{
    modeLoaded = "";
    std::string          externalFile = genConfig.inputDir;

    externalFile += ("/board/ctrlpt_thuong.csv");
    if(loadTestConfig(externalFile)) {
        loadTestParam(loader->rows());
        loadTestParamToUi();
    } else {
        LREP("Load failed\n");
    }
    loader.reset();
}


void TestCtrlPt::loadTestParamToUi()
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

void TestCtrlPt::AppendRowTable(QStringList &row)
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

void TestCtrlPt::ConfigController()
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

void TestCtrlPt::EnableSettingPanel(bool en)
{
    btnConnectSerial->setEnabled(en);
    comSerialList->setEnabled(en);
    editSerial->setEnabled(en);
}


void TestCtrlPt::PrintGeneralConfig()
{
    LREP("keep test: {}\n", m_ctrlptConfig.keepTestIfFaled);
    LREP("auto open result: {}\n", m_ctrlptConfig.reTestIfFailed);
}

void TestCtrlPt::LoadCtrlPtConfig()
{
    m_ctrlptConfig = UiConfig::getInstance()->getCtrlPtConfig();
}

void TestCtrlPt::SaveCtrlPtConfig()
{
    UiConfig::getInstance()->saveCtrlPtKeepTestIfFailed(m_ctrlptConfig.keepTestIfFaled);
    UiConfig::getInstance()->saveCtrlPtReTestIfFailed(m_ctrlptConfig.reTestIfFailed);
}


void TestCtrlPt::GetUserConfig()
{
    m_ctrlptConfig.keepTestIfFaled = checkKeepTest->isChecked();
    m_ctrlptConfig.reTestIfFailed = checkRetestIfFailed->isChecked();
    LREP("Check {} - Keep {}", m_ctrlptConfig.reTestIfFailed, m_ctrlptConfig.keepTestIfFaled);
}

void TestCtrlPt::StopAllTest(bool save)
{
    StopTestSuite(save);
    labelTestPassNum->setText(QString::number(testTracker.testPass));
    labelTestRunNum->setText(QString::number(testTracker.testRun));
    control->SigGen_DeSetCombo();
    EnableSettingPanel(true);
}

void TestCtrlPt::StartAllTest(const QString &serial, const QString &who)
{
    StartTestSuite(TEMPLATE_CTRLPT_THUONG, serial, who);
    EnableSettingPanel(false);
    btnStartTest->setText("DỪNG");
}


bool TestCtrlPt::FindText(QString &s)
{
    for(int i = 0; i < comSerialList->count(); i++) {
        if(comSerialList->itemText(i) == s) {
            return true;
        }
    }
    return false;
}

void TestCtrlPt::on_selectComClicked()
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


void TestCtrlPt::on_zigTestConnectEvent(int evt)
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
