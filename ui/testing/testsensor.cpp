#include "testsensor.h"
#include <iostream>
#include <protocol/client_msg/msg.pb.h>
#include <isc/utils.h>

using namespace cppframework;
/**
 * @brief TestSensor::TestSensor create all ui element,
 *                  load configuration and create connection
 * @param parent
 */
TestSensor::TestSensor(Controller *controller, TestBase *parent) :
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
 * @brief TestSensor::~TestSensor
 */
TestSensor::~TestSensor()
{

}

void TestSensor::initVariable()
{
    /**
     * Delay must large enough prevent TCP appends two frames into one package
     */
    genConfig.siggenDelay = 200;
    genConfig.serverDelay = 20000;
    floorValue = 10;
    changeMiss = false;
    testTrackerFile = CONFIG_TEST_TRACK_SENSOR;
    outputFileName = FILENAME_RES_SENSOR;
    LoadSensorConfig();
    LoadTestTracker();
    InitAllTestName();
    isSaveCfg = false;
}

void TestSensor::createUiElem()
{
    groupConfig = new QGroupBox(tr("CÀI ĐẶT"));
    comboTestMode   = new QComboBox;
    labelTestMode = new QLabel("CHỌN CHẾ ĐỘ");

    labelInstrIp = new QLabel("ĐỊA CHỈ SIGNAL GEN");
    editInstrIp = new QLineEdit;
    labelServerIp = new QLabel("ĐỊA CHỈ SERVER");
    editServerIp = new QLineEdit;
    btnConnectInstr = new QPushButton("KẾT NỐI");
    btnConnectServer = new QPushButton("KẾT NỐI");

    tableView = new QTableView(this);
    mainLayout = new QVBoxLayout;
    settingLayout = new QFormLayout;
    hLayout = new QHBoxLayout;

    labelHeader = new QLabel("ĐO KIỂM TỰ ĐỘNG CHỈ TIÊU SENSOR");    
    btnTestCaseSetting =  new QPushButton("CẤU HÌNH BÀI ĐO");
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

    editInstrPort = new QLineEdit;
    editServerPort  = new QLineEdit;
    editServerUdpPort = new QLineEdit;

    labelSslStatus = new QLabel("KHÔNG KẾT NỐI");
    labelInstrStatus = new QLabel("KHÔNG KẾT NỐI");

    labelTestRunNum = new QLabel(" ");
    labelTestPassNum = new QLabel(" ");

    editTest = new QTextEdit;

    editFloor = new QLineEdit;
    btnFloor = new QPushButton("SET NOISE FLOOR");
    comTestType = new QComboBox;
    btnTestType = new QPushButton("SET MISS TYPE");
    btnPause = new QPushButton("TẠM DỪNG");

}

void TestSensor::createLayout()
{

    settingLayout->addRow(labelTestMode, comboTestMode);
    settingLayout->addWidget(btnLoadTestParam);
    settingLayout->addWidget(btnTestCaseSetting);
    settingLayout->addItem(new QSpacerItem(0, 10));
    settingLayout->addRow(labelInstrIp, editInstrIp);
    settingLayout->addRow("CỔNG TCP", editInstrPort);
    settingLayout->addRow("TRẠNG THÁI", labelInstrStatus);
    labelInstrStatus->setStyleSheet("QLabel {color : red; }");
    settingLayout->addRow("SIGNAL GENERATOR", btnConnectInstr);
    settingLayout->addItem(new QSpacerItem(0, 10));
    settingLayout->addRow(labelServerIp, editServerIp);
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
    manLayout->addWidget(btnPause);
//    manLayout->addRow(editTest);
//    manLayout->addWidget(btnTest);
    manLayout->addRow(editFloor, btnFloor);
    manLayout->addRow(comTestType, btnTestType);

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

void TestSensor::createElemContent()
{
    createTableViewHeader();

    comboTestMode->addItem(tr("ĐIỀU KIỆN THƯỜNG"));
    comboTestMode->addItem(tr("NÓNG"));
    comboTestMode->addItem(tr("LẠNH"));
    comboTestMode->addItem(tr("MÔI TRƯỜNG"));
    comboTestMode->addItem(tr("LÃO HÓA"));
    comboTestMode->addItem(tr("RUNG SÓC VA ĐẬP"));

    comTestType->addItem(tr("HOLD"));
    comTestType->addItem(tr("SHIFT"));

    comboTestMode->setMinimumHeight(25);
    comboTestMode->setEditable(true);
    comboTestMode->lineEdit()->setReadOnly(true);
    comboTestMode->lineEdit()->setAlignment(Qt::AlignCenter);
    for(int i = 0; i < comboTestMode->count(); i++) {
        comboTestMode->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
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

    editInstrIp->setText(QString(m_sensorConfig.SigGenIp.c_str()));
    editInstrPort->setText(QString::number(m_sensorConfig.siggenPort));
    editServerIp->setText(QString(m_sensorConfig.ServerIp.c_str()));
    editServerPort->setText(QString::number(m_sensorConfig.sslPort));
    editServerUdpPort->setText(QString::number(m_sensorConfig.udpPort));

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

    checkKeepTest->setChecked(m_sensorConfig.keepTestIfFaled);
    checkRetestIfFailed->setChecked(m_sensorConfig.reTestIfFailed);

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    editTest->setText("Log data");
    editFloor->setText(QString::number( floorValue));
}

void TestSensor::createTableViewHeader()
{
    tableView->setWordWrap(true);
    QStringList header;

    header << "Bài kiểm tra" << "Trạng thái" << "Giá trị" << "Min" << "Max" << "Thông tin";
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

void TestSensor::createConnection()
{
    /**
     * @brief button connection
     */
    connect(btnTestCaseSetting, SIGNAL(clicked(bool)), this, SLOT(on_btnSettingClicked()));
    connect(btnLoadTestParam, SIGNAL(clicked(bool)), this, SLOT(on_btnLoadTestParamClicked()));
    connect(btnStartTest, SIGNAL(clicked(bool)), this, SLOT(on_btnStartTestClicked()));
    connect(btnPause, SIGNAL(clicked(bool)), this, SLOT(on_btnPauseClicked()));    
    connect(btnConnectServer, SIGNAL(clicked(bool)), this, SLOT(on_btnConnectServerClicked()));
    connect(btnConnectInstr, SIGNAL(clicked(bool)), this, SLOT(on_btnConnectSignalGenClicked()));
    connect(btnFloor, SIGNAL(clicked(bool)), this, SLOT(on_btnSetNoiseFloorClicked()));
    connect(btnTestType, SIGNAL(clicked(bool)), this, SLOT(on_btnTestTypeClicked()));    


    /**
     * @brief user edit parameter update
     */
    connect(editServerIp, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(editServerPort, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(editServerUdpPort, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(editInstrIp, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(editInstrPort, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(checkKeepTest, SIGNAL(clicked(bool)), this, SLOT(on_updateUserSetting()));
    connect(checkRetestIfFailed, SIGNAL(clicked(bool)), this, SLOT(on_updateUserSetting()));

    /**
     * @brief connection event
     */
    control->addConnection(connect(control, SIGNAL(sigServerStatus(int)), this, SLOT(on_SslClientConnectEvent(int))));
    control->addConnection(connect(control, SIGNAL(sigSigGenStatus(int)), this, SLOT(on_SiggenConnectEvent(int))));
    control->addConnection(connect(control, SIGNAL(sigSignalRecv(quint64)),this, SLOT(on_DataReceived(quint64))));
}



/**
 * @brief TestSensor::StartTestSuite
 */


/**
 * @brief TestSensor::GetTestState
 * @return
 */


void TestSensor::InitTestResult()
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
    control->Server_SetNoiseFloor(0, floorValue);
    control->Server_ClearSignalDataBase();
}



/**
 * @brief TestSensor::DoTestCurrent
 */
void TestSensor::DoTestCurrent(ComParam &param, TestProgress progress)
{
    (void)progress;
    std::vector<double>::iterator iter  = param.input.freqList.begin();
    while(IsKeepgoingOnTest() && iter != param.input.freqList.end()) {
        double freq = *iter;
        emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");
        emit updateStatusBar("Đang kiểm tra dòng tiêu thụ tại: " + QString::number(freq, 'g', 10) + " Mhz ...");
        control->Server_SetRecvFreq(freq, BW_40_MHZ, 0);

        TestSuiteDelay(genConfig.serverDelay);

        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;


        emit showInputDialog("Nhập giá trị dòng điện: ");
        m_confirm = false;
        m_value = INT32_MAX;
        param.result.hasValue = false;

        uint32_t count = 1000;
        while(!m_confirm && count-- > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        if(m_value != INT32_MAX) {
            param.result.hasValue = true;
            param.result.currValue = m_value;
        }


        if(param.result.hasValue) {            
            testPoint.value = param.result.currValue;
            // Check pass fail
            if(param.result.currValue >= param.input.min &&
                    param.result.currValue <= param.input.max ) {
                testPoint.passed = true;
                displayAndWriteResultRow(testPoint, true);
            }else {
                testPoint.passed = false;
                displayAndWriteResultRow(testPoint, false);
            }

            // Show value is readed
            displayValueOfFreq(param.result.currValue);

            // store result
            param.result.listResult.push_back(testPoint);
        } else {
            displayAndWriteResultRow(testPoint, QString("N/A"));
            displayValueOfFreq("N/A");
            emit updateStatusBar("Không nhận được kết quả dòng điện từ bộ nguồn !!!", QColor(Qt::red));
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        if((!m_sensorConfig.keepTestIfFaled) && (!testPoint.passed)) {
            break;
        }

        iter++;
    }
}



/**
 * @brief TestSensor::DoTestSensitive
 *
 *
Bước 1. Cấu hình khối xử lý trung tâm
Cấu hình tần số thu của VER – SI3 từ 20 MHz đến 60 MHz
Lựa chọn chiều dài thời gian thu 5s đến 10s cho cửa sổ waterfall (cấu hình trong cửa sổ Search)
Bước 2. Thiết lập máy phát tín hiệu cao tần
Đưa máy phát tín hiệu về trạng thái ban đầu : Ấn Preset;
Lựa chonh điều chế FM với băng thông 12.5 kHz (Tần số baseband 1 kHz, độ di tần 5,6 kHz);
điều chỉnh mức công suất đầu ra máy phát cao tần mức -120 dBm
Chọn chế độ ALC off;
Bật chế độ điều chế:
 Mod on/off (đèn tín hiệu trên máy sáng xanh)
Thiết lập tần số cao tần trên máy phát tín hiệu cao tần là 25,025 MHz tương ứng với kênh cần kiểm tra;
 Ấn FREQ  Chọn tần số tương ứng;
Thiết lập mức cao tần phát ra. Bắt đầu từ -110 dBm;
 Ấn AMPTD  -110 dBm;
Tắt đường cao tần ( RF on/off).
Bước 4. Bắt đầu thực hiện đo
 Thực hiện phát tín hiệu cao tần từ máy phát tín hiệu vào thiết bị cần kiểm tra.
 Bật RF on/off (đèn tín hiệu báo bật);
Nhìn trên màn hình phân tích thác nước water fall đã xuất hiện vạch phổ
 Nếu tín hiệu được phát hiện và hiển thị trong cửa sổ danh sách tín hiệu thì giá trị độ nhạy phát hiện tín hiệu là -110 dBm.
 Nếu chưa thấy thì thực hiện theo bước 5.
Bước 5. Tìm độ nhạy
Tắt tín hiệu cao tần từ máy phát tín hiệu:
 Tắt RF on/off (đèn tín hiệu báo tắt)
Tăng mức cao tần trên máy phát tín hiệu cao tần mỗi bước 1dB.
Thực hiện phát tín hiệu cao tần từ máy phát tín hiệu:
 Bật RF on/off (đèn tín hiệu báo bật)
Kiểm tra tín hiệu trên màn hình hiển thị nếu vẫn chưa thấy thì thực hiện theo bước 6.
Bước 6:
Thực hiện theo bước 5 cho đến khi trên cửa sổ danh sách tín hiệu xuất hiện tín hiệu được phát từ máy phát
Giá trị độ nhạy hiện tại là giá trị máy phát tín hiệu cao tần (dBm);
Ghi lại kết quả đo được vào phụ lục 1.
Bước 7. Thực hiện đo độ nhạy thu tại các tần số còn lại theo quy định
Thực hiện tương tự để đo độ nhạy của máy ở các tần số theo yêu cầu, đọc và ghi kết quả đo được vào phiếu kiểm tra theo theo phụ lục tương ứng.
 */

/*
Trước khi phát từ máy đo, kiểm tra signal đối với tần kiểm tra xem có không (spur)
*/
void TestSensor::DoTestSensitive(ComParam &param, TestProgress progress)
{    
    (void)progress;
    if(param.input.freqTestList.size() == 0)
        return;

    double currPwr = param.input.max;
    double currentMiss;
    param.result.hasValue = false;

    std::vector<double>::iterator iter  = param.input.freqTestList.begin();
    control->SigGen_SetCombo(*iter, Freq_Mhz,
                            currPwr, Power_dBm,
                            1.0, Freq_Khz,
                            genConfig.siggenDelay); //Control server, freq passed is Mhz

    control->Server_SetGain(0, param.input.gain);
    control->Server_SetNoiseFloor(0, param.input.noisefloor);
    currentMiss = *iter + 40;
    emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");
    if(!changeMiss) {
        control->Server_SetRecvFreq(*iter, BW_40_MHZ, 0);
        uint32_t count = genConfig.serverDelay / 100;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }while(IsKeepgoingOnTest() && (count--));
    }

    if(GetTestState() == TestState_Pause) {
        emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
        PauseTest();
        control->SigGen_InitDevice();
    }

    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {
        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
            control->SigGen_InitDevice();
        }
        double freq = *iter;
        emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");
        emit updateStatusBar("Đang kiểm tra độ nhạy phát hiện tín hiệu tại: " + QString::number(freq, 'g', 10) + " Mhz ...");
        control->currFreqExp = freq * 1E6;
        currPwr = param.input.max;

        control->Server_ClearSignaListReceived();
        control->SigGen_SetRFSignalOut(false, genConfig.siggenDelay * 2);

        bool changed = false;
        if(changeMiss) {            
            control->Server_SetRecvFreq(freq, BW_40_MHZ, 0);
            control->Server_SetNoiseFloor(0, param.input.noisefloor);
            changed = true;
        } else {
            if(freq >= currentMiss) {
                changed = true;
                currentMiss = freq + 40.0;
                control->Server_SetRecvFreq(currentMiss - 20.0, BW_40_MHZ, 0);
                control->Server_SetNoiseFloor(0, param.input.noisefloor);
            }
        }

        // Check signal list if has spur
        bool hasSpur = control->Server_CheckHasSignalFrequency(uint64_t(freq * 1E6), param.input.ferr);

        if (!hasSpur) { // Nếu không có spur
            control->SigGen_SetRFPower(currPwr, Power_dBm, genConfig.siggenDelay);
            control->SigGen_SetRFFreq(freq, Freq_Mhz, genConfig.siggenDelay);
            control->SigGen_SetRFSignalOut(true, genConfig.siggenDelay);

            double check = 0;
            uint32_t count = genConfig.serverDelay / 100;
            do {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                check = control->Server_CheckSignalPower((uint64_t(freq * 1E6)), param.input.ferr);
            }while(IsKeepgoingOnTest() && (count--) && check == 0 && changed);

            changed = false;
        }

        double getPwr = 0;
        // Nếu đã tăng đến max mà không nhận được tín hiệu thì thoát vòng lặp
        // Bất kỳ lúc nào phát hiện tín hiệu thì thoát vòng lặp
        while(!hasSpur && IsKeepgoingOnTest() &&
              !param.result.hasValue &&
              std::abs(currPwr) > std::abs(param.input.min)) {

            emit updateStatusBar("Đang kiểm tra tần: " +
                                 QString::number(freq, 'g', 10) + " Mhz. Công suất máy phát " +
                                 QString::number(currPwr) + " dBm");

            // Control instrument
            control->SigGen_SetRFPower(currPwr, Power_dBm, genConfig.siggenDelay);


            uint32_t count = 14;
            do {
                std::this_thread::sleep_for(std::chrono::milliseconds(genConfig.siggenDelay /4));
                getPwr = control->Server_CheckHasSignalPower((uint64_t(freq * 1E6)), param.input.ferr);
            }while((count--) && getPwr == 0);

            // Nếu có tín hiệu trong danh sách
            if(0 > getPwr) {
                param.result.hasValue = true;
                LREP("\n\nFrequency {} found {} at {} dbm!\n\n\n", freq * 1E6, getPwr, currPwr);
                break;
            }
            // Kiểm tra độ nhậy phát hiện tín hiệu với bước tăng công suất máy phát 1dBm
            currPwr+=1.0;
        }

        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;

        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }

        if(param.result.hasValue) {
            param.result.currValue = currPwr;
            testPoint.value = param.result.currValue;
            // Check pass fail
            if(param.result.currValue <= param.input.min &&
                    param.result.currValue  >= param.input.max) {
                testPoint.passed = true;
                displayAndWriteResultRow(testPoint, true, getPwr);
            }else {
                testPoint.passed = false;
                displayAndWriteResultRow(testPoint, false);
            }

            param.result.hasValue = false;
            // Show value is readed
            displayValueOfFreq(param.result.currValue);

        } else {
            if(hasSpur) {
                displayAndWriteResultRow(testPoint, QString("SPUR DETECTED"));
                displayValueOfFreq("SPUR DETECTED");
                emit updateStatusBar("Phát hiện spur: " +
                                     QString::number(freq, 'g', 10) + " Mhz !!!", QColor(Qt::red));
            } else {
                displayAndWriteResultRow(testPoint, QString("N/A"));
                displayValueOfFreq("N/A");
                emit updateStatusBar("Không nhận được kết quả độ nhạy từ server tại: " +
                                     QString::number(freq, 'g', 10) + " Mhz !!!", QColor(Qt::red));
            }
        }        

        if(!testPoint.passed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
        }

        param.result.listResult.push_back(testPoint);

        if((!m_sensorConfig.keepTestIfFaled) && (!testPoint.passed)) {
            break;
        }

        iter++;
    }

    control->SigGen_DeSetCombo(200);
}


/**
 * @brief TestSensor::DoTestErrorPower
 *
 *
 * Bước 1. Cấu hình khối xử lý trung tâm
Cấu hình tần số thu VER – SI3 từ 20 MHz đến 60 MHz
Lựa chọn chiều dài thời gian thu 5s đến 10s cho cửa sổ waterfall (cấu hình trong cửa sổ Search)
Bước 2. Thiết lập máy phát tín hiệu cao tần
Đưa máy về trạng thái ban đầu : Ấn Preset;
Lựa chọn chế độ điều chế FM với băng thông 12.5 kHz ((Tần số baseband 1 kHz, độ di tần 5,6 kHz);
Điều chỉnh mức dông suất đầu ra cao tần -60 dBm
Chọn chế độ ALC off;
Bật chế độ điều chế:
 Mod on/off (đèn tín hiệu trên máy sáng xanh)
Thiết lập tần số cao tần trên máy phát tín hiệu cao tần là 25,025 MHz tương ứng với kênh cần kiểm tra;
 Ấn FREQ  Chọn tần số tương ứng;
Thiết lập mức cao tần phát ra. -60 dBm;
 Ấn AMPTD  -60 dBm;
Tắt đường cao tần ( RF on/off).
Bước 3. Bắt đầu thực hiện đo
 Thực hiện phát tín hiệu cao tần từ máy phát tín hiệu vào thiết bị cần kiểm tra.
 Bật RF on/off (đèn tín hiệu báo bật);
Nhìn trên màn hình phân tích phổ thác nước waterfall đã xuất hiện vạch phổ của tín hiệu từ máy phát cao tần phát vào.
Bước 4. Tìm giá trị công suất
Di chuyển chuột đến vị trí vạch phổ vừa xuất hiện, 1 cửa sổ về thông tin tín hiệu tự động mở ra.
Nhìn trên ô hiển thị tham số tín hiệu giá trị công suất đo được.
Ghi lại kết quả đo được vào phiếu kiểm tra.
Bước 5. Thực hiện đo công suất tại các tần số còn lại theo quy định
Thực hiện tương tự để đo công suất của máy ở các tần số theo yêu cầu, đọc và ghi kết quả đo được vào phiếu kiểm tra theo theo phụ lục tương ứng.

 */
void TestSensor::DoTestErrorPower(ComParam &param, TestProgress progress)
{
    (void)progress;
    if(param.input.freqTestList.size() == 0)
        return;    

    double currentMiss;
    std::vector<double>::iterator iter  = param.input.freqTestList.begin();
    control->SigGen_SetCombo(*iter, Freq_Mhz,
                            -60, Power_dBm,
                            1.0, Freq_Khz,
                            genConfig.siggenDelay);

    control->Server_SetGain(0, param.input.gain);
    control->Server_SetNoiseFloor(0, param.input.noisefloor);
    currentMiss = *iter + 40;    
    emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");

    if(!changeMiss) {
        control->Server_SetRecvFreq(*iter, BW_40_MHZ, 0);
        uint32_t count = genConfig.serverDelay / 100;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }while(IsKeepgoingOnTest() && (count--));
    }

    if(GetTestState() == TestState_Pause) {
        emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
        PauseTest();
        control->SigGen_InitDevice();
    }

    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {
        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
            control->SigGen_InitDevice();
        }

        double freq = *iter;
        emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");
        emit updateStatusBar("Đang kiểm tra sai số đo công suất tại: " +
                             QString::number(freq, 'g', 10) + " Mhz ...");        
        control->currFreqExp = freq * 1E6;
        // Đặt công suất phát -60dBm
        control->SigGen_SetRFFreq(freq, Freq_Mhz, genConfig.siggenDelay);
        control->SigGen_SetRFSignalOut(true, genConfig.siggenDelay);

        if(changeMiss) {
            control->Server_SetRecvFreq(freq, BW_40_MHZ, 0);
        } else {
            if(freq >= currentMiss) {
                currentMiss = freq + 40.0;
                control->Server_SetRecvFreq(currentMiss - 20.0, BW_40_MHZ, 0);
            }
        }

        double pwr = 0;
        uint32_t count = genConfig.serverDelay / 100;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            pwr = control->Server_CheckHasSignalPower(uint64_t(freq * 1E6), param.input.ferr);
        }while(IsKeepgoingOnTest() && (count--) && (pwr == 0));

        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;        

        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }

        LREP("________PWR:{}_______\n", pwr);
        if(SENSOR_RESET_VAL == true) { // For test
            static bool log = true;
            //log = !log;
            if(log)
                pwr = -58;
            else
                pwr = -68;
        }

        if(pwr < 0) {
            // Kiểm tra sai số công suất thu được so với công suất từ máy signal generator
            param.result.currValue = std::abs(pwr - (-60));
            LREP("Pwr error: {}\n", param.result.currValue );
            testPoint.value = param.result.currValue ;
            // Check pass fail
            if(param.result.currValue >= param.input.min &&
                    param.result.currValue  <=  param.input.max ) {
                testPoint.passed = true;
                displayAndWriteResultRow(testPoint, true, pwr);
            }else {
                testPoint.passed = false;
                displayAndWriteResultRow(testPoint, false, pwr);
            }

            // Show value is readed
            displayValueOfFreq(param.result.currValue);

        } else {
            displayAndWriteResultRow(testPoint, QString("N/A"));
            displayValueOfFreq("N/A");

            emit updateStatusBar("Không nhận được kết quả sai số công suất tại: " +
                                 QString::number(freq, 'g', 10) + " Mhz !!!", QColor(Qt::red));            
        }        

        if(testPoint.passed == false && m_sensorConfig.reTestIfFailed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
            LREP("FAIL LIST IS: {}\n", param.input.failFreqList.size());
        }

        param.result.listResult.push_back(testPoint);
        if((!m_sensorConfig.keepTestIfFaled) && (!testPoint.passed)) {
            break;
        }

        control->SigGen_SetRFSignalOut(false, genConfig.siggenDelay);
        iter++;
    }

    control->SigGen_DeSetCombo(200);
}

/**
 * @brief TestSensor::DoTestBw25kH
 *
Bài đo băng thông tín hiệu có băng thông lớn hơn 25kHz
Bước 1. Cấu hình khối xử lý trung tâm
Cấu hình tần số thu của VER – SI3 từ 20 MHz đến 60 MHz
Lựa chọn chiều dài thời gian thu 5s đến 10s cho cửa sổ waterfall (cấu hình trong cửa sổ Search)
Bước 2. Thiết lập máy phát tín hiệu cao tần
Đưa máy về trạng thái ban đầu : Ấn Preset;
Lựa chinh chế độ điều chế FM với băng thông 30Khz (Tần số baseband 5 kHz, độ di tần 5,6 kHz);
Điều chỉnh mức công suất đầu ra mức -60 dBm
Chọn chế độ ALC off;
Bật chế độ điều chế:
 Mod on/off (đèn tín hiệu trên máy sáng xanh)
Thiết lập tần số cao tần trên máy phát tín hiệu cao tần là 25,025 MHz tương ứng với kênh cần kiểm tra;
 Ấn FREQ  Chọn tần số tương ứng;
Thiết lập mức cao tần phát ra. -60 dBm;
 Ấn AMPTD  -60 dBm;
Tắt đường cao tần ( RF on/off).
Bước 3. Bắt đầu thực hiện đo
 Thực hiện phát tín hiệu cao tần từ máy phát tín hiệu vào thiết bị cần kiểm tra.
 Bật RF on/off (đèn tín hiệu báo bật);
Nhìn trên màn hình phân tích phổ thác nước waterfall đã xuất hiện vạch phổ của tín hiệu từ máy phát cao tần phát vào.
Bước 4. Tìm giá trị băng thông
Di chuyển chuột đến vị trí vạch phổ vừa xuất hiện, cửa sổ về thông tin tín hiệu tự động mở ra.
Nhìn trên ô hiển thị tham số tín hiệu giá trị băng thông đo được.
Ghi lại kết quả đo được vào phụ lục 1.
Bước 5. Thực hiện đo băng thông tại các tần số còn lại theo quy định
Thực hiện tương tự để đo băng thông của máy ở các tần số theo yêu cầu, đọc và
ghi kết quả đo được vào phiếu kiểm tra theo theo phụ lục tương ứng.

 */
void TestSensor::DoTestBw25kH(ComParam &param, TestProgress progress)
{
    (void)progress;
    double currentMiss;
    if(param.input.freqTestList.size() == 0)
        return;

    std::vector<double>::iterator iter = param.input.freqTestList.begin();
    control->SigGen_SetFMARB(100E3, *iter, Freq_Mhz,
                             genConfig.loadFileHighName,
                             -60, Power_dBm, genConfig.siggenDelay);


    currentMiss = *iter + 40;    
    control->Server_SetGain(0, param.input.gain);
    control->Server_SetNoiseFloor(0, param.input.noisefloor);
    emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");

    if(!changeMiss) {
        control->Server_SetRecvFreq(*iter, BW_40_MHZ, 0);
        uint32_t count = genConfig.serverDelay / 100;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }while(IsKeepgoingOnTest() && (count--));
    }

    if(GetTestState() == TestState_Pause) {
        emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
        PauseTest();
        control->SigGen_InitDevice();
    }

    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {
        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
            control->SigGen_InitDevice();
        }
        double freq = *iter;
        emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");
        emit updateStatusBar("Đang kiểm tra sai số đo băng thông > 25Khz tại: " +
                             QString::number(freq, 'g', 10) + " Mhz ...");

        control->SigGen_SetRFFreq(freq, Freq_Mhz, genConfig.siggenDelay);
        control->SigGen_SetRFSignalOut(true, genConfig.siggenDelay);
        control->Server_SetSigCalc(1, 0, 20, 100);
        control->currFreqExp = freq * 1E6;

        if(changeMiss) {            
            control->Server_SetRecvFreq(freq, BW_40_MHZ, 0);
        } else {
            if(freq >= currentMiss) {
                currentMiss = freq + 40.0;                
                control->Server_SetRecvFreq(currentMiss - 20.0, BW_40_MHZ, 0);
            }
        }

        uint32_t bw  = 0;
        uint32_t count = genConfig.serverDelay / 100;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            bw = control->Server_CheckBandwidth(freq * 1E6, param.input.ferr);
        }while(IsKeepgoingOnTest() && (count--) && (bw == 0));

        LREP("Recv bandwidth {}\n", bw);
        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;

        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }

        if(SENSOR_RESET_VAL == true) { // For test
            static bool log = true;
            //log = !log;
            if(log)
                bw = genConfig.bandwidthHigh;
            else
                bw = genConfig.bandwidthHigh * 2;
        }

        if(bw) {                        
            // Kiểm tra sai số so với bw = 30 Khz
            param.result.currValue = (int(bw - genConfig.bandwidthHigh) /
                                       (float)genConfig.bandwidthHigh) * 100.0;
            testPoint.value = param.result.currValue ;
            LREP("Err bw high: {} %\n", param.result.currValue );
            // Check pass fail
            if(param.result.currValue  >= param.input.min &&
                    param.result.currValue  <= param.input.max) {
                testPoint.passed = true;
                displayAndWriteResultRow(testPoint, true, bw);
            }else {
                testPoint.passed = false;
                displayAndWriteResultRow(testPoint, false);
            }

            // Show value is readed
            displayValueOfFreq(param.result.currValue);

        } else {
            displayAndWriteResultRow(testPoint, QString("N/A"));
            displayValueOfFreq("N/A");
            emit updateStatusBar("Không nhận được kết quả sai số băng thông > 25K tại: " +
                                 QString::number(freq, 'g', 10) + " Mhz !!!", QColor(Qt::red));
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        if(!testPoint.passed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
        }
        // store result
        param.result.listResult.push_back(testPoint);

        if((!m_sensorConfig.keepTestIfFaled) && (!testPoint.passed)) {
            break;
        }

        control->SigGen_SetRFSignalOut(false, genConfig.siggenDelay);
        iter++;
    }

    control->SigGen_DeSetCombo(200);
}


/**
 * @brief TestSensor::DoTestBw25kL
 *
 * Bài đo băng thông tín hiệu có băng thông nhỏ hơn 25kHz
Bước 1. Cấu hình khối xử lý trung tâm
Cấu hình tần số thu của VER – SI3 từ 20 MHz đến 60 MHz
Lựa chọn chiều dài thời gian thu 5s đến 10s cho cửa sổ waterfall (cấu hình trong cửa sổ Search)
Bước 2. Thiết lập máy phát tín hiệu cao tần
Đưa máy về trạng thái ban đầu : Ấn Preset;
Lựa chọn điều chế FM với băng thông 12.5 kHz (Tần số baseband 1 kHz, độ di tần 5,6 kHz);
Điều chỉnh mức công suất đầu ra máy phát cao tần mức -60 dBm
Chọn chế độ ALC off;
Bật chế độ điều chế:
 Mod on/off (đèn tín hiệu trên máy sáng xanh)
Thiết lập tần số cao tần trên máy phát tín hiệu cao tần là 25,025 MHz tương ứng với kênh cần kiểm tra;
 Ấn FREQ  Chọn tần số tương ứng;
Thiết lập mức cao tần phát ra. -60 dBm;
 Ấn AMPTD  -60 dBm;
Tắt đường cao tần ( RF on/off).
Bước 3. Bắt đầu thực hiện đo
 Thực hiện phát tín hiệu cao tần từ máy phát tín hiệu vào thiết bị cần kiểm tra.
 Bật RF on/off (đèn tín hiệu báo bật);
Nhìn trên màn hình phân tích phổ thác nước waterfall đã xuất hiện vạch phổ của tín hiệu từ máy phát cao tần phát vào.
Bước 4. Tìm giá trị băng thông
Di chuyển chuột đến vị trí vạch phổ vừa xuất hiện.
Nhìn trên ô hiển thị tham số tín hiệu giá trị băng thông đo được.
Ghi lại kết quả đo được vào phụ lục 1.
Bước 5. Thực hiện đo băng thông tại các tần số còn lại theo quy định
Thực hiện tương tự để đo băng thông của máy ở các tần số theo yêu cầu, đọc và ghi kết quả đo được vào phiếu kiểm tra theo theo phụ lục tương ứng.
 *
 */
void TestSensor::DoTestBw25kL(ComParam &param, TestProgress progress)
{
    (void)progress;
    if(param.input.freqTestList.size() == 0)
        return;

    double currentMiss;
    std::vector<double>::iterator iter  = param.input.freqTestList.begin();
    control->SigGen_SetFMARB(100E3, *iter, Freq_Mhz,
                             genConfig.loadFileLowName,
                             -60, Power_dBm, genConfig.siggenDelay);
    currentMiss = *iter + 40;    
    control->Server_SetGain(0, param.input.gain);
    control->Server_SetNoiseFloor(0, param.input.noisefloor);

    emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");

    if(!changeMiss) {
        control->Server_SetRecvFreq(*iter, BW_40_MHZ, 0);
        uint32_t count = genConfig.serverDelay / 100;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }while(IsKeepgoingOnTest() && (count--));
    }

    if(GetTestState() == TestState_Pause) {
        emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
        PauseTest();
        control->SigGen_InitDevice();
    }

    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {
        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
            control->SigGen_InitDevice();
        }
        double freq = *iter;

        emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");
        emit updateStatusBar("Đang kiểm tra sai số đo băng thông < 25Khz tại: " +
                             QString::number(freq, 'g', 10) + " Mhz ...");        

        control->SigGen_SetRFFreq(freq, Freq_Mhz, genConfig.siggenDelay);
        control->Server_SetSigCalc(1, 0, 20, 100);

        control->currFreqExp = freq * 1E6;

        control->SigGen_SetRFFreq(freq, Freq_Mhz, genConfig.siggenDelay);
        control->SigGen_SetRFSignalOut(true, genConfig.siggenDelay);

        if(changeMiss) {
            control->Server_SetRecvFreq(freq, BW_40_MHZ, 0);
        } else {
            if(freq >= currentMiss) {
                currentMiss = freq + 40.0;      
                control->Server_SetRecvFreq(currentMiss - 20.0, BW_40_MHZ, 0);
            }
        }

        uint32_t bw  = 0;
        uint32_t count = genConfig.serverDelay / 100;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            bw = control->Server_CheckBandwidth(freq * 1E6, param.input.ferr);
        }while(IsKeepgoingOnTest() && (count--) && (bw == 0));


        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;

        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }

        if(SENSOR_RESET_VAL == true) { // For test
            static bool log = false;
            log = !log;
            if(log)
                bw = genConfig.bandwidthLow;
            else
                bw = genConfig.bandwidthLow * 2;
        }

        if(bw) {            
            param.result.currValue = int32_t(bw - genConfig.bandwidthLow);
            testPoint.value = param.result.currValue;
            // Check pass fail
            if(param.result.currValue >= param.input.min &&
                    param.result.currValue <= param.input.max) {
                testPoint.passed = true;
                displayAndWriteResultRow(testPoint, true, bw);
            }else {
                testPoint.passed = false;
                displayAndWriteResultRow(testPoint, false, bw);

            }

            // Show value is readed
            displayValueOfFreq(param.result.currValue);


        } else {
            displayAndWriteResultRow(testPoint, QString("N/A"));
            displayValueOfFreq("N/A");

            emit updateStatusBar("Không nhận được kết quả sai số băng thông 25K+ tại: " +
                                 QString::number(freq, 'g', 10) + " Mhz ...", QColor(Qt::red));
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        if(!testPoint.passed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
        }


        // store result
        param.result.listResult.push_back(testPoint);

        if((!m_sensorConfig.keepTestIfFaled) && (!testPoint.passed)) {
            break;
        }
        control->SigGen_SetRFSignalOut(false, genConfig.siggenDelay);
        iter++;
    }

    control->SigGen_DeSetCombo(200);
}

/**
 * @brief TestSensor::DoTestErrorFreq
 *
 *Bước 1. Cấu hình khối xử lý trung tâm
Cấu hình tần số thu của VER – SI3 từ 20 MHz đến 60 MHz
Lựa chọn chiều dài thời gian thu 5s đến 10s cho cửa sổ waterfall (cấu hình trong cửa sổ Search)
Bước 2. Thiết lập máy phát tín hiệu cao tần
Đưa máy về trạng thái ban đầu : Ấn Preset;
Lựa chọn chế độ phát tín hiệu không điều chế (tín hiệu sine );
Điều chỉnh mức công suất đầu ra máy phát cao tần mức -60 dBm
Chọn chế độ ALC off;
Bật chế độ điều chế:
 Mod on/off (đèn tín hiệu trên máy sáng xanh)
Thiết lập tần số cao tần trên máy phát tín hiệu cao tần là 25,025 MHz tương ứng với kênh cần kiểm tra;
 Ấn FREQ  Chọn tần số tương ứng;
Thiết lập mức cao tần phát ra. -60 dBm;
 Ấn AMPTD  -60 dBm;
Tắt đường cao tần ( RF on/off).
Bước 3. Bắt đầu thực hiện đo
 Thực hiện phát tín hiệu cao tần từ máy phát tín hiệu vào thiết bị cần kiểm tra.
 Bật RF on/off (đèn tín hiệu báo bật);
Nhìn trên màn hình phân tích phổ thác nước waterfall đã xuất hiện vạch phổ của tín hiệu từ máy phát cao tần phát vào.
Bước 4. Tìm giá tần số đo được
Di chuyển chuột đến vị trí vạch phổ vừa xuất hiện.
Nhìn trên ô hien thị tham so tín hiệu giá trị tần số đo được.
Ghi lại kết quả đo được vào phụ lục 1.
Bước 5. Thực hiện đo tần số tại các điểm còn lại theo quy định
Thực hiện tương tự để đo tần số của máy ở các tần số theo yêu cầu,
đọc và ghi kết quả đo được vào phiếu kiểm tra theo theo phụ lục tương ứng.
 */
void TestSensor::DoTestErrorFreq(ComParam &param, TestProgress progress)
{
    (void)progress;
    if(param.input.freqTestList.size() == 0)
        return;

    double currentMiss;

    std::vector<double>::iterator iter  = param.input.freqTestList.begin();
    control->SigGen_SetCombo(*iter, Freq_Mhz,
                            -60, Power_dBm,
                            1.0, Freq_Khz,
                            genConfig.siggenDelay);

    control->Server_SetGain(0, param.input.gain);
    control->Server_SetNoiseFloor(0, param.input.noisefloor);

    currentMiss = *iter + 40;
    if(!changeMiss) {
        control->Server_SetRecvFreq(*iter, BW_40_MHZ, 0);
        uint32_t count = genConfig.serverDelay / 100;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }while(IsKeepgoingOnTest() && (count--));
    }

    if(GetTestState() == TestState_Pause) {
        emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
        PauseTest();
        control->SigGen_InitDevice();
    }

    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {
        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
            control->SigGen_InitDevice();
        }
        double freq = *iter;
        emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");
        emit updateStatusBar("Đang kiểm tra sai số đo tần số tại: " + QString::number(freq, 'g', 10) + " Mhz ...");
        control->SigGen_SetRFFreq(freq, Freq_Mhz, genConfig.siggenDelay);
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


        uint64_t currFreq  = 0;
        uint32_t count = genConfig.serverDelay / 100;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            currFreq = control->Server_GetReceivedFrequency(freq * 1E6, param.input.ferr);
        }while(IsKeepgoingOnTest() && (count--) && (currFreq == 0));

        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;

        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }

        if(SENSOR_RESET_VAL == true) { // For test            
            static bool log = false;
            log = !log;
            if(log)
                currFreq = (freq * 1E6) - 133;
            else
                currFreq = (freq * 1E6) - 1333;

        }

        if(currFreq) {            
            // Lấy độ lệch tần số tín hiệu phát so với tín hiệu thu được
            param.result.currValue = std::llabs(currFreq - uint64_t(freq * 1E6));
            LREP("Curr Freq: {}, Freq Error: {}\n",currFreq, param.result.currValue);
            testPoint.value = param.result.currValue;
            // Check pass fail
            if(param.result.currValue >= param.input.min&&
                    param.result.currValue <= param.input.max) {
                testPoint.passed = true;
                displayAndWriteResultRow(testPoint, true, currFreq);
            }else {
                testPoint.passed = false;
                displayAndWriteResultRow(testPoint, false);
            }

            // Show value is readed
            displayValueOfFreq(param.result.currValue);


        } else {
            displayAndWriteResultRow(testPoint, QString("N/A"));
            displayValueOfFreq("N/A");        
            emit updateStatusBar("Không nhận được kết quả sai số đo tần số tại: " +
                                 QString::number(freq, 'g', 10) + " Mhz !!!", QColor(Qt::red));
        }

        if(!testPoint.passed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
        }

        // store result
        param.result.listResult.push_back(testPoint);
        if((!m_sensorConfig.keepTestIfFaled) && (!testPoint.passed)) {
            break;
        }

        control->SigGen_SetRFSignalOut(false, genConfig.siggenDelay);
        iter++;
    }

    control->SigGen_DeSetCombo(200);
}



/**
 * @brief TestSensor::DoTestThirdInt
 *
Bước 1. Cấu hình khối xử lý trung tâm
    Cấu hình tần số trung tâm : 1485 MHz
    Lựa chọn Span trên giao diện phân tích phổ: 40MHz
Bước 2. Thiết lập máy phát tín hiệu cao tần
    Đưa máy về trạng thái ban đầu : Ấn Preset;
    Lựa chọn chế độ phát multiple tone;
    Điều chỉnh mức công suất đầu ra máy phát cao tần mức -150 dBm
    Chọn chế độ ALC off;
    Tắt chế độ điều chế:
    Mod on/off (đèn tín hiệu trên máy tắt)
    Thiết lập tần số cao tần trên máy phát tín hiệu cao tần số 1 là 1484 MHz tương ứng với kênh cần kiểm tra;
    Ấn FREQ  Chọn tần số tương ứng;
    Thiết lập mức cao tần phát ra. -30 dBm;
    Ấn AMPTD  -150 dBm;
    Tắt đường cao tần ( RF on/off).
    Tương tự thiết lập tần số cao tần trên máy phát tín hiệu cao tần số 1 là 1486 MHz tương ứng với kênh cần kiểm tra, công suất cao tần ra là -30 dBm.
Bước 3. Bắt đầu thực hiện đo
+ Thực hiện phát tín hiệu cao tần từ cả 2 máy phát tín hiệu vào thiết bị cần kiểm tra.
    Bật RF on/off (đèn tín hiệu báo bật);
+ Khi đó trên màn hình cửa sổ thác nước sẽ xuất hiện ít nhất 4 tín hiệu có tần số 1486 MHz;
1484 MHz; 1482 MHz; và 1488 MHz, trong đó công suất của tín hiệu 1486MHz xấp xỉ bằng công suất tín hiệu 1484 MHz (ký hiệu là P1 dBm);
công suất tín hiệu 1482MHz xấp xỉ bằng công suất tín hiệu 1488MHz (ký hiệu là P2 dBm).
Bước 4. Tìm giá trị IP3
+ Tính toán mức input IP3:  3/2*P1 – 1/2 * P2

 */
void TestSensor::DoTestThirdInt(ComParam &param, TestProgress progress)
{
    (void)progress;
    double freqSpace = 2.0; // Mhz
    double currentPwr = -30;

    if(param.input.freqTestList.size() == 0)
        return;

    std::vector<double>::iterator iter  = param.input.freqTestList.begin();

    control->Server_SetGain(0, param.input.gain);
    control->Server_SetNoiseFloor(0, param.input.noisefloor);
    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {
        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
            control->SigGen_InitDevice();
        }

        double freq = *iter;
        control->SigGen_SetTwoTone(freq, Freq_Mhz, freqSpace, Freq_Mhz, currentPwr, Power_dBm, genConfig.siggenDelay);
        control->Server_SetRecvFreq(freq, BW_40_MHZ, 0);

        uint64_t mainFreq1 = freq * 1E6 - (freqSpace / 2 * 1E6);
        uint64_t mainFreq2 = freq * 1E6 + (freqSpace / 2 * 1E6);
        uint64_t lowFreq = mainFreq1 - (freqSpace  * 1E6);
        uint64_t highFreq = mainFreq2 + (freqSpace  * 1E6);

        control->currFreqExp = mainFreq1;
        control->currFreqExp2 = mainFreq2;
        control->currFreqExp3 = lowFreq;
        control->currFreqExp4 = highFreq;

        double checkMain1;
        double checkMain2;
        double checkImg1;
        double checkImg2;


        uint32_t count = genConfig.serverDelay / 100;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }while(IsKeepgoingOnTest() && count--);

        count = 15;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            checkMain1 = control->Server_CheckHasSignalPower(mainFreq1, param.input.ferr);
            checkMain2 = control->Server_CheckHasSignalPower(mainFreq2, param.input.ferr);
            checkImg1 = control->Server_CheckHasSignalPower(lowFreq, param.input.ferr);
            checkImg2 = control->Server_CheckHasSignalPower(highFreq, param.input.ferr);
            currentPwr +=1;
            control->SigGen_SetRFPower(currentPwr, Power_dBm, genConfig.siggenDelay);
            emit updateStatusBar("Đang kiểm tra tần: " +
                                 QString::number(freq, 'g', 10) + " Mhz. Công suất máy phát " +
                                 QString::number(currentPwr) + " dBm");            
        }while(IsKeepgoingOnTest() && (count--) && (checkMain1 == 0 || checkMain2 == 0 || checkImg1 == 0 || checkImg2 == 0));


        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;

        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }

        LREP("CHECK 1: {} CHECK 2: {} CHECK 3: {} CHECK 4: {}\n", checkMain1, checkMain2, checkImg1, checkImg2);
        if(checkMain1 != 0 && checkMain2 != 0 && checkImg1 != 0 && checkImg2 != 0) {
            testPoint.value  = ((3 * checkMain1) / 2.0) - (checkImg1 /2.0);
            LREP("__________THIRD {}__________\n", testPoint.value);
            param.result.currValue = testPoint.value;
            // Check pass fail
            if(param.result.currValue >= param.input.min &&
                    param.result.currValue <= param.input.max) {
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

            emit updateStatusBar("Không nhận được kết quả méo hài bậc ba tại: " +
                                 QString::number(freq, 'g', 10) + " Mhz !!!", QColor(Qt::red));            
        }

        if(!testPoint.passed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
        }

        param.result.listResult.push_back(testPoint);
        if((!m_sensorConfig.keepTestIfFaled) && (!testPoint.passed))
            break;

        iter++;
    }

    control->SigGen_DeSetCombo(200);
}



void TestSensor::InitAllTestName()
{
    m_listTestName.push_back(SENSOR_STR_TEST_CURRENT);
    m_listTestName.push_back(SENSOR_STR_TEST_SENSITIVE);
    m_listTestName.push_back(SENSOR_STR_TEST_ERR_PWR);
    m_listTestName.push_back(SENSOR_STR_TEST_ERR_BW_25KH);
    m_listTestName.push_back(SENSOR_STR_TEST_ERR_BW_25KL);
    m_listTestName.push_back(SENSOR_STR_TEST_ERR_FREQ);
    m_listTestName.push_back(SENSOR_STR_TEST_THIRD_INTP);
}

void TestSensor::GetResultFromPower()
{
//    emit updateStatusBar("LẤY KẾT QUẢ TỪ BỘ NGUỒN ");
//    std::this_thread::sleep_for(std::chrono::milliseconds(genConfig.siggenDelay));
}


/**
 * @brief TestSensor::DoTestSuiteFunction
 */
void TestSensor::DoTestSuiteFunction()
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

                if(test.second.name == SENSOR_STR_TEST_CURRENT) {
                    LREP("__________ TEST CURRENT _________\n");                                        
                    DoTestCurrent(test.second, GetTestProgress());
                } else if(test.second.name == SENSOR_STR_TEST_SENSITIVE) {
                    LREP("__________ TEST SENSITIVE _________\n");                    
                    DoTestSensitive(test.second, GetTestProgress());
                } else if(test.second.name == SENSOR_STR_TEST_ERR_PWR) {
                    LREP("__________ TEST ERROR PWR _________\n");                    
                    DoTestErrorPower(test.second, GetTestProgress());
                } else if(test.second.name == SENSOR_STR_TEST_ERR_BW_25KH) {
                    LREP("__________ TEST ERROR BW 25K + _________\n");
                    DoTestBw25kH(test.second, GetTestProgress());
                } else if(test.second.name == SENSOR_STR_TEST_ERR_BW_25KL) {
                    LREP("__________ TEST ERROR BW 25K - _________\n");
                    DoTestBw25kL(test.second, GetTestProgress());
                } else if(test.second.name == SENSOR_STR_TEST_ERR_FREQ) {
                    LREP("__________ TEST ERROR FREQ MEAS _________\n");
                    DoTestErrorFreq(test.second, GetTestProgress());
                } else if(test.second.name == SENSOR_STR_TEST_THIRD_INTP) {
                    LREP("__________ TEST THIRD INT _________\n");
                    DoTestThirdInt(test.second, GetTestProgress());
                }

                test.second.result.curPassed =
                        CheckTestCaseResult(test.second.result.listResult);
                currLineIdx++;

            }

            if(GetTestState() == TestState_Running) {
                if(checkTotalPassed()) {
                    SetPassed();
                } else {
                    if(m_sensorConfig.reTestIfFailed) {
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


void TestSensor::StopAllTest(bool save)
{
    StopTestSuite(save);
    labelTestPassNum->setText(QString::number(testTracker.testPass));
    labelTestRunNum->setText(QString::number(testTracker.testRun));
    EnableSettingPanel(true);
}


void TestSensor::StartAllTest(const QString &serial, const QString &who, bool createResult)
{    
    if(modeLoaded == "_THUONG") {
        StartTestSuite(TEMPLATE_SENSOR_THUONG, serial, who);
    } else {
        StartTestSuite(TEMPLATE_SENSOR_THUNGHIEM, serial, who);
    }

    if(createResult) {        
        currLineResult = 20;
        for(auto &test : testHead){
            resFile->write("B" + QString::number(currLineResult), test.second.name.c_str());
            if(test.second.name == SENSOR_STR_TEST_CURRENT) {                
                resFile->write("E" + QString::number(currLineResult), "≤ " + QString::number(test.second.input.max) + " A");
            } else if(test.second.name == SENSOR_STR_TEST_SENSITIVE) {
                resFile->write("E" + QString::number(currLineResult), "≤ " + QString::number(test.second.input.max) + " dBm" );
            } else if(test.second.name == SENSOR_STR_TEST_ERR_PWR) {
                resFile->write("E" + QString::number(currLineResult), "± " + QString::number(test.second.input.max) + " dBm");
            } else if(test.second.name == SENSOR_STR_TEST_ERR_BW_25KH) {
                resFile->write("E" + QString::number(currLineResult), "± " + QString::number(test.second.input.max) + " %");
            } else if(test.second.name == SENSOR_STR_TEST_ERR_BW_25KL) {
                resFile->write("E" + QString::number(currLineResult), "± " + QString::number(test.second.input.max) + " Hz");
            } else if(test.second.name == SENSOR_STR_TEST_ERR_FREQ) {
                resFile->write("E" + QString::number(currLineResult), "≤ " + QString::number(test.second.input.max) + " Hz");
            } else if(test.second.name == SENSOR_STR_TEST_THIRD_INTP) {
                resFile->write("E" + QString::number(currLineResult), "≥ " + QString::number(test.second.input.max) + " dBm");
            }
            CreateResultLine(test.second);
        }
    }

    SetTestState(TestState_Running);

    EnableSettingPanel(false);
    btnStartTest->setText("DỪNG");
}


void TestSensor::on_updateUserSetting()
{
    GetUserConfig();
    SaveSensorConfig();
    isSaveCfg = true;
}


void TestSensor::on_btnTestClicked()
{
    editTest->clear();
}



void TestSensor::on_btnStartTestClicked()
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

//        if(control->SigGen_GetStatus() != communication::Event_Connected) {
//            QMessageBox::warning(this, "Lỗi", "Chưa kết nối máy signal generator !");
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


void TestSensor::on_btnConnectServerClicked()
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

void TestSensor::on_btnConnectSignalGenClicked()
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

void TestSensor::on_btnSetNoiseFloorClicked()
{
    floorValue = editFloor->text().toUInt();
    control->Server_SetNoiseFloor(0, floorValue);
}

void TestSensor::on_btnTestTypeClicked()
{
    if(comTestType->currentIndex() == 0) {
        LREP("CHANGE MISS OFF\n");
        changeMiss = false;
    } else {
        LREP("CHANGE MISS ON\n");
        changeMiss = true;
    }
}

void TestSensor::on_btnPauseClicked()
{
    TestState state = GetTestState();
    switch(state) {
    case TestState_Running:
        btnStartTest->setEnabled(false);
        SetTestState(TestState_Pause);
        btnPause->setText("TIẾP TỤC");
        break;
    case TestState_Pause:
        btnStartTest->setEnabled(true);
        SetTestState(TestState_Running);
        btnPause->setText("TẠM DỪNG");
        break;
    case TestState_RequestStop:
        break;
    case TestState_Stop:
        break;

    default:
        break;
    }
}

void TestSensor::on_SslClientConnectEvent(int evt)
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




void TestSensor::on_SiggenConnectEvent(int evt)
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

void TestSensor::on_DataReceived(quint64 data)
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


#include "testsensor.h"
#include <iostream>
using namespace cppframework;


void TestSensor::loadTestParam(const CSVFile::CsvVector &data)
{
    int order;

    if(!data.size())
      return;
    m_rows.clear();


    LREP("Clear all test param before load the new !");
    clearAllParam();
    CSVFile::CsvVector::const_iterator iter;
    for(iter = data.begin(); iter != data.end(); ++iter){
    std::vector<std::string> row = *iter;
        if(SearchTestName(row.at(1)) && (row.size() >= 15)) {
            ComParam head;
            head.name = row.at(1);
            QString cont;
            head.enable = (row.at(2) == "TRUE" || row.at(2) == "true") ? true : false;
//            head.input.min = str::Util::convert<double>(row.at(5), 0);
//            head.input.max = str::Util::convert<double>(row.at(6), 0);

            if(head.enable) { // && (std::abs(head.input.max) > std::abs(head.input.min))) {
                order = cppframework::str::Util::convert<int>(row.at(3), 1);
                head.input.min = str::Util::convert<double>(row.at(5), 0);
                head.input.max = str::Util::convert<double>(row.at(6), 0);
                head.input.ferr = str::Util::convert<int64_t>(row.at(11), 0);
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

    PrintTestParamAll();
}


/**
 * @brief TestSensor::on_btnSettingClicked
 */
void TestSensor::on_btnSettingClicked()
{
    bool ok;

    QString text = QInputDialog::getText(this, "Admin access",
                                             "Issue password:", QLineEdit::Password,
                                             "", &ok);
    if (ok && !text.isEmpty()) {
        if(text == "1") {
            std::string          externalFile = genConfig.inputDir;
            if(comboTestMode->currentText() == "ĐIỀU KIỆN THƯỜNG") {
                externalFile += ("/sensor/sensor_thuong.csv");
            } else if(comboTestMode->currentText() == "NÓNG") {
                externalFile += ("/sensor/sensor_nong.csv");
            }else if(comboTestMode->currentText() == "LẠNH") {
                externalFile += ("/sensor/sensor_lanh.csv");
            }else if(comboTestMode->currentText() == "MÔI TRƯỜNG") {
                externalFile += ("/sensor/sensor_moitruong.csv");
            }else if(comboTestMode->currentText() == "LÃO HÓA") {
                externalFile += ("/sensor/sensor_laohoa.csv");
            }else if(comboTestMode->currentText() == "RUNG SÓC VA ĐẬP") {
                externalFile += ("/sensor/sensor_rungsocvadap.csv");
            }
            bool ret = QDesktopServices::openUrl(QUrl::fromLocalFile(QString(externalFile.c_str())));
            if(!ret) {
                QMessageBox::warning(this, "Open error", "File: \"" + QString(externalFile.c_str()) + "\" not found !");
            }
        }
        else {
            QMessageBox::warning(this, "WRONG PASSWORD", "The password is incorrect !");
        }
    }
}

/*
 *
 *
 *
*/
void TestSensor::on_btnLoadTestParamClicked()
{
//    disconnect(btnLoadTestParam, SIGNAL(clicked(bool)), this, SLOT(on_btnLoadTestParamClicked()));
    LoadTestConfigFromFile();
//    connect(btnLoadTestParam, SIGNAL(clicked(bool)), this, SLOT(on_btnLoadTestParamClicked()));
    isTestParmLoaded = true;
}

/*
 *
 *
 *
*/
void TestSensor::LoadTestConfigFromFile()
{
    modeLoaded = "";
    std::string          externalFile = genConfig.inputDir;
    if(comboTestMode->currentText() == "ĐIỀU KIỆN THƯỜNG") {
        externalFile += ("/sensor/sensor_thuong.csv");
        labelHeader->setText("ĐO KIỂM TỰ ĐỘNG CHỈ TIÊU SENSOR - THƯỜNG");
        modeLoaded = "_THUONG";
    } else if(comboTestMode->currentText() == "NÓNG") {
        externalFile += ("/sensor/sensor_nong.csv");
        labelHeader->setText("ĐO KIỂM TỰ ĐỘNG CHỈ TIÊU SENSOR - NÓNG");
        modeLoaded = "_NONG";
    }else if(comboTestMode->currentText() == "LẠNH") {
        externalFile += ("/sensor/sensor_lanh.csv");
        labelHeader->setText("ĐO KIỂM TỰ ĐỘNG CHỈ TIÊU SENSOR - LẠNH");
        modeLoaded = "_LANH";
    }else if(comboTestMode->currentText() == "MÔI TRƯỜNG") {
        externalFile += ("/sensor/sensor_moitruong.csv");
        labelHeader->setText("ĐO KIỂM TỰ ĐỘNG CHỈ TIÊU SENSOR - MÔI TRƯỜNG");
        modeLoaded = "_MOITRUONG";
    }else if(comboTestMode->currentText() == "LÃO HÓA") {
        externalFile += ("/sensor/sensor_laohoa.csv");
        labelHeader->setText("ĐO KIỂM TỰ ĐỘNG CHỈ TIÊU SENSOR - LÃO HÓA");
        modeLoaded = "_LAOHOA";
    }else if(comboTestMode->currentText() == "RUNG SÓC VA ĐẬP") {
        externalFile += ("/sensor/sensor_rungsocvadap.csv");
        labelHeader->setText("ĐO KIỂM TỰ ĐỘNG CHỈ TIÊU SENSOR - RUNG SÓC VA ĐẬP");
        modeLoaded = "_RUNGSOCVADAP";
    }

    if(loadTestConfig(externalFile)) {
        loadTestParam(loader->rows());
        loadTestParamToUi();
    } else {

    }
    loader.reset();
}


void TestSensor::ConfigController()
{

    SensorConfig senCfg = UiConfig::getInstance()->getSensorConfig();
    GeneralConfig genCfg = UiConfig::getInstance()->getGeneralConfig();
    if(control) {
        control->ConfigSslClient(senCfg.ServerIp,senCfg.sslPort);
        control->ConfigUdp(senCfg.ServerIp, senCfg.udpPort);
        control->ConfigSigGen(senCfg.SigGenIp,senCfg.siggenPort);
        if(genCfg.localIp != "") {
            //LREP("Setup this machine ip: {}\n", genConfig.localIp);
            control->SetLocalIp(genCfg.localIp);
        } else {
            LREP_WARN("Setup this machine ip: DEFAULT_LOCAL_IP\n");
            control->SetLocalIp(DEFAULT_LOCAL_IP);
        }
        control->SetSigenType((SigGenType)genCfg.sigGenType);
        control->SetSpectType((SpectrumType)genCfg.spectType);
        control->SetPowerType((PowerType)genCfg.powerType);
    }
}

void TestSensor::EnableSettingPanel(bool en)
{
    btnConnectInstr->setEnabled(en);
    btnConnectServer->setEnabled(en);
    btnLoadTestParam->setEnabled(en);
    btnTestCaseSetting->setEnabled(en);
    editSerial->setEnabled(en);
    checkKeepTest->setEnabled(en);
    checkRetestIfFailed->setEnabled(en);
}

void TestSensor::PrintGeneralConfig()
{
    LREP("keep test: {}\n", m_sensorConfig.keepTestIfFaled);
    LREP("auto open result: {}\n", m_sensorConfig.reTestIfFailed);
    LREP("server ip: {}\n", m_sensorConfig.ServerIp);
    LREP("server port: {}\n", m_sensorConfig.sslPort);
    LREP("server udp port: {}\n", m_sensorConfig.udpPort);
    LREP("instr ip: {}\n", m_sensorConfig.SigGenIp);
    LREP("instr port: {}\n", m_sensorConfig.siggenPort);
}

void TestSensor::LoadSensorConfig()
{
    m_sensorConfig = UiConfig::getInstance()->getSensorConfig();
}

void TestSensor::SaveSensorConfig()
{
    UiConfig::getInstance()->saveSensorKeepTestIfFailed(m_sensorConfig.keepTestIfFaled);
    UiConfig::getInstance()->saveSensorReTestIfFailed(m_sensorConfig.reTestIfFailed);
    UiConfig::getInstance()->saveSensorSigGenIp(m_sensorConfig.SigGenIp);
    UiConfig::getInstance()->saveSensorSigGenPort(m_sensorConfig.siggenPort);
    UiConfig::getInstance()->saveSensorServerAddress(m_sensorConfig.ServerIp);
    UiConfig::getInstance()->saveSensorServerSslPort(m_sensorConfig.sslPort);
    UiConfig::getInstance()->saveSensorServerUdpPort(m_sensorConfig.udpPort);
}


void TestSensor::GetUserConfig()
{
    m_sensorConfig.keepTestIfFaled = checkKeepTest->isChecked();
    m_sensorConfig.reTestIfFailed = checkRetestIfFailed->isChecked();
    m_sensorConfig.SigGenIp = editInstrIp->text().toStdString();
    m_sensorConfig.siggenPort = editInstrPort->text().toUShort();
    m_sensorConfig.ServerIp = editServerIp->text().toStdString();
    m_sensorConfig.sslPort = editServerPort->text().toUShort();
    m_sensorConfig.udpPort = editServerUdpPort->text().toUShort();
}


void TestSensor::PrintTestParamAll()
{

}
