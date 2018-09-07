#ifndef TESTGPSDO_H
#define TESTGPSDO_H

#include "testbase.h"
#include <QtSerialPort/QSerialPortInfo>

#define GPSDO_RESET_VAL                   true    // For test
//#define GPSDO_RESET_VAL                 false   // For run


class TestGpsdo : public TestBase
{
    Q_OBJECT
public:
    TestGpsdo(Controller *controller, TestBase *parent = 0);
    ~TestGpsdo();

    void initVariable();
    void createUiElem();
    void createLayout();
    void createElemContent();
    void createTableViewHeader();
    void createConnection();
    void loadTestParamToUi();
    void AppendRowTable(QStringList &row);
    void ConfigController();
    void EnableSettingPanel(bool en);
    /********************************************/

    bool loadTestParam(const CSVFile::CsvVector &data);
    void LoadTestConfigFromFile();

    void clearInputParam();
    /********************************************/
    void DoTestSuiteFunction();
    void InitTestResult();

    void ControlJigGpsdo(ComParam &param);

    void InitAllTestName();

    void GenDefaultConfig();
    void PrintGeneralConfig();
    void LoadGpsdoConfig();
    void SaveGpsdoConfig();
    void GetUserConfig();
    bool FindText(QString &s);
    void StopAllTest(bool save = true);
    void StartAllTest(const QString &serial, const QString &who);

public slots:
    void on_btnLoadTestParamClicked();
    void on_btnTestClicked();
    void on_btnStartTestClicked();
    void on_btnConnectSerialClicked();
    void on_updateUserSetting();
    void on_GpsdoDataEvent(uint8_t *data, int len);
    void on_selectComClicked();
    void on_zigTestConnectEvent(int evt);
    void on_getCurrentLocalTime();
    void on_setParamToZig();

private:
    QGroupBox       *groupConfig;
    QGroupBox       *groupSetting;
    QGroupBox       *groupMan;
    QTableView      *tableView;
    QHBoxLayout     *hLayout;
    QVBoxLayout     *mainLayout, *mainSettingLayout;
    QFormLayout     *settingLayout, *manLayout;
    QLabel          *labelHeader;

    QComboBox       *comSerialList;
    QPushButton     *btnConnectSerial, *btnStartTest;

    QCheckBox       *checkKeepTest;
    QPushButton     *btnTest;
    QLineEdit       *editSerial;
    QCheckBox       *checkRetestIfFailed;
    QLineEdit       *editWhoTest;

    QDoubleSpinBox  *editLong, *editLat;
    QSpinBox        *editUTC;
    QDateTimeEdit   *editTime;

    QPushButton     *btnSetParam, *btnGetParam;

    uint64_t        waitGpsdoInMs;
    GpsdoConfig      m_gpsdoConfig;

};

#endif // TESTGPSDO_H
