#include "testbase.h"

using namespace cppframework;


TestBase::TestBase(QWidget *parent) :
    QWidget(parent)
{
    resFile = NULL;
    doTestSuiteTerm = true;
    testState = TestState_Stop;
    currLineIdx = 0;
    totalResIdx = 0;
    isTestParmLoaded = false;
    doTestSuiteTerm = false;
    currLineResult = 0;
    loader = nullptr;
    control = nullptr;
    model = new QStandardItemModel();
}

TestBase::TestBase(Controller *controller, QWidget *parent) :
    QWidget(parent)
{
    control = controller;
    resFile = NULL;
    doTestSuiteTerm = true;
    testState = TestState_Stop;
    currLineIdx = 0;
    totalResIdx = 0;
    isTestParmLoaded = false;
    doTestSuiteTerm = false;
    currLineResult = 0;
    loader = nullptr;
    model = new QStandardItemModel();

    LoadGenConfig();
    testTracker.resultPath = QString(genConfig.outputDir.c_str());
    testTracker.templatePath = QString(genConfig.inputDir.c_str()) + "/template/";

    modeLoaded = "";
    outputFileName = "";

    createConnection();
}

TestBase::~TestBase()
{    
    SetTestState(TestState_RequestStop);
    stopTestFrame();
}

void TestBase::SetController(Controller* controller)
{
    control = controller;
}

QString TestBase::GetCurrentTimeToString()
{
    QDate cd  = QDate::currentDate();
    QTime ct = QTime::currentTime();

    QString time;
    time = QString::number(cd.year()) + "." + QString::number(cd.month()) + "." + QString::number(cd.day()) + "_" +
            QString::number(ct.hour()) + "." + QString::number(ct.minute()) + "." + QString::number(ct.second()) + "_";

    return time;
}

void TestBase::LoadGenConfig()
{
    genConfig = UiConfig::getInstance()->getGeneralConfig();
}

void TestBase::createConnection()
{
    connect(this, SIGNAL(showQuesDialog()), this, SLOT(on_ShowQuestionBox()));
    connect(this, SIGNAL(sigLoadRetestParamToUi()), this, SLOT(on_loadRetestParamToUi()));
    connect(this, SIGNAL(showInputDialog(QString)), this, SLOT(on_showInputDialog(QString)));
    /**
     * @brief test result update
     */
    connect(this, SIGNAL(updateCellData(int,int,QString)), this, SLOT(on_updateCellData(int,int,QString)));
    connect(this, SIGNAL(clearColumData(int,int,int)), this, SLOT(on_clearColumData(int,int,int)));

    connect(this, SIGNAL(showInfoDialog(QString)), this, SLOT(on_showInfoDialog(QString)));

}

void TestBase::addTestCase(int order, ComParam &test)
{
    testHead[order] = test;
}

void TestBase::clearAllParam()
{    
    for(auto &elem : testHead) {
        elem.second.input.freqList.clear();
        elem.second.result.listResult.clear();
    }
    testHead.clear();
}

void TestBase::clearAllResultAndFailed()
{
    for(auto &elem : testHead) {
        elem.second.result.listResult.clear();
        elem.second.input.failFreqList.clear();
        elem.second.result.curPassed = false;
        elem.second.result.hasValue = false;
    }
}

void TestBase::clearAllResult()
{
    for(auto &elem : testHead) {
        elem.second.result.listResult.clear();
        //elem.second.result.curPassed = false;
    }
}



bool TestBase::getInputParamById(int id, TestBase::ComParam &inputParam)
{
    for(auto &var : testHead) {
        if(var.first == id) {
            inputParam = var.second;
            return true;
        }
    }

    return false;
}

bool TestBase::setPassFaildByName(const std::string &name, bool pass)
{    
    for(auto &elem : testHead) {
        if(elem.second.name == name) {
            elem.second.result.hasValue = true;
            elem.second.result.curPassed = pass;
            return true;
        }
    }
    return false;
}


bool TestBase::getPassFaildByName(const string &name)
{
    for(auto &elem : testHead) {
        if(elem.second.name == name) {
            return elem.second.result.curPassed;
        }
    }
    return false;
}

bool TestBase::setBoardResponseByName(const string &name, bool res)
{
    for(auto &elem : testHead) {
        if(elem.second.name == name) {
            elem.second.result.hasValue = res;
            return true;
        }
    }
    return false;
}

bool TestBase::getBoardResponseByName(const string &name)
{
    for(auto &elem : testHead) {
        if(elem.second.name == name) {
            return elem.second.result.hasValue;
        }
    }
    return false;
}

bool TestBase::checkTotalPassed()
{
    for(auto &elem : testHead) {
        if(elem.second.result.curPassed == false) {
            return false;
        }
    }
    return true;
}


bool TestBase::getInputParamByName(std::string &testName, ComParam &inputParam)
{  
    for(auto &var : testHead) {
        if(var.second.name == testName) {
            inputParam = var.second;
            return true;
        }
    }
    return false;
}



void TestBase::convertVectStrToDouble(string str, std::vector<double> &data)
{
    std::vector<std::string> vect;
    str::Util::split(str, "-", vect);
    for(size_t i = 0; i < vect.size(); i++) {
        data.push_back(str::Util::convert<double>(vect.at(i), 0.0));
    }
}


bool TestBase::loadTestConfig(std::string &cfgFile)
{
    filepathTestInput = cfgFile;
    loader = std::make_shared<CSVFile>(filepathTestInput);
    int err = loader->open();
    if(err == 0) {
        if(loader->get_count()) {
            //loader->displayall();
            //CSVFile::CsvVector data = loader->rows();
        }
        return true;
    } else {
        return false;
    }
}

void TestBase::LoadTestTracker()
{
    std::ofstream savefile;
    std::ifstream loadfile;
    loadfile.open(testTrackerFile, std::ios::in);

    if(!loadfile.good()) {
        LREP("create new test tracker\r\n");
        savefile.open(testTrackerFile, std::ios::out);
        if(savefile.good()) {
            LREP("init test tracker\n");
            testTracker.testPass = 0; testTracker.testRun = 0;
            savefile.write(reinterpret_cast<char*>(&testTracker.testRun), sizeof(uint32_t));
            savefile.write(reinterpret_cast<char*>(&testTracker.testPass), sizeof(uint32_t));
            savefile.close();
        } else {
            ASSERT(false);
        }
    } else {
        //std::string::size_type len;
        //LREP("load test tracker\r\n");
        loadfile.seekg(0);
        loadfile.read(reinterpret_cast<char*>(&testTracker.testRun), sizeof(uint32_t));
        loadfile.read(reinterpret_cast<char*>(&testTracker.testPass), sizeof(uint32_t));
        LREP("RUN: {} - PASS {}\r\n", testTracker.testRun, testTracker.testPass);
        loadfile.close();
    }
}

void TestBase::SaveTestTracker()
{

    std::ofstream savefile;
    savefile.open(testTrackerFile, std::ios::out);
    if(savefile.good()) {
        LREP("save test tracker\r\n");
        savefile.write(reinterpret_cast<char*>(&testTracker.testRun), sizeof(uint32_t));
        savefile.write(reinterpret_cast<char*>(&testTracker.testPass), sizeof(uint32_t));
        savefile.close();
    }
}


void TestBase::SetTestState(TestState state) {
    testStateMutex.lock();
    testState = state;
    testStateMutex.unlock();
}


void TestBase::stopTestFrame()
{
    doTestSuiteTerm = true;
    if(doTestSuiteThread.joinable())
        doTestSuiteThread.join();
}

void TestBase::startTestFrame()
{
    doTestSuiteTerm = false;
    doTestSuiteThread = std::thread([this] (){
        DoTestSuiteFunction();
    });
}

void TestBase::CreateNewResultFile(const QString &templateFile, const QString &serial, const QString &who, bool writeTemplate)
{    
    resFile = new QXlsx::Document(testTracker.templatePath + templateFile);
    if(resFile == NULL) {
        ASSERT(false);
        return;
    }
    WriteTestInfo(serial, who);    
}


void TestBase::CreateNewResultFileFullPath(const QString &templateFile, const QString &serial, const QString &who, bool writeTemplate)
{
    resFile = new QXlsx::Document(templateFile);
    if(resFile == NULL) {
        ASSERT(false);
        return;
    }
    WriteTestInfo(serial, who);
}



void TestBase::SaveResultToFile()
{
    QDate cd = QDate::currentDate();
    QString currDate =   QString::number(cd.year())  + "." + QString::number(cd.month()) + "."  + QString::number(cd.day());

    QString outDir = testTracker.resultPath + "/" + currDate;
    QDir dir(outDir);
    if(!dir.exists()) {
        dir.mkpath(".");
    }

    QString time = GetCurrentTimeToString();

    QString filename = time + outputFileName;
    QString filename_fullpath = outDir + "/" + filename + modeLoaded + totalTestRes + ".xlsx";
    outputFileNameFullPath = filename_fullpath;
    //qDebug() << "save to file: " << outputFileNameFullPath;
    if(resFile) {
        resFile->saveAs(filename_fullpath);
    }else {
        ASSERT(false);
    }

    delete resFile;
    resFile = NULL;
}

void TestBase::WriteTestInfo(const QString &serial,const QString &name)
{
    if(!resFile)
        return;
    QDate cd = QDate::currentDate();
    QString currDate =  QString::number(cd.day()) + "-" + QString::number(cd.month()) + "-"  + QString::number(cd.year());
    resFile->write("G8", serial);
    resFile->write("D12", currDate);
    resFile->write("D13", name);
}

void TestBase::WriteRowResult(double value, const QString &result)
{
    if(!resFile)
        return;

    resFile->write("F" + QString::number(currLineResult), value);
    resFile->write("G" + QString::number(currLineResult), result);
    LREP("Write result ON: {}\n", currLineResult);
    currLineResult++;
}

void TestBase::WriteRowResult(const QString &info, const QString &result)
{
    if(!resFile)
        return;

    resFile->write("F" + QString::number(currLineResult), info);
    resFile->write("G" + QString::number(currLineResult), result);
    currLineResult++;
}

void TestBase::WriteTotalResult(const QString &result)
{
    if(!resFile)
        return;
    resFile->write("D14", result);
}


void TestBase::updateCellContent(int row, int colum, const QString &data) {
    model->setData(model->index(row, colum), data, Qt::EditRole);
    if(data.contains("PASSED", Qt::CaseInsensitive)) {
        model->setData(model->index(row, colum), QColor(Qt::darkGreen), Qt::BackgroundColorRole);
        //model->setData(model->index(row, colum), QColor(Qt::white), Qt::TextColorRole);
    } else if (data.contains("FAILED", Qt::CaseInsensitive)) {
        model->setData(model->index(row, colum), QColor(Qt::darkRed), Qt::BackgroundColorRole);
        //model->setData(model->index(row, colum), QColor(Qt::white), Qt::TextColorRole);
    } else if (data.contains("TESTING", Qt::CaseInsensitive)) {
        //model->setData(model->index(row, colum), QColor(Qt::lightGray), Qt::BackgroundColorRole);
        //model->setData(model->index(row, colum), QColor(QColor(47, 47, 47)), Qt::TextColorRole);
    } else {
        model->setData(model->index(row, colum), QColor(81,81,81), Qt::BackgroundColorRole);
        //model->setData(model->index(row, colum), QColor(Qt::white), Qt::TextColorRole);
    }
}

TestBase::TestState TestBase::GetTestState() {
    TestState state;
    testStateMutex.lock();
    state = testState;
    testStateMutex.unlock();
    return state;
}

bool TestBase::IsKeepgoingOnTest()
{
    if(GetTestState() == TestState_Running ||
            GetTestState() == TestState_Pause)
        return true;
    return false;
}


void TestBase::clearCellContentColum(int colum, int numrow, int start) {
    if(numrow <= 0 || numrow <= start) {
        return;
    }

    for(int i = start; i < numrow; i++) {
        updateCellContent(i, colum, " ");
    }

}

void TestBase::DoTestSuiteFunction()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void TestBase::createTableViewHeader()
{

}

void TestBase::TestSuiteDelay(uint32_t millisecond)
{
    uint32_t delay = millisecond / 100;
    while(GetTestState() == TestState_Running && (delay--)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


void TestBase::PauseTest() {
    while(GetTestState() == TestState_Pause) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

QString TestBase::InsertDot(uint64_t value)
{
    QString result = "";
    int count  = 0;
    while(value > 0) {
        if(count > 0 && count %3 == 0) result = "," + result;
        count++;
        result = QString::number(value % 10) + result;
        value /= 10;
    }
    return result;
}

bool TestBase::SearchTestName(string &name)
{
    for(auto str : m_listTestName) {
        if(str == name)
            return true;
    }
    return false;
}

uint32_t TestBase::GetLineWithFreqFailed(std::vector<TestBase::FailPoint> &list, double freq)
{
    for(auto var: list) {
        if(var.freq == freq) {
            return var.writeLine;
        }
    }
    return 0;
}


void TestBase::on_updateCellData(int row, int colum, QString data)
{
    updateCellContent(row, colum, data);
}

void TestBase::on_clearColumData(int colum, int numrow, int start)
{
    clearCellContentColum(colum, numrow, start);
}

void TestBase::on_ShowQuestionBox()
{
    QMessageBox::StandardButton answer = QMessageBox::question(
        this,
        tr("TEST FAILED"),
        tr("Bạn muốn chạy lại những điểm không đạt ?"),
        QMessageBox::Yes | QMessageBox::No
    );

    if(answer == QMessageBox::Yes) {
        userAct = User_Select_Yes;
    } else {
        userAct = User_Select_No;
    }
}

void TestBase::on_loadRetestParamToUi()
{
    loadRetestParamToUi();
}

void TestBase::on_showInputDialog(QString cont)
{
    m_value = QInputDialog::getDouble(this, "Nhập giá trị", cont, 1.0, INT32_MIN, INT32_MAX, 4);
    LREP("CONFIRM\n");
    m_confirm = true;
}

void TestBase::on_showInfoDialog(QString cont)
{
    QMessageBox::information(this, "Thông báo", cont);
    m_confirmInfo = true;
}


bool TestBase::CheckTestCaseResult(std::vector<TestPoint> &result)
{
    for(auto var : result) {
        if(!var.passed)
            return false;
    }
    return true;
}

void TestBase::StartTestSuite(const QString fileName, const QString serial, const QString who, bool writeTemplate)
{
    if(fileName != "") {
        CreateNewResultFile(fileName, serial, who, writeTemplate);
    }
    //SetTestState(TestState_Running);
    SetTestProgress(Progress_First_Time);
    testTracker.testRun++;
}

void TestBase::StopTestSuite(bool saveResult)
{
    SetTestState(TestState_Stop);
    if(saveResult) {
        SaveResultToFile();
        SaveTestTracker();
    }
}


void TestBase::SaveResultForContinueTest(const QString serial, const QString who) {
    totalTestRes = "_FALSE";
    SaveResultToFile();
    SaveTestTracker();
    CreateNewResultFileFullPath(outputFileNameFullPath, serial, who);
}

void TestBase::displayPassedCase(int index)
{
    emit updateCellData(index, STATUS_IN_COLUM, "PASSED");
}

void TestBase::displayFailedCase(int index)
{
    emit updateCellData(index, STATUS_IN_COLUM, "FAILED");
}


void TestBase::AppendRowTable(QStringList &row)
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


void TestBase::loadTestParamToUi()
{
    model->clear();
    createTableViewHeader();

    foreach (QStringList row, m_rows) {

        QList<QStandardItem *> items;

        QStringList::iterator iter = row.begin();
        QString text = *iter;
        QStandardItem *item = new QStandardItem(text);
        items.append(item);
        iter++;
        int i = 1;
        while(iter != row.end()) {
            QString text = *iter;
            QStandardItem *item = new QStandardItem(text);
            if(i++ != 5)
                item->setTextAlignment(Qt::AlignCenter);

            items.append(item);
            iter++;
        }

        model->appendRow(items);
    }

    QStringList res;
    res << "TOÀN BỘ" << " ";
    AppendRowTable(res);
    totalResIdx = m_rows.size();
    LREP("TOTAL RES INDEX: {}\n", totalResIdx);
}

void TestBase::loadRetestParamToUi()
{
    m_rows.clear();
    model->clear();

    createTableViewHeader();

    for(auto &test : testHead) {
        if(!test.second.result.curPassed) {
            QString cont = "KIỂM TRA LẠI CÁC ĐIỂM KHÔNG ĐẠT";
            m_rows << (QStringList() << QString(test.second.name.c_str()).toUpper() << " " << " " << " " << " " << cont);

            for(auto var : test.second.input.failFreqList) {

                m_rows << (QStringList() << "Freq: " + QString::number(var.freq, 'g', 10) + " Mhz" << " " << " " <<
                         QString::number(test.second.input.min) <<
                         QString::number(test.second.input.max));
            }
        }
    }

    foreach (QStringList row, m_rows) {
        QList<QStandardItem *> items;
        QStringList::iterator iter = row.begin();
        QString text = *iter;
        QStandardItem *item = new QStandardItem(text);
        items.append(item);
        iter++;
        int i = 1;
        while(iter != row.end()) {
            QString text = *iter;
            QStandardItem *item = new QStandardItem(text);
            if(i++ != 5)
                item->setTextAlignment(Qt::AlignCenter);

            items.append(item);
            iter++;
        }

        model->appendRow(items);
    }

    QStringList res;
    res << "TOÀN BỘ" << " ";
    AppendRowTable(res);

    totalResIdx = m_rows.size();
}

void TestBase::CreateResultLine(ComParam &param)
{
    for(auto var : param.input.freqList) {
        resFile->write("D" + QString::number(currLineResult), QString::number(var, 'g', 10) + " Mhz");
        //LREP("{}-{}\t", currLineResult, var);
        currLineResult++;
    }
}


void TestBase::displayAndWriteResultRow(TestPoint tp, bool passed)
{
    QString num = QString::number(tp.point, 'g', 10);
    double value = tp.value;
    if(passed) {
        emit updateCellData(currLineIdx, STATUS_IN_COLUM,  "FREQ " + num + " MHz PASSED");
        WriteRowResult(value ,"PASSED");
    } else {
        emit updateCellData(currLineIdx, STATUS_IN_COLUM,  "FREQ " + num + " MHz FAILED");
        WriteRowResult(value ,"FAILED");
    }
}

void TestBase::displayAndWriteResultRow(TestBase::TestPoint tp, QString info)
{
    QString num = QString::number(tp.point, 'g', 10);
    emit updateCellData(currLineIdx, STATUS_IN_COLUM,  "FREQ " + num + " MHz FAILED");
    WriteRowResult(info ,"FAILED");
}

void TestBase::displayAndWriteResultRow(TestPoint tp, bool passed, double pwrvalue)
{
    QString num = QString::number(tp.point, 'g', 10);
    //QString value = QString::number(tp.value, 'g', 10);
    double value = tp.value;
    if(passed) {
        emit updateCellData(currLineIdx, STATUS_IN_COLUM,  "READ " + QString::number(pwrvalue, 'g', 10) + " PASSED");
        WriteRowResult(value ,"PASSED");
    } else {
        emit updateCellData(currLineIdx, STATUS_IN_COLUM,  "READ " + QString::number(pwrvalue, 'g', 10) + " FAILED");
        WriteRowResult(value ,"FAILED");
    }
}

void TestBase::displayValueOfFreq(double val)
{
    emit updateCellData(currLineIdx++, VALUE_IN_COLUM, QString::number(val, 'g', 10));
}
void TestBase::displayValueOfFreq(QString val)
{
    emit updateCellData(currLineIdx++, VALUE_IN_COLUM, val);
}



void TestBase::SetPassed(bool save)
{
    testTracker.testPass++; // should call this line before StopTestSuite();
    totalTestRes = "_PASS";
    LREP("TOTAL TEST PASSED\n");
    WriteTotalResult("PASSED");
    StopTestSuite(save);
    emit updateCellData(totalResIdx, STATUS_IN_COLUM, "PASSED");
}

void TestBase::SetFailed(bool save)
{
    totalTestRes = "_FAIL";
    LREP("TOTAL TEST FAILED\n");
    WriteTotalResult("FAILED");
    StopTestSuite(save);
    emit updateCellData(totalResIdx, STATUS_IN_COLUM, "FAILED");
}
