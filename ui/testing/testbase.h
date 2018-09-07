#ifndef TESTBASE_H
#define TESTBASE_H

#include <thread>
#include <mutex>
#include "testconfig.h"
#include "xlsx/xlsxdocument.h"
#include "csv/csvfile.h"
#include "network/controller.h"
#include <QObject>
#include <QDate>
#include <QDir>
#include <QStandardItemModel>
#include <QWidget>
#include <QtWidgets>
#include <configuration/uiconfig.h>


class TestBase : public QWidget
{

Q_OBJECT
public:

    struct TestPoint {
        double point;
        double value;
        bool   passed;
    };

    struct FailPoint {
        double      freq;
        uint32_t    displayLine;
        uint32_t    writeLine;
    };

    struct InputParam{
        std::vector<double> freqList;
        std::vector<FailPoint> failFreqList;
        std::vector<FailPoint> reTestingList;
        std::vector<double> freqTestList;
        double           min;
        double           max;
        int64_t          ferr;
        double           gain;
        double           noisefloor;
        bool             changeMiss;
    };

    struct OutputResult {
        bool    hasValue;
        double  currValue;
        bool    curPassed;
        std::vector<TestPoint> listResult;
    };

    struct ComParam {
        std::string   name;
        bool          enable;
        InputParam    input;
        OutputResult  result;
    };

    struct TestTracker{
        uint32_t    testRun;
        uint32_t    testPass;
        QString templatePath;
        QString resultPath;
    };

    enum TestState {
        TestState_Running,
        TestState_RequestStop,
        TestState_Pause,
        TestState_Stop,        
    };

    enum TestProgress {
        Progress_First_Time,
        Progress_Retest_Failed_Point,
    };

    enum WaitUserSelect {
        User_Wait_Select,
        User_Select_No,
        User_Select_Yes,
    };

    explicit TestBase(QWidget *parent = 0);
     TestBase(Controller *controller, QWidget *parent = 0);
    ~TestBase();

    void SetController(Controller *controller);

    QString GetCurrentTimeToString();

    void LoadGenConfig();
    void SaveGenConfig();
    void createConnection();
    void addTestCase(int order, ComParam &test);
    void clearAllParam();
    void clearAllResult();
    void clearAllResultAndFailed();
    void clearResultList(ComParam &param);
    bool getInputParamByName(std::string &testName, ComParam &inputParam);
    bool getInputParamById(int id,  ComParam &inputParam);    
    bool setPassFaildByName(const std::string &name, bool pass);
    bool getPassFaildByName(const std::string &name);
    bool setBoardResponseByName(const std::string &name, bool res);
    bool getBoardResponseByName(const std::string &name);
    bool checkTotalPassed();    
    void convertVectStrToDouble(std::string str, std::vector<double> &data);
    bool loadTestConfig(string &cfgFile);
    void LoadTestTracker();
    void SaveTestTracker();
    void SaveResultToFile();
    void CreateNewResultFile(const QString &templateFile, const QString &serial, const QString &who, bool writeTemplate = false);
    void CreateNewResultFileFullPath(const QString &templateFile, const QString &serial, const QString &who, bool writeTemplate = false);
    void WriteTestInfo(const QString &serial, const QString &name);
    void WriteRowResult(double value, const QString &result);
    void WriteRowResult(const QString &info, const QString &result);
    void WriteTotalResult(const QString &result);
    void writeTestValue(QString value, QString result);
    bool CheckTestCaseResult(std::vector<TestPoint> &result);
    void displayPassedCase(int index);
    void displayFailedCase(int index);
    void SetTestState(TestState state);
    void StartTestSuite(const QString fileName, const QString serial, const QString who, bool writeTemplate = false);
    void StopTestSuite(bool saveResult = true);    
    void SaveResultForContinueTest(const QString serial, const QString who);
    void startTestFrame();
    void stopTestFrame();
    TestProgress GetTestProgress() {return testProg;}
    void SetTestProgress(TestProgress prog) {testProg = prog;}
    TestState GetTestState();
    bool IsKeepgoingOnTest();
    void updateCellContent(int row, int colum, const QString &data);
    void clearCellContentColum(int colum, int numrow, int start = 0);
    virtual void DoTestSuiteFunction();
    virtual void createTableViewHeader();
    void TestSuiteDelay(uint32_t millisecond);
    void AppendRowTable(QStringList &row);
    void loadTestParamToUi();
    void loadRetestParamToUi();
    void PauseTest();
    void CreateResultLine(ComParam &param);
    QString InsertDot(uint64_t value);
    bool    SearchTestName(std::string &name);
    uint32_t GetLineWithFreqFailed(std::vector<FailPoint> &list, double freq);


    void displayAndWriteResultRow(TestPoint tp, bool passed);
    void displayAndWriteResultRow(TestPoint tp, QString info);
    void displayAndWriteResultRow(TestPoint tp, bool passed, double value);
    void displayValueOfFreq(double val);
    void displayValueOfFreq(QString val);

    void SetPassed(bool save = true);
    void SetFailed(bool save = true);

public:

    /* Test state, param */
    QList<QStringList> m_rows; // For load data to UI
    QString         totalTestRes;
    int             currLineIdx;
    int             totalResIdx;
    bool            isTestParmLoaded;
    bool            doTestSuiteTerm;
    int             currLineResult;
    QString         modeLoaded;
    std::string     testTrackerFile;
    WaitUserSelect  userAct;
    /* Network controller */
    Controller      *control;
    TestTracker     testTracker;

    /* xlsx element */
    QXlsx::Document *resFile;
    QString         outputFileName;
    QString         outputFileNameFullPath;

    /* Test input */
    std::map<int, ComParam>     testHead;
    std::shared_ptr<CSVFile> loader;
    std::list<std::string> m_listTestName;

    /* UI control element */
    QStandardItemModel *model;
    GeneralConfig   genConfig;
    QLabel          *labelTestPassNum, *labelTestRunNum;
    double          m_value;
    bool            m_confirm;
    bool            m_confirmInfo;

signals:
    void updateCellData(int row, int colum, QString data);
    void clearColumData(int colum, int numrow, int start = 0);
    void updateStatusBar(QString cont, QColor color = QColor(Qt::white));
    void showQuesDialog();
    void sigLoadRetestParamToUi();
    void showInputDialog(QString cont);
    void showInfoDialog(QString cont);
    void setSerialNumber(QString serial);

public slots:
    void on_updateCellData(int row, int colum, QString data);
    void on_clearColumData(int colum, int numrow, int start);
    void on_ShowQuestionBox();
    void on_loadRetestParamToUi();
    void on_showInputDialog(QString cont);
    void on_showInfoDialog(QString cont);

private:
    TestState       testState;
    std::mutex      testStateMutex;
    TestProgress    testProg;
    std::string     filepathTestInput;
    std::thread     doTestSuiteThread;
};

#endif // TESTBASE_H
