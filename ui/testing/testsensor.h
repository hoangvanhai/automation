#ifndef TESTSENSOR_H
#define TESTSENSOR_H


#include <thread>
#include <mutex>
#include <cstdlib>
#include "testbase.h"


#define SENSOR_RESET_VAL                   true    // For test
//#define SENSOR_RESET_VAL                 false   // For run


class TestSensor : public TestBase
{       
    Q_OBJECT
public:
    explicit TestSensor(Controller *controller, TestBase *parent = 0);
    ~TestSensor();

    void initVariable();
    void createUiElem();
    void createLayout();
    void createElemContent();
    void createTableViewHeader();
    void createConnection();    
    void ConfigController();
    void EnableSettingPanel(bool en);
    /********************************************/

    void loadTestParam(const CSVFile::CsvVector &data);    
    void LoadTestConfigFromFile();

    void PrintTestParamAll();
    /********************************************/

    void InitTestResult();

    void DoTestCurrent(ComParam &param, TestProgress progress);
    void DoTestSensitive(ComParam &param, TestProgress progress);
    void DoTestErrorPower(ComParam &param, TestProgress progress);
    void DoTestBw25kH(ComParam &param, TestProgress progress);
    void DoTestBw25kL(ComParam &param, TestProgress progress);
    void DoTestErrorFreq(ComParam &param, TestProgress progress);
    void DoTestThirdInt(ComParam &param, TestProgress progress);    

    void InitAllTestName();
    void GetResultFromPower();

    void PrintGeneralConfig();
    void LoadSensorConfig();
    void SaveSensorConfig();
    void GetUserConfig();

    void DoTestSuiteFunction();
    void StopAllTest(bool save = true);
    void StartAllTest(const QString &serial, const QString &who, bool createResult = false);
    void SaveAndRetest();


public slots:
    void on_btnSettingClicked();
    void on_btnLoadTestParamClicked();
    void on_btnTestClicked();
    void on_btnStartTestClicked();    
    void on_btnConnectServerClicked();
    void on_btnConnectSignalGenClicked();
    void on_btnSetNoiseFloorClicked();
    void on_btnTestTypeClicked();
    void on_btnPauseClicked();
    void on_updateUserSetting();

    void on_SslClientConnectEvent(int evt);
    void on_SiggenConnectEvent(int evt);
    void on_DataReceived(quint64 data);


private:
    QGroupBox       *groupConfig;
    QGroupBox       *groupSetting;
    QGroupBox       *groupMan;
    QTableView      *tableView;
    QHBoxLayout     *hLayout;
    QVBoxLayout     *mainLayout, *mainSettingLayout;
    QFormLayout     *settingLayout, *manLayout;    
    QLabel          *labelHeader;

    QLabel          *labelTestMode;    
    QComboBox       *comboTestMode;         // test hot/cold ...
    QLabel          *labelInstrIp;
    QLineEdit       *editInstrIp, *editInstrPort;
    QLabel          *labelServerIp;
    QLineEdit       *editServerIp, *editServerPort, *editServerUdpPort;
    QLabel          *labelSslStatus;
    QLabel          *labelInstrStatus;
    QPushButton     *btnConnectInstr, *btnConnectServer,
                    *btnTestCaseSetting, *btnLoadTestParam, *btnStartTest;

    QLabel          *labelCheckKeep;
    QCheckBox       *checkKeepTest;
    QPushButton     *btnTest;
    QLabel          *labelSerial;
    QLineEdit       *editSerial;    
    QCheckBox       *checkRetestIfFailed;
    QLabel          *labelWhoTest;
    QLineEdit       *editWhoTest;    

    QTextEdit       *editTest;    
    QLineEdit       *editFloor;
    QPushButton     *btnFloor, *btnTestType, *btnPause;

    QComboBox       *comTestType;


    uint32_t        floorValue;
    bool            changeMiss;


    uint32_t        bwTestHigh;
    uint32_t        bwTestLow;

    SensorConfig    m_sensorConfig;    

    bool            isSaveCfg;    

};



#endif // TESTSENSOR_H
