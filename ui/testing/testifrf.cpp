#include "testifrf.h"
#include <iostream>
#include <protocol/client_msg/msg.pb.h>
#include <isc/utils.h>

using namespace cppframework;
/**
 * @brief TestIfrf::TestIfrf create all ui element,
 *                  load configuration and create connection
 * @param parent
 */
TestIfrf::TestIfrf(Controller *controller, TestBase *parent) :
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
 * @brief TestIfrf::~TestIfrf
 */
TestIfrf::~TestIfrf()
{        
}

void TestIfrf::initVariable()
{
    /**
     * Delay must large enough prevent TCP appends two frames into one package
     */
    testTrackerFile = CONFIG_TEST_TRACK_IFRF;
    outputFileName = FILENAME_RES_IFRF;
    LoadGenConfig();    
    LoadIfrfConfig();
    LoadTestTracker();
    InitAllTestName();
    isSaveCfg = false;
    m_waitCode = 0;
    currFreq = 140000000;
}

void TestIfrf::createUiElem()
{
    groupConfig = new QGroupBox(tr("CÀI ĐẶT"));
    comboTestMode   = new QComboBox;
    labelTestMode = new QLabel("CHỌN CHẾ ĐỘ");

    labelInstrIp = new QLabel("ĐỊA CHỈ SIGNAL GEN");
    editInstrIp = new QLineEdit;
    editSpectIp = new QLineEdit;
    btnConnectInstr = new QPushButton("KẾT NỐI");
    btnConnectSpect = new QPushButton("KẾT NỐI");

    tableView = new QTableView(this);
    mainLayout = new QVBoxLayout;
    settingLayout = new QFormLayout;
    hLayout = new QHBoxLayout;

    labelHeader = new QLabel("ĐO KIỂM TỰ ĐỘNG CHỈ TIÊU MẠCH IFRF");
    btnTestCaseSetting =  new QPushButton("CẤU HÌNH BÀI ĐO");
    btnLoadTestParam = new QPushButton("NẠP THAM SỐ ĐO");

    btnStartTest = new QPushButton("BẮT ĐẦU");
    checkKeepTest = new QCheckBox;
    labelCheckKeep = new QLabel("TIẾP TỤC NẾU FAIL");

    labelSerial = new QLabel("SERIAL");
    editSerial = new QLineEdit;

    labelOpenWhenDone = new QLabel("CHẠY LẠI NẾU FAIL");
    checkRetestIfFailed = new QCheckBox;

    labelWhoTest = new QLabel("NGƯỜI TEST");
    editWhoTest = new QLineEdit;

    manLayout = new QFormLayout;
    mainSettingLayout = new QVBoxLayout;

    groupSetting = new QGroupBox("CÀI ĐẶT");
    groupMan = new QGroupBox("THAO TÁC");

    editInstrPort = new QLineEdit;
    editSpectPort  = new QLineEdit;

    labelSpectStatus = new QLabel("KHÔNG KẾT NỐI");
    labelInstrStatus = new QLabel("KHÔNG KẾT NỐI");

    labelTestRunNum = new QLabel(" ");
    labelTestPassNum = new QLabel(" ");

    comboSerialList = new QComboBox;    

    btnConnectSerial = new QPushButton("KẾT NỐI COM");
    btnPause  = new QPushButton("TẠM DỪNG");

    btnSendCommand = new QPushButton("SET FREQ");
    btnTestSpect = new QPushButton("SEND SPECT");
    editSendCommand = new QLineEdit;
    editRecvCommand = new QLineEdit;
}

void TestIfrf::createLayout()
{

    settingLayout->addRow(labelTestMode, comboTestMode);
    settingLayout->addWidget(btnLoadTestParam);
    settingLayout->addWidget(btnTestCaseSetting);
    settingLayout->addItem(new QSpacerItem(0, 10));

    settingLayout->addRow("CỔNG COM", comboSerialList);    
    settingLayout->addWidget(btnConnectSerial);
    settingLayout->addItem(new QSpacerItem(0, 10));

    settingLayout->addRow(labelInstrIp, editInstrIp);
    settingLayout->addRow("CỔNG TCP", editInstrPort);
    settingLayout->addRow("TRẠNG THÁI", labelInstrStatus);
    labelInstrStatus->setStyleSheet("QLabel {color : red; }");
    settingLayout->addRow("SIGNAL GENERATOR", btnConnectInstr);
    settingLayout->addItem(new QSpacerItem(0, 10));

    settingLayout->addRow("ĐỊA CHỈ SPECTRUM", editSpectIp);
    settingLayout->addRow("CỔNG TCP", editSpectPort);
    settingLayout->addRow("TRẠNG THÁI", labelSpectStatus);
    labelSpectStatus->setStyleSheet("QLabel {color : red; }");
    settingLayout->addRow("SPECTRUM", btnConnectSpect);
    settingLayout->addItem(new QSpacerItem(0, 10));

    settingLayout->addRow(labelCheckKeep, checkKeepTest);
    settingLayout->addRow("CHẠY LẠI NẾU FAIL", checkRetestIfFailed);
    manLayout->addRow("SỐ LƯỢNG TEST", labelTestRunNum);
    manLayout->addRow("SỐ LƯỢNG PASS", labelTestPassNum);
    manLayout->addRow(labelWhoTest, editWhoTest);
    manLayout->addRow(labelSerial, editSerial);
    manLayout->addWidget(btnStartTest);
    manLayout->addWidget(btnPause);

    settingLayout->setHorizontalSpacing(1);
    btnStartTest->setFixedHeight(40);


    manLayout->addRow(editSendCommand, btnSendCommand);
    manLayout->addRow(editRecvCommand);
    manLayout->addWidget(btnTestSpect);

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

void TestIfrf::createElemContent()
{
    createTableViewHeader();
    comboTestMode->addItem(tr("ĐIỀU KIỆN THƯỜNG"));
    comboTestMode->addItem(tr("NÓNG"));
    comboTestMode->addItem(tr("LẠNH"));

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QString s = info.portName();
        comboSerialList->addItem(s);
    }
    int i;

    comboTestMode->setMinimumHeight(25);
    comboTestMode->setEditable(true);
    comboTestMode->lineEdit()->setReadOnly(true);
    comboTestMode->lineEdit()->setAlignment(Qt::AlignCenter);

    for(i = 0; i < comboTestMode->count(); i++) {
        comboTestMode->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    comboSerialList->setEditable(true);
    comboSerialList->lineEdit()->setReadOnly(true);
    comboSerialList->lineEdit()->setAlignment(Qt::AlignCenter);
    for(i = 0; i < comboSerialList->count(); i++) {
        comboSerialList->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }
    comboSerialList->setCurrentIndex(comboSerialList->count() - 1);

    editInstrIp->setAlignment(Qt::AlignCenter);
    editInstrPort->setAlignment(Qt::AlignCenter);
    editInstrPort->setFixedWidth(50);
    labelInstrStatus->setAlignment(Qt::AlignCenter);

    editSpectIp->setAlignment(Qt::AlignCenter);
    editSpectPort->setAlignment(Qt::AlignCenter);
    editSpectPort->setFixedWidth(50);
    labelSpectStatus->setAlignment(Qt::AlignCenter);

    editInstrIp->setText(QString(m_ifrfConfig.SigGenIp.c_str()));
    editInstrPort->setText(QString::number(m_ifrfConfig.siggenPort));
    editSpectIp->setText(QString(m_ifrfConfig.spectIp.c_str()));
    editSpectPort->setText(QString::number(m_ifrfConfig.spectPort));

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

    checkKeepTest->setChecked(m_ifrfConfig.keepTestIfFaled);
    checkRetestIfFailed->setChecked(m_ifrfConfig.reTestIfFailed);

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void TestIfrf::createTableViewHeader()
{
    tableView->setWordWrap(true);
    QStringList header;

    header << "Bài kiểm tra" << "Trạng thái" << "Giá trị" << "Min" << "Max" << "Thông tin";
    if(model == nullptr) {
        LREP("Error \n");
        return;
    }

    model->setHorizontalHeaderLabels(header);

    tableView->setModel(model);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setColumnWidth(0, 300);
    tableView->setColumnWidth(1, 250);
    tableView->setColumnWidth(2, 120);
    tableView->setColumnWidth(3, 120);
    tableView->setColumnWidth(4, 120);
    tableView->setColumnWidth(5, 550);
}

void TestIfrf::createConnection()
{
    /**
     * @brief button connection
     */
    connect(btnTestCaseSetting, SIGNAL(clicked(bool)), this, SLOT(on_btnSettingClicked()));
    connect(btnLoadTestParam, SIGNAL(clicked(bool)), this, SLOT(on_btnLoadTestParamClicked()));
    connect(btnStartTest, SIGNAL(clicked(bool)), this, SLOT(on_btnStartTestClicked()));    
    connect(btnConnectSpect, SIGNAL(clicked(bool)), this, SLOT(on_btnConnectSpectClicked()));
    connect(btnConnectInstr, SIGNAL(clicked(bool)), this, SLOT(on_btnConnectSignalGenClicked()));
    connect(btnConnectSerial, SIGNAL(clicked(bool)), this, SLOT(on_btnConnectSerialClicked()));
    connect(btnPause, SIGNAL(clicked(bool)), this, SLOT(on_btnPauseClicked()));

    /**
     * @brief data event connect
     */


    /**
     * @brief user edit parameter update
     */
    connect(editSpectIp, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(editSpectPort, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(editInstrIp, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(editInstrPort, SIGNAL(editingFinished()), this, SLOT(on_updateUserSetting()));
    connect(checkKeepTest, SIGNAL(clicked(bool)), this, SLOT(on_updateUserSetting()));
    connect(checkRetestIfFailed, SIGNAL(clicked(bool)), this, SLOT(on_updateUserSetting()));

    /**
     * @brief connection event
     */    
    connect(comboSerialList, SIGNAL(activated(QString)), this, SLOT(on_selectComClicked(QString)));
    connect(comboSerialList, SIGNAL(highlighted(QString)), this, SLOT(on_selectComClicked(QString)));

    connect(btnSendCommand, SIGNAL(clicked(bool)), this, SLOT(on_btnTestSendClicked()));
    connect(btnTestSpect, SIGNAL(clicked(bool)), this, SLOT(on_btnTestSpectClicked()));

}




void TestIfrf::InitTestResult()
{
    if(GetTestProgress() == Progress_First_Time) {
        LoadGenConfig();
        clearAllResultAndFailed();
    } else {
        LREP("Retest failed point\n");
        emit sigLoadRetestParamToUi();
        clearAllResult();
    }

    control->Spect_InitDevice();
    control->SigGen_InitDevice();
    control->Dev_SetAttent(0, true);
//    control->Dev_SetAttent(31.75, true);
}




/**
 * @brief TestIfrf::DoTestCurrent
 */
void TestIfrf::DoTestPowerConsume(ComParam &param)
{



}



/**
 * @brief TestIfrf::DoTestSensitive
Bước 1. Câu hình mạch
Cau hinh tan so thu của mạch có bao gồm điểm 22.025MHz (băng thông 40MHz)
Bước 2. Thiết lập máy phát tín hiệu cao tần
Đưa máy phát tín hiệu về trạng thái ban đầu : Ấn Preset;
Chọn chế độ ALC off;
Thiết lập tần số cao tần trên máy phát tín hiệu cao tần là 22.025 MHz tương ứng với kênh cần kiểm tra;
 Ấn FREQ  Chọn tần số tương ứng;
Thiết lập mức cao tần phát ra. Bắt đầu từ -120 dBm;
 Ấn AMPTD  -120 dBm;
Tắt đường cao tần ( RF on/off).
Bước 3. Thiết lập máy phân tích phổ tín hiệu
Đưa máy phát tín hiệu về trạng thái ban đầu : Ấn Preset;
Thiết lập tần số trung tâm bằng tần số trung tần 140MHz;
Ấn FREQ  Center  140MHz;
Thiết lập băng thông 40MHz;
 Ấn BW  40MHz;
Thiết lập mức công suất tham chiếu -50dBm;
 Ấn AMPT  REF  -50dBm;
Bước 4. Bắt đầu thực hiện đo
 Thực hiện phát tín hiệu cao tần từ máy phát tín hiệu vào thiết bị cần kiểm tra.
 Bật RF on/off (đèn tín hiệu báo bật);
Nhìn trên màn hình phân tích phô thác nước waterfall đã xuât hiện vạch phô
Thiết lập độ rộng tần số phân tích trên máy phân tích phổ 2Mhz, và độ phân giải băng thông 100Khz.
Ấn Span  2Mhz
Ấn BW Solution BW manual 100Khz
 Nếu tín hiệu được phát hiện và hiển thị trong cửa sổ danh sách tín hiệu
thì giá trị độ nhạy phát hiện tín hiệu là -120 dBm.
 Nếu chưa thây thì thực hiện theo bước 5.
Bước 5. Tìm độ nhạy
Tắt tín hiệu cao tần từ máy phát tín hiệu:
 Tắt RF on/off (đèn tín hiệu báo tắt)
Tăng mức cao tần trên máy phát tín hiệu cao tần mỗi bước 1dB.
Thực hiện phát tín hiệu cao tần từ máy phát tín hiệu:
 Bật RF on/off (đèn tín hiệu báo bật)
Kiểm tra vạch phô trên màn hình hiên thị nêu vân chưa thây thì thực hiện theo bước 6.
Bước 6:
Thực hiện theo bước 5 cho đến khi trên cửa sổ danh sách tín hiệu xuất hiện tín hiệu được phát từ máy phát
Giá trị độ nhạy hiện tại là giá trị máy phát tín hiệu cao tân (dBm);
Ghi lại kết quả đo được vào phụ lục 1.
Bước 7. Thực hiện đo độ nhạy thu tại các tần số còn lại theo quy định
Thực hiện tương tự để đo độ nhạy của mạch ở các tần số theo yêu cầu, đọc và
ghi kết quả đo được vào phiếu kiểm tra theo theo phụ lục tương ứng.
 */
void TestIfrf::DoTestSensitive(ComParam &param)
{
    if(param.input.freqTestList.size() == 0)
        return;
    control->SigGen_InitDevice();

    double currPwr = param.input.max;
    param.result.hasValue = false;

    control->Dev_SetAttent(0, true);
    std::vector<double>::iterator iter  = param.input.freqTestList.begin();
    control->SigGen_SetupFMMod(*iter, Freq_Mhz,
                            currPwr, Power_dBm,
                            1.0, Freq_Khz,
                            genConfig.siggenDelay); //Control server, freq passed is Mhz

    control->Spect_SetupFMDemodSinad(140, Freq_Mhz, 25000, 0.1, genConfig.siggenDelay);

    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {

        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
            control->SigGen_InitDevice();
            //control->Spect_InitDevice();
            control->SigGen_SetupFMMod(*iter, Freq_Mhz,
                                    currPwr, Power_dBm,
                                    1.0, Freq_Khz,
                                    genConfig.siggenDelay); //Control server, freq passed is Mhz

            control->Spect_SetupFMDemodSinad(140, Freq_Mhz, 25000, 0.1, genConfig.siggenDelay);
        }

        double freq = *iter;
        emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");
        emit updateStatusBar("Đang kiểm tra độ nhạy phát hiện tín hiệu tại: " +
                             QString::number(freq, 'g', 10) + " Mhz ...");

        param.result.hasValue = false;
        double getPwr = 0;
        control->Dev_SetFreqency(uint64_t(freq * 1E6));
        double sensitive = GetSensitiveValue(freq, param.input.ferr,
                                             param.input.min, param.input.max, getPwr);

        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;

        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }


        if(IFRF_RESET_VAL_IFRF) {
            param.result.hasValue = true;
            static bool log = true;
            log = !log;
            if(log) {
                sensitive = param.input.min;
                sensitive = param.input.max;
            } else {
                sensitive = param.input.min + 1;
                sensitive = param.input.max;
            }
        }

        if(sensitive != 0) {
            param.result.currValue = sensitive;
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
            displayValueOfFreq(param.result.currValue); // Show value is readed
        } else {
            displayAndWriteResultRow(testPoint, QString("N/A"));
            displayValueOfFreq("N/A");
            emit updateStatusBar("Không nhận được kết quả độ nhạy tại: " +
                                 QString::number(freq, 'g', 10) + " Mhz !!!", QColor(Qt::red));
        }

        if(!testPoint.passed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
        }

        param.result.listResult.push_back(testPoint);

        if((!m_ifrfConfig.keepTestIfFaled) && (!testPoint.passed)) {
            break;
        }

        iter++;
    }

    control->SigGen_DeSetCombo(200);
}

double TestIfrf::GetSensitiveValue(double freq, uint64_t ferr,
                                   double pwrMin, double pwrMax, double &getSinad)
{
    double currPwr = pwrMax;
    if(pwrMax > -10) pwrMax = -10;
    LREP("set signalgen: freq: {} - pwr: {}\n", freq, pwrMax);
    bool hasValue = false;    
    control->SigGen_SetRFFreq(freq, Freq_Mhz, genConfig.siggenDelay);    
    getSinad = 0;

    while(IsKeepgoingOnTest() &&
          !hasValue &&
          std::abs(currPwr) > std::abs(pwrMin)) {
        emit updateStatusBar("Đang kiểm tra tần: " +
                             QString::number(freq, 'g', 10) + " Mhz. Công suất máy phát " +
                             QString::number(currPwr) + " dBm");
        control->SigGen_SetRFPower(currPwr, Power_dBm, genConfig.siggenDelay);
        std::this_thread::sleep_for(std::chrono::milliseconds(genConfig.siggenDelay));
        Spect_ClearSignalList();
        control->Spect_GetSinad(genConfig.siggenDelay);
        control->Spect_StartCalculate();
        //std::this_thread::sleep_for(std::chrono::milliseconds(genConfig.siggenDelay));       
        control->Spect_GetFirstValue(getSinad);
        if(getSinad >= 10) {
            LREP("\n\nFrequency {} found {} at {} dbm!\n\n\n", freq * 1E6, getSinad, currPwr);
            hasValue = true;
            break;
        }
        currPwr+=1.0;
    }

    if(hasValue) {
        return currPwr;
    } else  {
        return 0;
    }
}


/**
 * @brief TestIfrf::DoTestSelectImage
Bước 1. Câu hình mạch
Câu hình tân sô thu của mạch có bao gồm điểm 22.025MHz (băng thông 40MHz)

Bước 2. Thiết lập máy phát tín hiệu cao tần
Đưa máy phát tín hiệu về trạng thái ban đầu : Ấn Preset;
Điêu chinh mức công suât đâu ra máy phát cao tân tại giá trị độ nhạy đo được ở bước 7.3.1
Chọn chế độ ALC off;
Thiết lập tần số cao tần trên máy phát tín hiệu cao tần là 22.025 MHz tương ứng với kênh cần kiểm tra;
 Ấn FREQ  Chọn tần số tương ứng;
Thiết lập mức cao tần phát ra. Bắt đầu từ giá trị độ nhạy đo được tại bước 7.3.1;
 Ấn AMPTD  nhập giá trị độ nhạy đo được tại bước 7.3.1;
Tắt đường cao tần ( RF on/off).

Bước 3. Thiết lập máy phân tích phổ tín hiệu
Đưa máy phát tín hiệu về trạng thái ban đầu : Ấn Preset;
Thiết lập tần số trung tâm bằng tần số trung tần 140MHz;
Ấn FREQ  Center  140MHz;
Thiết lập băng thông 40MHz;
 Ấn BW  40MHz;
Thiết lập mức công suất tham chiếu -50dBm;
 Ấn AMPT  REF  -50dBm;

Bước 4. Bắt đầu thực hiện đo
 Thực hiện phát tín hiệu cao tần từ máy phát tín hiệu vào thiết bị cần kiểm tra.
 Bật RF on/off (đèn tín hiệu báo bật);
Nhìn trên màn hình phân tích phô thác nước waterfall đã xuât hiện vạch phô

- Thiết lập độ rộng tần số phân tích trên máy phân tích phổ 1Mhz, và độ phân giải băng thông 100Khz.
- Ấn Span  1Mhz
- Ấn BW Solution BW manual 100Khz
 Tín hiệu được phát hiện và hiển thị trong cửa sổ danh sách tín hiệu, lưu lại giá trị  (gọi là Pout1).
 Tiếp tục thực hiện theo bước 5.
Bước 5. Tìm độ chọn lọc tần số ảnh.
Tắt tín hiệu cao tần từ máy phát tín hiệu:
 Tắt RF on/off (đèn tín hiệu báo tắt)

Thiết lập tần số cao tần trên máy phát tín hiệu cao tần là 4622.025 MHz tương ứng với tần số ảnh cần đo (bảng tần số ảnh tương ứng với mỗi tần số phát như phụ lục I đính kèm);
Ấn FREQ  4622.025Mhz.
    +  Thiết lập mức cao tần phát ra. Bắt đầu từ giá trị -50dBm
Ấn AMPTD  -50 dBm
    +  Thực hiện phát tín hiệu cao tần từ máy phát tín hiệu vào thiết bị cần kiểm tra.
Bật RF on/off (đèn tín hiệu báo bật);
Kiểm tra trên màn hình phân tích phổ. Nếu tín hiệu được phát hiện và hiển thị trong cửa sổ danh sách tín hiệu (gọi là Pout2). Nếu Pout2<Pout1. Thực hiện tiếp bước 6.

Bước 6:
Tắt tín hiệu cao tần từ máy phát tín hiệu:
 Tắt RF on/off (đèn tín hiệu báo tắt)
Tăng mức cao tần trên máy phát tín hiệu cao tần mỗi bước 1dB (đặt Pin là công suất trên máy phát sau khi đã tăng 1dB).
Thực hiện phát tín hiệu cao tần từ máy phát tín hiệu:
 Bật RF on/off (đèn tín hiệu báo bật)
Kiem tra vạch phô trên màn hình hiên thị, nếu giá trị Pout2<Pout1 tiếp tục thực hiện bước 7.
Bước 7:
Thực hiện theo bước 5 cho đến khi giá trị Pout2=Pout1. Độ chọn lọc tần số ảnh là hiệu số giữa Pin và độ nhạy thu tại bước 7.3.1;
Ghi lại kết quả đo được vào bảng tương ứng.
 *
 */
void TestIfrf::DoTestSelectImage(ComParam &param)
{

    if(param.input.freqTestList.size() == 0)
        return;

    double currPwr = -120;
    param.result.hasValue = false;

    control->Spect_InitDevice();
    control->SigGen_InitDevice();
    control->Dev_SetAttent(0, true);

    std::vector<double>::iterator iter  = param.input.freqTestList.begin();
    control->SigGen_SetupFMMod(*iter, Freq_Mhz,
                            currPwr, Power_dBm,
                            1.0, Freq_Khz,
                            genConfig.siggenDelay); //Control server, freq passed is Mhz

    control->Spect_SetupFMDemodSinad(140, Freq_Mhz, 25000, 0.1, genConfig.siggenDelay);
    control->Spect_SetReferentLevel(-10, genConfig.siggenDelay);

    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {

        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
            control->SigGen_InitDevice();
            //control->Spect_InitDevice();
            control->SigGen_SetupFMMod(*iter, Freq_Mhz,
                                    currPwr, Power_dBm,
                                    1.0, Freq_Khz,
                                    genConfig.siggenDelay); //Control server, freq passed is Mhz

            control->Spect_SetupFMDemodSinad(140, Freq_Mhz, 25000, 0.1, genConfig.siggenDelay);
        }

        double freq = *iter;
        emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");
        emit updateStatusBar("Đang kiểm tra độ nhạy phát hiện tín hiệu tại: " +
                             QString::number(freq, 'g', 10) + " Mhz ...");

        control->Dev_SetFreqency(uint64_t(freq * 1E6));

        param.result.hasValue = false;

        double getPwr = 0;
        double sensitive = GetSensitiveValue(freq, param.input.ferr,
                                             -105, -115, getPwr);


        LREP("get sensitive value: {}\n", sensitive);
        double sensitiveImg = 0;
        if(sensitive < 0) {
            sensitiveImg = GetSensitiveValue(ConvertToImageFreq(freq), param.input.ferr,
                                             -10, sensitive + param.input.max, getPwr);
        }

        LREP("get sensitiveIMG: {}\n", sensitiveImg);

        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;

        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }

        if(sensitive != 0 && sensitiveImg != 0) {
            param.result.currValue = sensitiveImg - sensitive;
            testPoint.value = param.result.currValue;
            LREP("sen img: {} send: {} result: {}", sensitiveImg, sensitive, testPoint.value);
            // Check pass fail
            if(param.result.currValue  >= param.input.max) {
                testPoint.passed = true;
                displayAndWriteResultRow(testPoint, true, getPwr);
            }else {
                testPoint.passed = false;
                displayAndWriteResultRow(testPoint, false);
            }
            param.result.hasValue = false;
            displayValueOfFreq(param.result.currValue); // Show value is readed
        } else {
            displayAndWriteResultRow(testPoint, QString("N/A"));
            displayValueOfFreq("N/A");
            emit updateStatusBar("Không nhận được kết quả độ nhạy tại: " +
                                 QString::number(freq, 'g', 10) + " Mhz !!!", QColor(Qt::red));
        }

        if(!testPoint.passed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
        }

        param.result.listResult.push_back(testPoint);

        if((!m_ifrfConfig.keepTestIfFaled) && (!testPoint.passed)) {
            break;
        }

        iter++;
    }

    control->SigGen_DeSetCombo(200);
}


/**
 * @brief TestIfrf::DoTestSelectInterFreq
 */
void TestIfrf::DoTestSelectInterFreq(ComParam &param)
{ 
    if(param.input.freqTestList.size() == 0)
        return;

    double currPwr = -120;
    param.result.hasValue = false;

    control->SigGen_InitDevice();
    control->Spect_InitDevice();
    control->Dev_SetAttent(0, true);

    std::vector<double>::iterator iter  = param.input.freqTestList.begin();
    control->SigGen_SetupFMMod(*iter, Freq_Mhz,
                            currPwr, Power_dBm,
                            1.0, Freq_Khz,
                            genConfig.siggenDelay); //Control server, freq passed is Mhz

    control->Spect_SetupFMDemodSinad(140, Freq_Mhz, 25000, 0.1, genConfig.siggenDelay);

    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {

        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
            control->SigGen_InitDevice();
            //control->Spect_InitDevice();
            control->SigGen_SetupFMMod(*iter, Freq_Mhz,
                                    currPwr, Power_dBm,
                                    1.0, Freq_Khz,
                                    genConfig.siggenDelay); //Control server, freq passed is Mhz

            control->Spect_SetupFMDemodSinad(140, Freq_Mhz, 25000, 0.1, genConfig.siggenDelay);
        }

        double freq = *iter;
        emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");
        emit updateStatusBar("Đang kiểm tra độ nhạy phát hiện tín hiệu tại: " +
                             QString::number(freq, 'g', 10) + " Mhz ...");

        control->Dev_SetFreqency(uint64_t(freq * 1E6));

        param.result.hasValue = false;

        double getPwr = 0;
        double sensitive = GetSensitiveValue(freq, param.input.ferr,
                                             -105, -115, getPwr);

        LREP("get sensitive value: {}\n", sensitive);
        double sensitiveImg = GetSensitiveValue(ConvertToInterFreq(freq), param.input.ferr,
                                             sensitive + param.input.max + 5, sensitive + param.input.max, getPwr);

        LREP("get sensitiveIMG: {}\n", sensitiveImg);

        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;

        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }

        if(1) {
            param.result.currValue = sensitiveImg - sensitive;
            testPoint.value = param.result.currValue;
            LREP("sen img: {} send: {} result: {}", sensitiveImg, sensitive, testPoint.value);

            if(sensitiveImg == 0 || param.result.currValue > param.input.max) {
                testPoint.passed = true;

                displayAndWriteResultRow(testPoint, true, getPwr);
                displayValueOfFreq( "> " + QString::number(param.input.max));
            }else {
                testPoint.passed = false;
                displayAndWriteResultRow(testPoint, false);
                displayValueOfFreq(param.result.currValue); // Show value is readed
            }
            param.result.hasValue = false;

        }

        if(!testPoint.passed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
        }

        param.result.listResult.push_back(testPoint);

        if((!m_ifrfConfig.keepTestIfFaled) && (!testPoint.passed)) {
            break;
        }

        iter++;
    }

    control->SigGen_DeSetCombo(200);    
}



/**
 * @brief TestIfrf::DoTestSpurious
 */
void TestIfrf::DoTestSpurious(ComParam &param)
{
    if(param.input.freqTestList.size() == 0)
        return;

    control->Spect_InitDevice();
    control->SigGen_InitDevice();
    double currPwr = -80;
    param.result.hasValue = false;

    std::vector<double>::iterator iter  = param.input.freqTestList.begin();
    control->SigGen_SetCombo(*iter, Freq_Mhz,
                            currPwr, Power_dBm,
                            1.0, Freq_Khz,
                            genConfig.siggenDelay); //Control server, freq passed is Mhz

    control->Spect_SetSpectrumWindow(140, Freq_Mhz, 40, Freq_Mhz, param.input.min, genConfig.siggenDelay);

//    control->SigGen_SetRFSignalOut(false, genConfig.siggenDelay);

    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {
        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
            control->SigGen_InitDevice();
            control->SigGen_SetCombo(*iter, Freq_Mhz,
                                    currPwr, Power_dBm,
                                    1.0, Freq_Khz,
                                    genConfig.siggenDelay); //Control server, freq passed is Mhz

            control->Spect_SetSpectrumWindow(140, Freq_Mhz, 40, Freq_Mhz, param.input.min, genConfig.siggenDelay);
        }

        double freq = *iter;
        emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");
        emit updateStatusBar("Đang kiểm tra spurious tại tần số: " +
                             QString::number(freq, 'g', 10) + " Mhz ...");

        param.result.hasValue = false;
        control->SigGen_SetRFFreq(freq, Freq_Mhz, genConfig.siggenDelay);
        control->Dev_SetFreqency(uint64_t(freq * 1E6));
        std::this_thread::sleep_for(std::chrono::milliseconds(genConfig.siggenDelay));
        control->Spect_ClearAllRecvData();
        control->Spect_SendCommand("*CLS\r\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(genConfig.siggenDelay * 3));
        control->Spect_GetScreenSpectrum(genConfig.siggenDelay);        
        std::this_thread::sleep_for(std::chrono::milliseconds(genConfig.siggenDelay * 3));
        control->Spect_StartCalculate();        
        std::list<FreqPoint> data_list = control->Spect_GetValueExcess(double(param.input.ferr));
        std::size_t size = data_list.size();
        //if(size >= 1) size -= 1;
        double percen = (double)size / control->Spect_GetListValueSize() * 100;
        LREP("list spur size: {} - value size: {}\npercen {}\n",
             size, control->Spect_GetListValueSize(), percen);
        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;

        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }

        if(control->Spect_GetListValueSize() != 0) {
            param.result.currValue = size;  //percen;
            testPoint.value = param.result.currValue;
            // Check pass fail
            QString comment;
            for(auto &var : data_list) {
                comment += "[F: "  + QString::number(var.point) +
                        " P: " + QString::number(var.value) + "] ";
            }
            resFile->write("H" + QString::number(currLineResult), comment);
            //if(param.result.currValue  <= param.input.max) {            
            if(percen  <= param.input.max) {
                testPoint.passed = true;
                displayAndWriteResultRow(testPoint, true, size);
            }else {
                testPoint.passed = false;
                displayAndWriteResultRow(testPoint, false, size);
            }                       

            param.result.hasValue = false;
            displayValueOfFreq(percen); // Show value is readed

        } else {
            displayAndWriteResultRow(testPoint, QString("N/A"));
            displayValueOfFreq("N/A");
            emit updateStatusBar("Không nhận được kết spurious tại: " +
                                 QString::number(freq, 'g', 10) + " Mhz !!!", QColor(Qt::red));
        }

        if(!testPoint.passed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
        }

        param.result.listResult.push_back(testPoint);

        if((!m_ifrfConfig.keepTestIfFaled) && (!testPoint.passed)) {
            break;
        }

        iter++;
    }

}



/**
 * @brief TestIfrf::DoTestImdInRange
Thực hiện tương tự các bước theo mục 7.3.2 (Bài đo méo hài bậc 3 IP3).
Giá trị IMD = P1 - P2
 */
void TestIfrf::DoTestImdInRange(ComParam &param)
{
    double freqSpace = 10.0; // Mhz
    double currentPwr = -20;

    if(param.input.freqTestList.size() == 0)
        return;

    control->SigGen_InitDevice();
    control->Spect_InitDevice();
    LREP("test IMD in range\n");

    control->Dev_SetAttent((double)param.input.ferr, true);
    control->Dev_SetAttent((double)param.input.ferr, true);

    std::vector<double>::iterator iter  = param.input.freqTestList.begin();
    control->Spect_SetSpectrumWindow(140, Freq_Mhz, 40, Freq_Mhz, param.input.min, genConfig.siggenDelay);

    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {
        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
            control->SigGen_InitDevice();
        }

        emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");

        double freq = *iter;
        LREP("set two tone\n");
        control->SigGen_SetTwoTone(freq, Freq_Mhz, freqSpace, Freq_Mhz, currentPwr, Power_dBm, genConfig.siggenDelay);
        LREP("done\n");
        control->Dev_SetFreqency(uint64_t(freq * 1E6));

        uint64_t mainFreq1 = 140 * 1E6 - (freqSpace / 2 * 1E6);
        uint64_t mainFreq2 = 140 * 1E6 + (freqSpace / 2 * 1E6);
        uint64_t lowFreq = mainFreq1 - (freqSpace  * 1E6);
        uint64_t highFreq = mainFreq2 + (freqSpace  * 1E6);

        double checkMain1;
        double checkMain2;
        double checkImg1;
        double checkImg2;

        //LREP("start check freq1: {} freq2: {} freq3: {} freq4: {}\n", lowFreq, mainFreq1, mainFreq2, highFreq);
        //int count = 15;
        {
            control->Spect_ClearAllRecvData();
            std::this_thread::sleep_for(std::chrono::milliseconds(genConfig.siggenDelay * 3));
            control->Spect_GetScreenSpectrum(genConfig.siggenDelay);
            std::this_thread::sleep_for(std::chrono::milliseconds(genConfig.siggenDelay * 3));
            control->Spect_StartCalculate();
            double maxval;
            control->Spect_GetMaxValue(maxval);
            LREP("get max value: {}\n", maxval);
            control->Spect_GetValueMaxAt(mainFreq1, checkMain1, 500000);
            control->Spect_GetValueMaxAt(mainFreq2, checkMain2, 500000);
            control->Spect_GetValueMaxAt(lowFreq, checkImg1, 500000);
            control->Spect_GetValueMaxAt(highFreq, checkImg2, 500000);

            control->SigGen_SetRFPower(currentPwr, Power_dBm, genConfig.siggenDelay);
            emit updateStatusBar("Đang kiểm tra tần: " +
                                 QString::number(freq, 'g', 10) + " Mhz. Công suất máy phát " +
                                 QString::number(currentPwr) + " dBm");
        }

        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;

        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }

        LREP("CHECK 1: {} CHECK 2: {} CHECK 3: {} CHECK 4: {}\n", checkMain1,
             checkMain2, checkImg1, checkImg2);
        if(checkMain1 != 0 && checkMain2 != 0 && checkImg1 != 0 && checkImg2 != 0) {
            testPoint.value  = checkMain1 - checkImg1;
            LREP("__________THIRD {}__________\n", testPoint.value);
            param.result.currValue = testPoint.value;
            // Check pass fail
            if(param.result.currValue >= param.input.max) {
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
                                 QString::number(freq, 'g', 10) + " Mhz !!!",
                                 QColor(Qt::red));
        }

        if(!testPoint.passed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
        }

        param.result.listResult.push_back(testPoint);
        if((!m_ifrfConfig.keepTestIfFaled) && (!testPoint.passed))
            break;

        iter++;
    }


    control->SigGen_DeSetCombo(200);
}

/**
 * @brief TestIfrf::DoTestImdOutRange
 Thực hiện tương tự các bước theo mục 7.3.2 (Bài đo méo hài bậc 3 IP3),
nhưng với giá trị tone spacing bằng 44Mhz. Giá trị IMD = P1-P2
 */
void TestIfrf::DoTestImdOutRange(ComParam &param)
{
    double freqSpace = 44.0; // Mhz
    double currentPwr = param.input.max - 4;

    if(param.input.freqTestList.size() == 0)
        return;

    control->SigGen_InitDevice();
    control->Spect_InitDevice();

    LREP("test IMD out range\n");

    control->Dev_SetAttent(0, true);

    std::vector<double>::iterator iter  = param.input.freqTestList.begin();
    control->Spect_SetSpectrumWindow(140, Freq_Mhz, 40, Freq_Mhz, -30, genConfig.siggenDelay);
    control->SigGen_SetTwoTone(*iter, Freq_Mhz, freqSpace, Freq_Mhz, currentPwr, Power_dBm, genConfig.siggenDelay);

    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {
        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
            control->SigGen_InitDevice();
        }
        emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");

        double freq = *iter;
        double freqout = freq - ((3 * freqSpace / 2) + 10);
        if(freqout < 20) freqout = 20;
        currentPwr = param.input.max - 4;
        //control->SigGen_SetTwoTone(freqout, Freq_Mhz, freqSpace, Freq_Mhz, currentPwr, Power_dBm, genConfig.siggenDelay);
        control->SigGen_SetRFFreq(freqout, Freq_Mhz, genConfig.siggenDelay);
        control->Dev_SetFreqency(uint64_t(freq * 1E6));


        double maxval, minval;        
        int count = param.input.min;
        bool hasvalue = false;
        do {
            control->SigGen_SetRFPower(currentPwr, Power_dBm, genConfig.siggenDelay);
            control->Spect_ClearAllRecvData();
            control->Spect_GetScreenSpectrum(genConfig.siggenDelay);
            std::this_thread::sleep_for(std::chrono::milliseconds(genConfig.siggenDelay * 3));
            control->Spect_StartCalculate();
            control->Spect_GetValueMaxAt(uint64_t((140.0 + 10.0) * 1E6), maxval, 500000);
            control->Spect_GetValueAtPoint(uint64_t((140.0 + 9.5) * 1E6), minval);
            double diff = std::abs(std::abs(maxval) -  std::abs(minval));
            LREP("get peak value: {} min value: {} diff: {}\n", maxval, minval, diff);
            if(diff > 6) {
                LREP("get tone: {}\n", diff);
                hasvalue = true;
            }

            currentPwr+=1.0;
            LREP("set power: {}\n", currentPwr);
            count--;
        } while(IsKeepgoingOnTest() && (count > 0) && !hasvalue);

        currentPwr -= 1;
        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;

        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }


        if(hasvalue) {
            testPoint.value  = currentPwr;
            LREP("__________IMD OUT {}__________\n", testPoint.value);
            param.result.currValue = testPoint.value;
            // Check pass fail
            if(testPoint.value >= param.input.max) {
                testPoint.passed = true;
                displayAndWriteResultRow(testPoint, true);
            }else {
                testPoint.passed = false;
                displayAndWriteResultRow(testPoint, false);
            }
            // Show value is readed
            displayValueOfFreq(param.result.currValue);

        } else {
            testPoint.passed = true;
            displayAndWriteResultRow(testPoint, true);
            displayValueOfFreq("> " + QString::number(currentPwr));

            emit updateStatusBar("Không nhận được kết quả méo hài bậc ba tại: " +
                                 QString::number(freq, 'g', 10) + " Mhz !!!",
                                 QColor(Qt::red));
        }

        if(!testPoint.passed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
        }

        param.result.listResult.push_back(testPoint);
        if((!m_ifrfConfig.keepTestIfFaled) && (!testPoint.passed))
            break;

        iter++;
    }


    //control->SigGen_DeSetCombo(200);
}



/**
 * @brief TestIfrf::DoTestThirdInt
Bước 1. Câu hình mạch
Câu hình tân sô thu của mạch có bao gồm điểm 22.025MHz (băng thông 40MHz)
Bước 2. Thiết lập máy phát tín hiệu cao tần
Đưa máy phát tín hiệu về trạng thái ban đầu: Ấn Preset
Thiết lập tần số và mức công suất máy phát.
Ấn Freq22.025Mhz
AMPTD-30dBm (đặt là Pin)
Thực hiện phát 2 tone tín hiệu với mức biên độ -30 dBm, khoảng cách giữa 2 tín hiệu 2Mhz.
Ấn ModeMultitone Initialize Table. Tại tab “Number of tones”: Ấn 2 Enter. Tại tab “Freq Spacing”: Ấn 2 Mhz Done
Sử sụng các phím mũi tên (lên, xuống, trái, phải) trên máy phát để thiết lập mức Power và Phase của 2 tones. Ở bài test này, để ở giá trị mặc định Power = 0dB và Phase = 0.
Chọn chế độ ALC off;
Tắt đường cao tần ( RF on/off).
Bước 3. Thiết lập máy phân tích phổ tín hiệu
Đưa máy phát tín hiệu về trạng thái ban đầu : Ấn Preset;
Thiết lập tần số trung tâm bằng tần số trung tần 140MHz;
Ấn FREQ  Center  140MHz;
Thiết lập băng thông 40MHz;
 Ấn BW  40MHz;
Thiết lập mức công suất tham chiếu -10dBm;
 Ấn AMPT  REF  -10dBm;
Bước 4. Bắt đầu thực hiện đo
 Bật chế độ phát 2 tones. Tại tab Multitone: on
Thực hiện phát tín hiệu cao tần từ máy phát tín hiệu vào thiết bị cần kiểm tra.
 Bật chế độ phát 2 tones. Tại tab Multitone: on
 Bật RF on/off (đèn tín hiệu báo bật);
Thiết lập độ rộng tần số phân tích trên máy phân tích phổ 10Mhz, và độ phân giải băng thông 100Khz.
Ấn Span  10Mhz
Ấn BW Solution BW manual 100Khz
Nhìn trên màn hình phân tích phổ thác nước waterfall xuât hiện tối thiểu 4 vạch phô
tại các điểm tần số tương ứng là 23.025 Mhz, 21.025Mhz, 19.025 Mhz, 25.025 Mhz.
Trong đó vạch phổ tại các tần số 23.025 Mhz, 21.025Mhz có giá trị biên độ xấp xỉ nhau
(đặt là P1) và vạch phổ tại các tần số 19.025 Mhz, 25.025 Mhz có giá trị biên độ
xấp xỉ nhau (đặt là P2).
Giá trị IP3 = Pin + (P1-P2)/2                                                         (1)
Ghi lại kết quả đo vào bảng tương ứng.
(Ấn Meas More ½ TOI. Trong tab Function result. Đọc giá trị TOI, ghi lại kết quả đo vào bảng 1.)
Trong trường hợp giá trin P2 rất nhỏ, chưa vượt qua ngưỡng của nền nhiễu. Thực hiện tiếp Bước 5.
Bước 5. Tìm giá trị méo hài bậc 3 IP3
Tắt tín hiệu cao tần từ máy phát tín hiệu:
 Tắt RF on/off (đèn tín hiệu báo tắt)
Tăng mức cao tần trên máy phát tín hiệu cao tần mỗi bước 1dB.
Thực hiện phát tín hiệu cao tần từ máy phát tín hiệu:
 Bật RF on/off (đèn tín hiệu báo bật)
Kiêm tra vạch phô trên màn hình hiên thị nêu tín hiệu tại các tần số 19.025 Mhz và 25.025 Mhz vân chưa thây thì thực hiện tiếp bước 6.
Bước 6:
Thực hiện theo bước 5 cho đến khi trên cửa sổ danh sách tín hiệu xuất hiện tín vạch phổ tại các tần số 19.025 Mhz và 25.025 Mhz.
Tính giá trị IP3 theo công thức (1) tại bước 4;
Ghi lại kết quả đo được vào phụ lục tương ứng.
Bước 7. Thực hiện đo giá trị IP3 tại các tần số còn lại theo quy định
Thực hiện tương tự để đo hệ số IP3 của mạch ở các tần số theo yêu cầu, đọc và ghi kết quả đo được vào phiếu kiểm tra theo theo phụ lục tương ứng.
 */
void TestIfrf::DoTestThirdInt(ComParam &param)
{
    double freqSpace = 10.0; // Mhz
    double currentPwr = -20;

    control->Spect_InitDevice();

    if(param.input.freqTestList.size() == 0)
        return;

    control->SigGen_InitDevice();
    control->Spect_InitDevice();

    LREP("test third int\n");

    control->Dev_SetAttent((double)param.input.ferr, true);
    control->Dev_SetAttent((double)param.input.ferr, true);

    std::vector<double>::iterator iter  = param.input.freqTestList.begin();       
    control->Spect_SetSpectrumWindow(140, Freq_Mhz, 40, Freq_Mhz, param.input.min, genConfig.siggenDelay);

    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {
        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
            control->SigGen_InitDevice();
        }

        emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");

        double freq = *iter;
        LREP("set two tone\n");
        control->SigGen_SetTwoTone(freq, Freq_Mhz, freqSpace, Freq_Mhz, currentPwr, Power_dBm, genConfig.siggenDelay);
        LREP("done\n");
        control->Dev_SetFreqency(uint64_t(freq * 1E6));

        uint64_t mainFreq1 = 140 * 1E6 - (freqSpace / 2 * 1E6);
        uint64_t mainFreq2 = 140 * 1E6 + (freqSpace / 2 * 1E6);
        uint64_t lowFreq = mainFreq1 - (freqSpace  * 1E6);
        uint64_t highFreq = mainFreq2 + (freqSpace  * 1E6);

        double checkMain1;
        double checkMain2;
        double checkImg1;
        double checkImg2;

        //LREP("start check freq1: {} freq2: {} freq3: {} freq4: {}\n", lowFreq, mainFreq1, mainFreq2, highFreq);
        //int count = 15;
        {
            control->Spect_ClearAllRecvData();
            std::this_thread::sleep_for(std::chrono::milliseconds(genConfig.siggenDelay * 3));
            control->Spect_GetScreenSpectrum(genConfig.siggenDelay);
            std::this_thread::sleep_for(std::chrono::milliseconds(genConfig.siggenDelay * 3));
            control->Spect_StartCalculate();
            double maxval;
            control->Spect_GetMaxValue(maxval);
            LREP("get max value: {}\n", maxval);
            control->Spect_GetValueMaxAt(mainFreq1, checkMain1, 500000);
            control->Spect_GetValueMaxAt(mainFreq2, checkMain2, 500000);
            control->Spect_GetValueMaxAt(lowFreq, checkImg1, 500000);
            control->Spect_GetValueMaxAt(highFreq, checkImg2, 500000);

            //control->SigGen_SetRFPower(currentPwr, Power_dBm, genConfig.siggenDelay);
            emit updateStatusBar("Đang kiểm tra tần: " +
                                 QString::number(freq, 'g', 10) + " Mhz. Công suất máy phát " +
                                 QString::number(currentPwr) + " dBm");            
        }

        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;

        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }

        LREP("CHECK 1: {} CHECK 2: {} CHECK 3: {} CHECK 4: {}\n", checkMain1,
             checkMain2, checkImg1, checkImg2);
        if(checkMain1 != 0 && checkMain2 != 0 && checkImg1 != 0 && checkImg2 != 0) {
            testPoint.value  = currentPwr + (checkMain1 - checkImg1) / 2.0;
            LREP("__________THIRD {}__________\n", testPoint.value);
            param.result.currValue = testPoint.value;
            // Check pass fail
            if(param.result.currValue >= param.input.max) {
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
                                 QString::number(freq, 'g', 10) + " Mhz !!!",
                                 QColor(Qt::red));
        }

        if(!testPoint.passed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
        }

        param.result.listResult.push_back(testPoint);
        if((!m_ifrfConfig.keepTestIfFaled) && (!testPoint.passed))
            break;

        iter++;
    }

    //control->SigGen_DeSetCombo(200);
}

/**
 * @brief TestIfrf::DoTestJamingRange
 */
void TestIfrf::DoTestJamingRange(ComParam &param)
{

}

/**
 * @brief TestIfrf::DoTestP1Param
Bước 1. Câu hình mạch
Câu hình tân sô thu của mạch có bao gồm điểm 22.025MHz (băng thông 40MHz)
Bước 2. Thiết lập máy phát tín hiệu cao tần
Đưa máy phát tín hiệu về trạng thái ban đầu : Ấn Preset;
Điêu chinh mức công suât đâu ra máy phát cao tân mức -50 dBm
Chọn chế độ ALC off;
Thiết lập tần số cao tần trên máy phát tín hiệu cao tần là 22.025 MHz tương ứng với kênh cần kiểm tra;
 Ấn FREQ  Chọn tần số tương ứng;
Thiết lập mức cao tần phát ra. Bắt đầu từ giá trị -50dBm;
 Ấn AMPTD  -50 dBm (đặt là Pin);
Tắt đường cao tần ( RF on/off).
Bước 3. Thiết lập máy phân tích phổ tín hiệu
Đưa máy phát tín hiệu về trạng thái ban đầu : Ấn Preset;
Thiết lập tần số trung tâm bằng tần số trung tần 140MHz;
Ấn FREQ  Center  140MHz;
Thiết lập băng thông 40MHz;
 Ấn BW  40MHz;
Thiết lập mức công suất tham chiếu -10dBm;
 Ấn AMPT  REF  -10dBm;
Bước 4. Bắt đầu thực hiện đo
 Thực hiện phát tín hiệu cao tần từ máy phát tín hiệu vào thiết bị cần kiểm tra.
 Bật RF on/off (đèn tín hiệu báo bật);
Nhìn trên màn hình phân tích phổ thác nước waterfall đã xuất hiện vạch phổ
Thiết lập độ rộng tần số phân tích trên máy phân tích phổ 1Mhz, và độ phân giải băng thông 100Khz.
Ấn Span  1Mhz
Ấn BW Solution BW manual 100Khz
 Tín hiệu được phát hiện và hiển thị trong cửa sổ danh sách tín hiệu, lưu lại giá trị
(gọi là Pout). Tính giá trị G = Pout – Pin.
 Tiếp tục thực hiện theo bước 5.
Bước 5. Tìm giá trị p1dB
Tắt tín hiệu cao tần từ máy phát tín hiệu:
 Tắt RF on/off (đèn tín hiệu báo tắt)
Tăng mức cao tần trên máy phát tín hiệu cao tần mỗi bước 1dB.
Thực hiện phát tín hiệu cao tần từ máy phát tín hiệu:
 Bật RF on/off (đèn tín hiệu báo bật)
Kiêm tra vạch phô trên màn hình hiên thị, nếu giá trị G không đổi tiếp tục thực hiện bước 6.
Bước 6:
Thực hiện theo bước 5 cho đến khi giá trị G giảm đi 1dB. Giá trị P1dB chính là giá trị Pin (dBm);
Ghi lại kết quả đo được vào phụ lục 1.
Bước 7. Thực hiện đo giá trị P1dB tại các tần số còn lại theo quy định
Thực hiện tương tự để đo điểm P1dB của mạch ở các tần số theo yêu cầu, đọc và ghi kết quả đo được vào phiếu kiểm tra theo theo phụ lục tương ứng.
 */
void TestIfrf::DoTestP1Param(ComParam &param)
{
    double currPin = param.input.max - 1;
    control->Dev_SetAttent(0, true);
    //control->Dev_SetAttent(31.75, true);
    control->Spect_InitDevice();
    if(param.input.freqTestList.size() == 0)
        return;

    control->SigGen_InitDevice();
    control->Spect_InitDevice();

    std::vector<double>::iterator iter  = param.input.freqTestList.begin();

    control->SigGen_SetCombo(*iter, Freq_Mhz,
                            currPin, Power_dBm,
                            1.0, Freq_Khz,
                            genConfig.siggenDelay);

    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {
        emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");
        double currPout, lastPout, currPin = 0;
        currPin = param.input.min;
        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
            control->SigGen_InitDevice();
            control->Spect_InitDevice();
        }

        double freq = *iter;
        control->Dev_SetFreqency(uint64_t(freq * 1E6));
        control->SigGen_SetRFFreq(freq, Freq_Mhz, genConfig.siggenDelay);
        control->SigGen_SetRFPower(currPin, Power_dBm, genConfig.siggenDelay);
        control->Spect_ClearAllRecvData();
        control->Spect_GetPowerMaxHold(140, Freq_Mhz, 25, genConfig.siggenDelay);
        control->Spect_StartCalculate();
        control->Spect_GetFirstValue(currPout);
        lastPout = currPout;

        int count = 10;
        do {            
            emit updateStatusBar("Đang kiểm tra tần: " +
                                 QString::number(freq, 'g', 20) + " Mhz. Công suất máy phát " +
                                 QString::number(currPin) + " dBm");
            currPin +=1;
            control->SigGen_SetRFPower(currPin, Power_dBm, genConfig.siggenDelay);
            //control->Spect_GetPowerMaxHold(140, Freq_Mhz, 25, genConfig.siggenDelay);
            control->Spect_GetValueAtMarker(MarkerValueType_Level, genConfig.siggenDelay);
            control->Spect_StartCalculate();
            control->Spect_GetFirstValue(currPout);
            // Kiểm tra nếu mức chênh lệch công suất vào ra thay đổi 1dBm

            LREP("delta Pout = {}\n", std::abs(currPout - lastPout));
            if(std::abs(currPout - lastPout) > 0.8) {
                lastPout = currPout;
            } else {
                param.result.hasValue = true;
                LREP("stop inc power\n");
                break;
            }

        }while(IsKeepgoingOnTest() && count--);


        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;

        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }


        if(param.result.hasValue) {
            testPoint.value  = currPin;
            param.result.currValue = testPoint.value;
            // Check pass fail
            if(param.result.currValue >= param.input.max) {
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

            emit updateStatusBar("Không nhận được kết quả P1dB tại: " +
                                 QString::number(freq, 'g', 10) + " Mhz !!!", QColor(Qt::red));
        }

        if(!testPoint.passed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
        }

        param.result.listResult.push_back(testPoint);
        if((!m_ifrfConfig.keepTestIfFaled) && (!testPoint.passed))
            break;

        iter++;
    }

    control->SigGen_DeSetCombo(200);
}

/**
 * @brief TestIfrf::DoTestDynLinear
 * @param param
 * Dải động tuyến tính = P1dB (dBm) tại bước 7.3.3 – Độ nhạy thu (dBm) tại bước 7.3.1
 */
void TestIfrf::DoTestDynLinear(ComParam &param)
{

    control->SigGen_InitDevice();
    control->Spect_InitDevice();

    if(param.input.freqTestList.size() == 0)
        return;

    std::vector<double>::iterator iter  = param.input.freqTestList.begin();

    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {
        emit updateCellData(currLineIdx, STATUS_IN_COLUM, "TESTING");
        double currPout, lastPout = 0;
        double currPin = -20;

        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
            control->SigGen_InitDevice();
            control->Spect_InitDevice();
        }

        double freq = *iter;
        double getPwr = 0;
        //control->Dev_SetFreqency(uint64_t(freq * 1E6));
        control->SigGen_SetupFMMod(freq, Freq_Mhz,
                                -120, Power_dBm,
                                1.0, Freq_Khz,
                                genConfig.siggenDelay); //Control server, freq passed is Mhz

        control->Spect_SetupFMDemodSinad(140, Freq_Mhz, 25000, 0.1, genConfig.siggenDelay);
        control->Spect_SetReferentLevel(-10, genConfig.siggenDelay);

        control->Dev_SetFreqency(uint64_t(freq * 1E6));
        double senValue = GetSensitiveValue(freq, param.input.ferr, -100, -115, getPwr);

        control->Spect_InitDevice();

        control->SigGen_SetCombo(freq, Freq_Mhz,
                                currPin, Power_dBm,
                                1.0, Freq_Khz,
                                genConfig.siggenDelay);

        control->SigGen_SetRFFreq(freq, Freq_Mhz, genConfig.siggenDelay);
        control->SigGen_SetRFPower(currPin, Power_dBm, genConfig.siggenDelay);
        control->Spect_ClearAllRecvData();
        control->Spect_GetPowerMaxHold(140, Freq_Mhz, 25, genConfig.siggenDelay);
        control->Spect_StartCalculate();
        control->Spect_GetFirstValue(currPout);
        lastPout = currPout;
        do {
            emit updateStatusBar("Đang kiểm tra tần: " +
                                 QString::number(freq, 'g', 20) + " Mhz. Công suất máy phát " +
                                 QString::number(currPin) + " dBm");
            currPin +=1;
            control->SigGen_SetRFPower(currPin, Power_dBm, genConfig.siggenDelay);
            //control->Spect_GetPowerMaxHold(140, Freq_Mhz, 25, genConfig.siggenDelay);
            control->Spect_GetValueAtMarker(MarkerValueType_Level, genConfig.siggenDelay);
            control->Spect_StartCalculate();
            control->Spect_GetFirstValue(currPout);
            // Kiểm tra nếu mức chênh lệch công suất vào ra thay đổi 1dBm

            LREP("delta Pout = {}\n", std::abs(currPout - lastPout));
            if(std::abs(currPout - lastPout) > 0.8) {
                lastPout = currPout;
            } else {
                param.result.hasValue = true;
                LREP("stop inc power\n");
                break;
            }
        }while(IsKeepgoingOnTest() && currPin < param.input.min);


        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;

        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }


        if(param.result.hasValue && senValue!= 0) {
            testPoint.value  = currPin - senValue;
            param.result.currValue = testPoint.value;
            // Check pass fail
            if(param.result.currValue >= param.input.max) {
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

            emit updateStatusBar("Không nhận được kết quả dynamic range tại: " +
                                 QString::number(freq, 'g', 10) + " Mhz !!!", QColor(Qt::red));
        }

        if(!testPoint.passed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
        }

        param.result.listResult.push_back(testPoint);
        if((!m_ifrfConfig.keepTestIfFaled) && (!testPoint.passed))
            break;

        iter++;
    }

    control->SigGen_DeSetCombo(200);
}

/**
 * @brief TestIfrf::DoTestBwCenterFreq
Bước 1. Câu hình mạch
Câu hình tân sô thu của mạch bao gồm điểm 30MHz (băng thông 40MHz)
Bước 2. Thiết lập máy phát tín hiệu cao tần
Đưa máy phát tín hiệu về trạng thái ban đầu : Ấn Preset;
Chọn chế độ ALC off;
Thiết lập tần số cao tần trên máy phát tín hiệu cao tần là 30 MHz tương ứng với tần số trung tâm của dải tần cần kiểm tra;
 Ấn FREQ  30Mhz;
Thiết lập mức cao tần phát ra. Giá trị -50dBm;
 Ấn AMPTD  -50 dBm;
Tắt đường cao tần ( RF on/off).
Bước 3. Thiết lập máy phân tích phổ tín hiệu
Đưa máy phát tín hiệu về trạng thái ban đầu : Ấn Preset;
Thiết lập tần số trung tâm bằng tần số trung tần 140MHz;
Ấn FREQ  Center  140MHz;
Thiết lập băng thông 40MHz;
 Ấn BW  40MHz;
Thiết lập mức công suất tham chiếu -10dBm;
 Ấn AMPT  REF  -10dBm;
    Bước 4. Bắt đầu thực hiện đo
 Thực hiện phát tín hiệu cao tần từ máy phát tín hiệu vào thiết bị cần kiểm tra.
 Bật RF on/off (đèn tín hiệu báo bật);
Nhìn trên màn hình phân tích phô thác nước waterfall đã xuât hiện vạch phô
Thiết lập độ rộng tần số phân tích trên máy phân tích phổ 60Mhz, và độ phân giải băng thông 100Khz.
Ấn Span  60Mhz
Ấn BW Solution BW manual 100Khz
Đặt chế độ lấy vết phổ lớn nhất Maxhold: Nhấn Trace Trace 1  Maxhold
+ Phát tín hiệu cao tần dải 20-60Mhz, bước thay đổi tần số là 1Mhz.
Trên máy phát: Ấn FREQ, sử dụng mũi tên (trái, phải) để dịch chuyển con trỏ chuột vào vị trí hàng đơn vị của giá trị tần số.
Xoay núm điều chỉnh tần số về bên trái và bên phải sao cho dải tần phát là 20 – 30Mhz.
+ Thực hiện tiếp bước 5
Bước 5. Đọc giá trị băng thông trung tần của mạch
Trên máy phân tích phổ, lấy giá chị công suất lớn nhất:
 Nhấn Peak Search và ghi lại giá trị đỉnh phổ là P1(dBm)
Di chuyển con trỏ theo đường tín hiệu bên trái (so với đỉnh phổ lớn nhất của tín hiệu)
và đặt con trỏ tại vị trí mức tín hiệu chênh lệnh so với đỉnh phổ 3dB (tức là giá trị P1 – 3 dBm). Giả sử điểm tìm được là điểm A ;
Ấn MRK  Marker1  Delta và di chuyển con trỏ về phía bên phải so với đỉnh phổ lớn nhất của
tín hiệu để tìm điểm có mức công suất chênh lệch so với đỉnh phổ là 3dB. Giả sử điểm tình được là điểm B;
Giá trị độ rộng băng thông được xác định là khoảng tần số giữa B và A:
Bandwidth =  B - A (Mhz)
Ghi lại kết quả đo được vào phụ lục tương ứng.
 */
void TestIfrf::DoTestBwCenterFreq(ComParam &param)
{
    double Pin = -50, freqLow, freqHigh;

    control->Dev_SetAttent(0, true);

    control->SigGen_InitDevice();
    control->Spect_InitDevice();

    if(param.input.freqTestList.size() == 0)
        return;

    std::vector<double>::iterator iter  = param.input.freqTestList.begin();

    control->SigGen_SetCombo(*iter, Freq_Mhz,
                            Pin, Power_dBm,
                            1.0, Freq_Khz,
                            genConfig.siggenDelay);

    while(IsKeepgoingOnTest() && iter != param.input.freqTestList.end()) {
        if(GetTestState() == TestState_Pause) {
            emit updateStatusBar("ĐÃ TẠM DỪNG CHƯƠNG TRÌNH");
            PauseTest();
            control->SigGen_InitDevice();
            control->Spect_InitDevice();
        }

        double freq = *iter;
        double setfreq = freq - 30.0;
        double maxfreq = freq + 30.0;
        control->Dev_SetFreqency(uint64_t(freq * 1E6));

        control->Spect_GetPowerMaxHold(140, Freq_Mhz, 0, genConfig.siggenDelay);
        control->Spect_SetSpan(100, Freq_Mhz, genConfig.siggenDelay);
        std::vector<double> listvalue;
        listvalue.clear();
        for( ; setfreq < maxfreq; setfreq += 0.5) {
            double currPout;
            control->SigGen_SetRFFreq(setfreq, Freq_Mhz, genConfig.siggenDelay / 2);
            control->Spect_ClearAllRecvData();
            control->Spect_SetMarkerMax(genConfig.siggenDelay);
            control->Spect_GetValueAtMarker(MarkerValueType_Level, genConfig.siggenDelay / 2);
            control->Spect_StartCalculate();
            control->Spect_GetFirstValue(currPout);
            LREP("gen freq: {} get max: {}\n", setfreq, currPout);
            listvalue.push_back(currPout);
            if(!IsKeepgoingOnTest()) {
                break;
            }
        }

        std::size_t listsize = listvalue.size();
        LREP("list size: {}\n", listsize);
        double max_value = -200, min_value = 0;
        for(auto &var : listvalue) {
            if(var > max_value) {
                max_value = var;
            }
        }
        for(auto &var : listvalue) {
            if(var < min_value) {
                min_value = var;
            }
        }

        double checkfreq = freq;
        for(int i = listsize / 2; i < listsize; i++) {
            checkfreq += 0.5;
            if(listvalue[i] < (max_value - 3)) {
                LREP("found low at: {}\n", checkfreq);
                break;
            }
        }

        freqHigh = checkfreq;

        checkfreq = freq;
        for(int i = listsize / 2; i > 0; i--) {
            checkfreq -= 0.5;
            if(listvalue[i] < (max_value - 3)) {
                LREP("found high at: {}\n", checkfreq);
                break;
            }
        }

        freqLow = checkfreq;

        TestPoint testPoint;
        testPoint.point = freq;
        testPoint.passed = false;

        if(GetTestProgress() == Progress_Retest_Failed_Point) {
            uint32_t writeLine = GetLineWithFreqFailed(param.input.reTestingList, freq);
            if(writeLine != 0) currLineResult = writeLine;
        }

        LREP("max = {} min = {} Freq low = {} freq high = {}\n",
             max_value, min_value, freqLow, freqHigh);

        if(freqLow != 0 && freqHigh != 0) {
            testPoint.value  = std::abs(freqHigh - freqLow);
            param.result.currValue = testPoint.value;
            // Check pass fail
            if(param.result.currValue >= param.input.max) {
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

            emit updateStatusBar("Không nhận được kết quả cent bandwidth tại: " +
                                 QString::number(freq, 'g', 10) + " Mhz !!!", QColor(Qt::red));
        }

        if(!testPoint.passed) {
            FailPoint failed;
            failed.freq = freq;
            failed.writeLine = currLineResult - 1;
            param.input.failFreqList.push_back(failed);
        }

        param.result.listResult.push_back(testPoint);
        if((!m_ifrfConfig.keepTestIfFaled) && (!testPoint.passed))
            break;

        iter++;
    }

//    control->SigGen_DeSetCombo(200);
}

void TestIfrf::InitAllTestName()
{
    m_listTestName.push_back(IFRF_STR_TEST_SENSITIVE);
    m_listTestName.push_back(IFRF_STR_TEST_IP3);
    m_listTestName.push_back(IFRF_STR_TEST_P1dB);
    m_listTestName.push_back(IFRF_STR_TEST_DO_CL_ANH);
    m_listTestName.push_back(IFRF_STR_TEST_CL_F_M);
    m_listTestName.push_back(IFRF_STR_TEST_DYN_LINEAR);
    m_listTestName.push_back(IFRF_STR_TEST_BW_SIG_F_M);
    m_listTestName.push_back(IFRF_STR_TEST_SPUR);
    m_listTestName.push_back(IFRF_STR_TEST_IMD_IN_RANGE);
    m_listTestName.push_back(IFRF_STR_TEST_IMD_OUT_RANGE);
    m_listTestName.push_back(IFRF_STR_TEST_OP_RANGE_JAM);
    m_listTestName.push_back(IFRF_STR_TEST_PWR_CONSUM);
}

void TestIfrf::GetResultFromPower()
{
    //emit updateStatusBar("LẤY KẾT QUẢ TỪ BỘ NGUỒN ");
    //std::this_thread::sleep_for(std::chrono::milliseconds(genConfig.siggenDelay));
}


/**
 * @brief TestIfrf::DoTestSuiteFunction
 */
void TestIfrf::DoTestSuiteFunction()
{
    while(!doTestSuiteTerm) {
        if(IsKeepgoingOnTest()) {
            InitTestResult();
            qDebug() << "/--------------------------------------/\n";
            emit clearColumData(STATUS_IN_COLUM, totalResIdx + 1, 0); // Clear include TOTAL result
            emit clearColumData(VALUE_IN_COLUM, totalResIdx + 1, 0); // Clear include TOTAL result
            currLineIdx = 1;
            currLineResult = 21;

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

                if(test.second.name == IFRF_STR_TEST_SENSITIVE) {
                    DoTestSensitive(test.second);
                } else if(test.second.name == IFRF_STR_TEST_IP3) {
                    DoTestThirdInt(test.second);
                } else if(test.second.name == IFRF_STR_TEST_P1dB) {
                    DoTestP1Param(test.second);
                } else if(test.second.name == IFRF_STR_TEST_DO_CL_ANH) {
                    DoTestSelectImage(test.second);
                } else if(test.second.name == IFRF_STR_TEST_CL_F_M ) {
                    DoTestSelectInterFreq(test.second);
                } else if(test.second.name == IFRF_STR_TEST_DYN_LINEAR) {
                    DoTestDynLinear(test.second);
                } else if(test.second.name == IFRF_STR_TEST_BW_SIG_F_M) {
                    DoTestBwCenterFreq(test.second);
                } else if(test.second.name == IFRF_STR_TEST_SPUR) {
                    DoTestSpurious(test.second);
                } else if(test.second.name == IFRF_STR_TEST_IMD_IN_RANGE) {
                    DoTestImdInRange(test.second);
                } else if(test.second.name == IFRF_STR_TEST_IMD_OUT_RANGE ) {
                    DoTestImdOutRange(test.second);
//                } else if(test.second.name == IFRF_STR_TEST_OP_RANGE_JAM) {
//                    DoTestJamingRange(test.second);
                } else if(test.second.name == IFRF_STR_TEST_PWR_CONSUM) {
                    DoTestPowerConsume(test.second);
                }
                test.second.result.curPassed =
                        CheckTestCaseResult(test.second.result.listResult);
                currLineIdx++;

            }

            if(GetTestState() == TestState_Running) {
                if(checkTotalPassed()) {
                    SetPassed();
                } else {
                    if(m_ifrfConfig.reTestIfFailed) {
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


void TestIfrf::on_updateCellData(int row, int colum, QString data)
{
    updateCellContent(row, colum, data);
}

void TestIfrf::on_clearColumData(int colum, int numrow, int start)
{
    clearCellContentColum(colum, numrow, start);
}

void TestIfrf::on_updateUserSetting()
{
    GetUserConfig();
    SaveIfrfConfig();
    isSaveCfg = true;
}


void TestIfrf::on_btnStartTestClicked()
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
//        if(control->m_sigGenAgilent->getStatus() != communication::Event_Connected) {
//            QMessageBox::warning(this, "Lỗi", "Chưa kết nối máy signal generator !");
//            return;
//        }
//        if(control->m_spectFsv->getStatus() != communication::Event_Connected) {
//            QMessageBox::warning(this, "Lỗi", "Chưa kết nối máy spectrm analyzer !");
//            return;
//        }
//        if(!control->Dev_GetStatus()) {
//            QMessageBox::warning(this, "Lỗi", "Chưa kết nối cổng com !");
//            return;
//        }

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

void TestIfrf::on_btnConnectSpectClicked()
{
    ConfigController();
    if(control->Spect_GetStatus() == communication::Event_Connected ||
            control->Spect_GetStatus() == communication::Event_Connecting) {
        control->Spect_Stop();
    } else {
        control->Spect_Start();
    }
}

void TestIfrf::on_btnConnectSignalGenClicked()
{
    ConfigController();
    if(control->SigGen_GetStatus() == communication::Event_Connected ||
            control->SigGen_GetStatus() == communication::Event_Connecting) {
        LREP("USER Stop instr\r\n");
        control->SigGen_Stop();
    } else {
        LREP("USER Start instr\r\n");
        control->SigGen_Start();
    }
}

void TestIfrf::on_btnConnectSerialClicked()
{

    ConfigController();

    if(control->Dev_GetStatus()) {
        control->Dev_Stop();
        btnConnectSerial->setText("KẾT NỐI");
        comboSerialList->setEnabled(true);
        LREP("Disconnected\n");
    } else {
        LREP("Try to connect\n");
        control->Dev_Start();
    }
}



void TestIfrf::on_SiggenConnectEvent(int evt)
{
    if(evt == communication::Event_Connected) {
        labelInstrStatus->setStyleSheet("QLabel {color : green; }");
    }else {
        labelInstrStatus->setStyleSheet("QLabel {color : red; }");
    }
    switch(evt) {
        case communication::Event_Connected:
        LREP("Event Connected to siggen\r\n");
        btnConnectInstr->setText("NGẮT KẾT NỐI");
        labelInstrStatus->setText("ĐÃ KẾT NỐI");
        break;
    case communication::Event_Disconnected:
        LREP("Event Disconnected to siggen\r\n");
        btnConnectInstr->setText("KẾT NỐI");
        labelInstrStatus->setText("KHÔNG KẾT NỐI");
        SetTestState(TestState_Stop);
        EnableSettingPanel(true);
        break;
    case communication::Event_Connecting:
        LREP("Event siggen connecting\r\n");
        labelInstrStatus->setText("ĐANG THỬ KẾT NỐI");
        btnConnectInstr->setText("NGẮT KẾT NỐI");
        break;
    case communication::Event_Network_Down:
        LREP("Event Network Down to siggen\r\n");
        btnConnectInstr->setText("KẾT NỐI");
        labelInstrStatus->setText("KHÔNG KẾT NỐI");
        control->SigGen_Stop();
        SetTestState(TestState_Stop);
        EnableSettingPanel(true);
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy máy signal generator !");
        break;


    default:
        break;

    }
}

void TestIfrf::on_SpectConnectEvent(int evt)
{
    if(evt == communication::Event_Connected) {
        labelSpectStatus->setStyleSheet("QLabel {color : green; }");
    }else {
        labelSpectStatus->setStyleSheet("QLabel {color : red; }");
    }
    switch(evt) {
        case communication::Event_Connected:
        btnConnectSpect->setText("NGẮT KẾT NỐI");
        labelSpectStatus->setText("ĐÃ KẾT NỐI");
        break;
    case communication::Event_Disconnected:
        btnConnectSpect->setText("KẾT NỐI");
        labelSpectStatus->setText("KHÔNG KẾT NỐI");
        SetTestState(TestState_Stop);
        EnableSettingPanel(true);
        break;
    case communication::Event_Connecting:
        labelSpectStatus->setText("ĐANG THỬ KẾT NỐI");
        btnConnectSpect->setText("NGẮT KẾT NỐI");
        break;
    case communication::Event_Network_Down:
        btnConnectSpect->setText("KẾT NỐI");
        labelSpectStatus->setText("KHÔNG KẾT NỐI");
        control->Spect_Stop();
        SetTestState(TestState_Stop);
        EnableSettingPanel(true);
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy máy spectrum analyzer !");
        break;


    default:
        break;

    }
}

void TestIfrf::on_SpectRecvData(uint8_t *data, int len)
{
    uint8_t *rawdata = new uint8_t[len+1];

    memcpy(rawdata, data, len);
    rawdata[len] =  0;
    std::string datarecv((const char*)rawdata);
    LREP("Received: {}", datarecv);
    delete[] rawdata;
    MarkerPoint point;
    point.freq = currFreq;
    point.power = str::Util::convert<double>(datarecv, 0);

    m_listMarker.push_back(point);

    if(m_waitCode & Spect_Get_Center_Freq) {
        m_waitCode &= ~Spect_Get_Center_Freq;
    }

    if(m_waitCode & Spect_Get_ValueAt_Marker) {
        m_waitCode &= ~Spect_Get_ValueAt_Marker;
    }

    if(m_waitCode & Spect_Get_Harmonic_Distorion) {
        m_waitCode &= ~Spect_Get_Harmonic_Distorion;
    }

    if(m_waitCode & Spect_Get_Spurious) {
        m_waitCode &= ~Spect_Get_Spurious;
    }

}

void TestIfrf::on_selectComClicked(QString str)
{
    (void)str;

    QList<QSerialPortInfo> lst = QSerialPortInfo::availablePorts();    
    if(lst.count() != comboSerialList->count())
        comboSerialList->clear();

    foreach (const QSerialPortInfo &info, lst) {
        QString s = info.portName();
        if(FindText(s) == false)
            comboSerialList->addItem(s);
    }
}

void TestIfrf::on_IfrfConnectEvent(int evt)
{    
    switch(evt) {
        case communication::Event_Connected:
        LREP("Event Connected to Ifrf\r\n");
        btnConnectSerial->setText("NGẮT KẾT NỐI");
        break;
    case communication::Event_Disconnected:
        btnConnectSerial->setText("KẾT NỐI");
        SetTestState(TestState_Stop);
        EnableSettingPanel(true);
        QMessageBox::warning(this, "Lỗi", "Không mở được cổng \"" +
                             comboSerialList->currentText() + "\" cổng đang bận hoặc không có quyền!");
        break;

    default:
        break;

    }

}

void TestIfrf::on_IfrfRecvDataEvent(uint8_t *data, int len)
{
    LREP("recv ifrf data len: {}\n", len);
}

void TestIfrf::on_btnTestSendClicked()
{


//    LREP("control signal gen freq = {}\n", editSendCommand->text().toDouble())
//    //control->SigGen_InitDevice();
//    control->Dev_SetFreqency((uint64_t)(editSendCommand->text().toDouble() * 1E6), true);

//    control->SigGen_SetCombo(editSendCommand->text().toDouble(), Freq_Mhz, -60, Power_dBm,
//                            5.6, Freq_Khz, genConfig.siggenDelay);

//    control->Spect_StartCalculate();
}

void TestIfrf::on_btnTestSpectClicked()
{
    control->Spect_SendCommand(editRecvCommand->text().toStdString() + "\r\n");
    LREP("Sent spect command {}\n", editRecvCommand->text().toStdString());
}


void TestIfrf::on_btnPauseClicked()
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




void TestIfrf::StartAllTest(const QString &serial, const QString &who, bool createResult)
{    
    if(modeLoaded == "_THUONG") {
        StartTestSuite(TEMPLATE_IFRF_THUONG, serial, who);
    } else {
        StartTestSuite(TEMPLATE_IFRF_THUNGHIEM, serial, who);
    }


    if(createResult) {
        currLineResult = 20;
        for(auto &test : testHead) {
            resFile->write("B" + QString::number(currLineResult), test.second.name.c_str());
            if(test.second.name == IFRF_STR_TEST_SENSITIVE) {
                resFile->write("E" + QString::number(currLineResult), "≤ " + QString::number(test.second.input.max) + " dBm");

            } else if(test.second.name == IFRF_STR_TEST_IP3) {
                resFile->write("E" + QString::number(currLineResult), "≤ " + QString::number(test.second.input.max) + " dBm" );

            } else if(test.second.name == IFRF_STR_TEST_P1dB) {
                resFile->write("E" + QString::number(currLineResult), "± " + QString::number(test.second.input.max) + " dBm");

            } else if(test.second.name == IFRF_STR_TEST_DO_CL_ANH) {
                resFile->write("E" + QString::number(currLineResult), "± " + QString::number(test.second.input.max) + " %");

            } else if(test.second.name == IFRF_STR_TEST_CL_F_M) {
                resFile->write("E" + QString::number(currLineResult), "± " + QString::number(test.second.input.max) + " Hz");

            } else if(test.second.name == IFRF_STR_TEST_DYN_LINEAR) {
                resFile->write("E" + QString::number(currLineResult), "≤ " + QString::number(test.second.input.max) + " Hz");

            } else if(test.second.name == IFRF_STR_TEST_BW_SIG_F_M) {
                resFile->write("E" + QString::number(currLineResult), "≥ " + QString::number(test.second.input.max) + " dBm");

            }else if(test.second.name == IFRF_STR_TEST_SPUR) {
                resFile->write("E" + QString::number(currLineResult), "≤" + QString::number(test.second.input.max) + " %");

            }else if(test.second.name == IFRF_STR_TEST_IMD_IN_RANGE) {
                resFile->write("E" + QString::number(currLineResult), "≥ " + QString::number(test.second.input.max) + " dBm");

            }else if(test.second.name == IFRF_STR_TEST_IMD_OUT_RANGE) {
                resFile->write("E" + QString::number(currLineResult), "≥ " + QString::number(test.second.input.max) + " dBm");

            }else if(test.second.name == IFRF_STR_TEST_OP_RANGE_JAM) {
                resFile->write("E" + QString::number(currLineResult), "≥ " + QString::number(test.second.input.max) + " dBm");

            }else if(test.second.name == IFRF_STR_TEST_PWR_CONSUM) {
                resFile->write("E" + QString::number(currLineResult), "≥ " + QString::number(test.second.input.max) + " dBm");

            }

            currLineResult++;
            CreateResultLine(test.second);
        }
    }

    SetTestState(TestState_Running);

    EnableSettingPanel(false);
    btnStartTest->setText("DỪNG");
}

void TestIfrf::StopAllTest(bool save)
{
    StopTestSuite(save);
    labelTestPassNum->setText(QString::number(testTracker.testPass));
    labelTestRunNum->setText(QString::number(testTracker.testRun));
    control->SigGen_DeSetCombo();
    EnableSettingPanel(true);
}

bool TestIfrf::FindText(QString &s)
{
    for(int i = 0; i < comboSerialList->count(); i++) {
        if(comboSerialList->itemText(i) == s) {
            return true;
        }
    }
    return false;
}


bool TestIfrf::loadTestParam(const CSVFile::CsvVector &data)
{
    if(!data.size())
      return false;
    m_rows.clear();

    //LREP("Clear all test param before load the new !\n");
    clearAllParam();

    CSVFile::CsvVector::const_iterator iter;
    for(iter = data.begin(); iter != data.end(); ++iter){
        std::vector<std::string> row = *iter;
        if(SearchTestName(row.at(1)) && (row.size() >= 12)) {
            ComParam head;
            QString cont;
            head.name = row.at(1);
            head.enable = (row.at(2) == "TRUE" || row.at(2) == "true") ? true : false;
            head.input.min = str::Util::convert<double>(row.at(5), 0);
            head.input.max = str::Util::convert<double>(row.at(6), 0);            

            //if(head.enable && (std::abs(head.input.max) > std::abs(head.input.min))) {
            if(head.enable) {
                int order = cppframework::str::Util::convert<int>(row.at(3), 1);                
                head.input.ferr = str::Util::convert<int64_t>(row.at(11), 0);

                if((row.at(7) == "TRUE" || row.at(7) == "true")) {
                    double step = str::Util::convert<double>(row.at(10), 1);
                    double start = str::Util::convert<double>(row.at(8), 20);
                    double stop = str::Util::convert<double>(row.at(9), 100);

                    for(double idx = start; idx <= stop; idx += step) {
                        head.input.freqList.push_back(idx);
                    }
                    cont = "FREQ START: <" + QString::number(start, 'g', 10) +
                            " Mhz> - STEP: <" + QString::number(step, 'g', 10) +
                            " Mhz> - STOP: <" + QString::number(stop, 'g', 10) + " Mhz> ERR: "
                            + QString::number(head.input.ferr, 'g', 10) + " Hz";
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

    return true;
}



/**
 * @brief TestIfrf::on_btnSettingClicked
 */
void TestIfrf::on_btnSettingClicked()
{
    bool ok;

    QString text = QInputDialog::getText(this, "Admin access",
                                             "Issue password:", QLineEdit::Password,
                                             "", &ok);
    if (ok && !text.isEmpty()) {
        if(text == "1") {
            std::string          externalFile;
            if(comboTestMode->currentText() == "ĐIỀU KIỆN THƯỜNG") {
                externalFile = genConfig.inputDir + "/board/ifrf_thuong.csv";
            } else if(comboTestMode->currentText() == "NÓNG") {
                externalFile = genConfig.inputDir + "/board/ifrf_nong.csv";
            }else if(comboTestMode->currentText() == "LẠNH") {
                externalFile = genConfig.inputDir + "/board/ifrf_lanh.csv";
            }else if(comboTestMode->currentText() == "MÔI TRƯỜNG") {
                externalFile = genConfig.inputDir + "/board/ifrf_moitruong.csv";
            }else if(comboTestMode->currentText() == "LÃO HÓA") {
                externalFile = genConfig.inputDir + "/board/ifrf_laohoa.csv";
            }else if(comboTestMode->currentText() == "RUNG SÓC VA ĐẬP") {
                externalFile = genConfig.inputDir + "/board/ifrf_rungsocvadap.csv";
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
void TestIfrf::on_btnLoadTestParamClicked()
{
    disconnect(btnLoadTestParam, SIGNAL(clicked(bool)), this, SLOT(on_btnLoadTestParamClicked()));
    LoadTestConfigFromFile();
    connect(btnLoadTestParam, SIGNAL(clicked(bool)), this, SLOT(on_btnLoadTestParamClicked()));
    isTestParmLoaded = true;
}

/*
 *
 *
 *
*/
void TestIfrf::LoadTestConfigFromFile()
{
    std::string          externalFile;
    if(comboTestMode->currentText() == "ĐIỀU KIỆN THƯỜNG") {
        externalFile = genConfig.inputDir + ("/board/ifrf_thuong.csv");
        labelHeader->setText("ĐO KIỂM TỰ ĐỘNG CHỈ TIÊU IFRF - THƯỜNG");
        modeLoaded = "_THUONG";
    } else if(comboTestMode->currentText() == "NÓNG") {
        externalFile = genConfig.inputDir + ("/board/ifrf_nong.csv");
        labelHeader->setText("ĐO KIỂM TỰ ĐỘNG CHỈ TIÊU IFRF - NÓNG");
        modeLoaded = "_NONG";
    }else if(comboTestMode->currentText() == "LẠNH") {
        externalFile = genConfig.inputDir + ("/board/ifrf_lanh.csv");
        labelHeader->setText("ĐO KIỂM TỰ ĐỘNG CHỈ TIÊU IFRF - LẠNH");
        modeLoaded = "_LANH";
    }else if(comboTestMode->currentText() == "MÔI TRƯỜNG") {
        externalFile = genConfig.inputDir + ("/board/ifrf_moitruong.csv");
        labelHeader->setText("ĐO KIỂM TỰ ĐỘNG CHỈ TIÊU IFRF - MÔI TRƯỜNG");
        modeLoaded = "_MOITRUONG";
    }else if(comboTestMode->currentText() == "LÃO HÓA") {
        externalFile = genConfig.inputDir + ("/board/ifrf_laohoa.csv");
        labelHeader->setText("ĐO KIỂM TỰ ĐỘNG CHỈ TIÊU IFRF - LÃO HÓA");
        modeLoaded = "_LAOHOA";
    }else if(comboTestMode->currentText() == "RUNG SÓC VA ĐẬP") {
        externalFile = genConfig.inputDir + ("/board/ifrf_rungsocvadap.csv");
        labelHeader->setText("ĐO KIỂM TỰ ĐỘNG CHỈ TIÊU IFRF - RUNG SÓC VA ĐẬP");
        modeLoaded = "_RUNGSOCVADAP";
    }

    model->clear();
    createTableViewHeader();
    if(loadTestConfig(externalFile)) {
        loadTestParam(loader->rows());
        loadTestParamToUi();
    } else {

    }
    loader.reset();
}

void TestIfrf::LoadIfrfConfig()
{
    m_ifrfConfig = UiConfig::getInstance()->getIfrfConfig();
}

void TestIfrf::SaveIfrfConfig()
{
    UiConfig::getInstance()->saveIfrfKeepTestIfFailed(m_ifrfConfig.keepTestIfFaled);
    UiConfig::getInstance()->saveIfrfReTestIfFailed(m_ifrfConfig.reTestIfFailed);
    UiConfig::getInstance()->saveIfrfSigGenIp(m_ifrfConfig.SigGenIp);
    UiConfig::getInstance()->saveIfrfSigGenPort(m_ifrfConfig.siggenPort);
    UiConfig::getInstance()->saveIfrfSpectIp(m_ifrfConfig.spectIp);
    UiConfig::getInstance()->saveIfrfSpectPort(m_ifrfConfig.spectPort);
}

void TestIfrf::PrintTestParamAll()
{

}


void TestIfrf::ConfigController()
{
    control->disconnectAllConnection();
    control->addConnection(connect(control, SIGNAL(sigSigGenStatus(int)), SLOT(on_SiggenConnectEvent(int))));
    control->addConnection(connect(control, SIGNAL(sigSpectRecvData(uint8_t*,int)), SLOT(on_SpectRecvData(uint8_t*,int))));
    control->addConnection(connect(control, SIGNAL(sigSpectStatus(int)), SLOT(on_SpectConnectEvent(int))));
    control->addConnection(connect(control, SIGNAL(sigSerialDevStatus(int)), SLOT(on_IfrfConnectEvent(int))));
    control->addConnection(connect(control, SIGNAL(sigSerialDevRecvData(uint8_t*,int)), SLOT(on_IfrfRecvDataEvent(uint8_t*,int))));
    if(control) {
        control->ConfigIsc(comboSerialList->currentText().toStdString(), 115200);
        control->ConfigSigGen(m_ifrfConfig.SigGenIp, m_ifrfConfig.siggenPort);
        control->ConfigSpectrum(m_ifrfConfig.spectIp, m_ifrfConfig.spectPort);
    }
}

void TestIfrf::EnableSettingPanel(bool en)
{
    btnConnectInstr->setEnabled(en);
    btnConnectSpect->setEnabled(en);
    btnLoadTestParam->setEnabled(en);
    btnTestCaseSetting->setEnabled(en);
    //btnConnectSerial->setEnabled(en);
    editSerial->setEnabled(en);
}


void TestIfrf::PrintGeneralConfig()
{
    LREP("keep test: {}\n",         m_ifrfConfig.keepTestIfFaled);
    LREP("auto open result: {}\n",  m_ifrfConfig.reTestIfFailed);
    LREP("spectrum ip: {}\n",       m_ifrfConfig.spectIp);
    LREP("spectrum port: {}\n",     m_ifrfConfig.spectPort);
    LREP("instr ip: {}\n",          m_ifrfConfig.SigGenIp);
    LREP("instr port: {}\n",        m_ifrfConfig.siggenPort);
}



void TestIfrf::GetUserConfig()
{
    m_ifrfConfig.keepTestIfFaled = checkKeepTest->isChecked();
    m_ifrfConfig.reTestIfFailed = checkRetestIfFailed->isChecked();
    m_ifrfConfig.SigGenIp = editInstrIp->text().toStdString();
    m_ifrfConfig.siggenPort = editInstrPort->text().toUShort();
    m_ifrfConfig.spectIp = editSpectIp->text().toStdString();
    m_ifrfConfig.spectPort = editSpectPort->text().toUShort();
}

double TestIfrf::ConvertToImageFreq(double freq)
{
    double midFreq, imgFreq;
    if(freq < 1800) {
        midFreq = 2441;
    } else {
        midFreq = 1950;
    }

    imgFreq = 2 * midFreq + freq;

    return imgFreq;
}

double TestIfrf::ConvertToInterFreq(double freq)
{
    double midFreq;
    if(freq < 1800) {
        midFreq = 2441;
    } else {
        midFreq = 1950;
    }

    return midFreq;
}


double TestIfrf::Spect_CheckPowerOfFreq(double freq, uint64_t err)
{
    double ret;
    if(control->Spect_GetValueAtPoint(freq, ret)) {
        return ret;
    } else {
        return 0;
    }        
}

double TestIfrf::Spect_CheckFreqAtPower(double power, double perr)
{
    for(auto s : m_listMarker) {
        if(std::abs(s.power - power) < perr) {
            return s.freq;
        }
    }
    return 0;
}
