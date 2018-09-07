#ifndef CALIBSENSOR_H
#define CALIBSENSOR_H


#include <thread>
#include <mutex>
#include <cstdlib>
#include "testing/testbase.h"


//#define CALIB_RESET_VAL                   true    // For test
#define CALIB_RESET_VAL                 false   // For run


#define FREQ_START_FREQ             20.0f
#define FREQ_END_FREQ               3000.0f

class CalibSensor : public TestBase
{

    struct CalibParam{
        double           power;
        double           step;
    };

    struct TestParam {
        struct CalibParam       line1;
        struct CalibParam       line2;
        struct CalibParam       line3;
    };

    struct TestResult {
        std::list<FreqPoint> calibResult;
    };

    Q_OBJECT
public:
    explicit CalibSensor(Controller *controller, TestBase *parent = 0);
    ~CalibSensor();

    void initVariable();
    void createUiElem();
    void createLayout();
    void createElemContent();
    void createTableViewHeader();
    void createConnection();
    void loadTestParamToUi();

    void ConfigController();
    void EnableSettingPanel(bool en);
    /********************************************/

    bool loadTestParam(const CSVFile::CsvVector &data);
    bool LoadTestConfigFromFile();

    void clearInputParam();
    /********************************************/    
    void displayNA(double genPower, uint64_t genFreq);
    void displayLineValue(double genPower, uint64_t genFreq, float recPower, uint64_t recFreq);

    void InitTestResult();

    void DoTestLine(CalibParam &param);
    void DoTestLine2();
    void DoTestLine3();

    void GenDefaultConfig();
    void PrintGeneralConfig();
    void LoadCalibConfig();
    void SaveCalibConfig();
    void GetUserConfig();

    void DoTestSuiteFunction();
    void StopAllTest(bool save = true);
    void StartAllTest(const QString &serial, const QString &who);

signals:
    void displayRow(QStringList row);
    void updateProgress(int value);
public slots:
    void on_btnLoadTestParamClicked();
    void on_btnTestClicked();
    void on_btnStartTestClicked();
    void on_btnConnectServerClicked();
    void on_btnConnectSignalGenClicked();

    void on_updateUserSetting();

    void on_SslClientConnectEvent(int evt);
    void on_SiggenConnectEvent(int evt);
    void on_DataReceived(quint64 data);
    void AppendRowTable(QStringList row);
    void ShowProgress(int value);


private:
    QGroupBox       *groupConfig;
    QGroupBox       *groupSetting;
    QGroupBox       *groupMan;
    QTableView      *tableView;
    QHBoxLayout     *hLayout;
    QVBoxLayout     *mainLayout, *mainSettingLayout;
    QFormLayout     *settingLayout, *manLayout;
    QLabel          *labelHeader;

    QLabel          *labelProgress;
    QProgressBar    *progressCalib;

    QComboBox       *comCalibMode;

    QLabel          *labelInstrIp;
    QLineEdit       *editInstrIp, *editInstrPort;
    QLabel          *labelServerIp;
    QLineEdit       *editServerIp, *editServerPort, *editServerUdpPort;
    QLabel          *labelSslStatus;
    QLabel          *labelInstrStatus;
    QPushButton     *btnConnectInstr, *btnConnectServer, *btnStartTest;

    QPushButton     *btnTest;
    QLabel          *labelSerial;
    QLineEdit       *editSerial;
    QLabel          *labelWhoTest;
    QLineEdit       *editWhoTest;
    QLabel          *labelResult;

    QTextEdit       *editTest;
    TestParam       testParam;
    TestResult      testResult;


    QPushButton     *btnTestType;

    QComboBox       *comTestType;

    bool            changeMiss;
    //uint64_t        genConfig.serverDelay;
    //uint64_t        genConfig.siggenDelay;

    SensorConfig    m_calibSenCfg;
    int             lineCalib;
    int             maxLine;
    CalibMode       calibMode;

    bool            isSaveCfg;
};



#endif // CALIBSENSOR_H
