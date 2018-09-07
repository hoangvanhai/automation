#ifndef TESTSYSTEM_H
#define TESTSYSTEM_H


#include <thread>
#include <mutex>
#include <cstdlib>
#include "testbase.h"
#include <mapview.h>
#include <network/controller.h>
#include <QtSerialPort/QSerialPortInfo>


#define SYSTEM_RESET_VAL                   true    // For test
//#define SYSTEM_RESET_VAL                   false   // For run


class TestSystem : public TestBase
{

    Q_OBJECT
public:
    explicit TestSystem(Controller *controller, TestBase *parent = 0);
    ~TestSystem();

    void initVariable();
    void createUiElem();
    void createLayout();
    void createElemContent();
    void createTableViewHeader();
    void createConnection();
    void AppendRowTable(QStringList &row);
    void ConfigController();
    void EnableSettingPanel(bool en);
    /********************************************/

    bool loadTestParam(const CSVFile::CsvVector &data);
    void LoadTestConfigFromFile();

    void clearInputParam();


    /********************************************/
    void InitTestResult();
    void DoTestTdoa(ComParam &param);

    void LoadSystemConfig();
    void SaveSystemConfig();
    void GetUserConfig();

    void DoTestSuiteFunction();
    void StopAllTest(bool save = true);
    void StartAllTest(const QString &serial, const QString &who, bool createResult);

    bool FindText(QString &s);
    static int  GetRand(int min, int max);

signals:
    void updateResultLocation(double lat, double lon, bool show);
public slots:
    void on_btnLoadMapClicked();
    void on_btnLoadTestParamClicked();
    void on_btnTestClicked();
    void on_btnStartTestClicked();    
    void on_btnConnectServerClicked();
    void on_btnConnectRfDelayClicked();
    void on_mapClose();

    void on_selectComClicked();
    void on_updateUserSetting();

    void on_SslClientConnectEvent(int evt);
    void on_SiggenConnectEvent(int evt);
    void on_DataReceived(quint64 data);
    void on_RfDelayConnEvent(int evt);    
    void on_ServerRecvTdoaStatus(external::client::geolocation::Status status);
    void on_UpdateLocationResult(double lat, double lon, bool show);

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
    QComboBox       *comSerialList;
    QLineEdit       *editServerIp, *editServerPort, *editServerUdpPort;
    QLabel          *labelSslStatus;    
    QPushButton     *btnConnectRfDelay, *btnConnectServer,
                    *btnLoadMap, *btnLoadTestParam, *btnStartTest;

    QLabel          *labelCheckKeep;
    QCheckBox       *checkKeepTest;
    QPushButton     *btnTest;
    QLabel          *labelSerial;
    QLineEdit       *editSerial;    
    QCheckBox       *checkRetestIfFailed;
    QLabel          *labelWhoTest;
    QLineEdit       *editWhoTest;    

    QTextEdit       *editTest;    
    uint32_t        bwTestHigh;
    uint32_t        bwTestLow;

    bool            isSaveCfg;
    MapView         *m_mapView;

    DrawPoint       txLocation;
    DrawPoint       Sensor0, Sensor1, Sensor2, Sensor3;


    SystemConfig    m_systemConfig;

    QProgressBar    *progS0, *progS1, *progS2, *progS3;
    QLabel          *labelS0, *labelS1, *labelS2, *labelS3;

};



#endif // TESTSYSTEM_H
