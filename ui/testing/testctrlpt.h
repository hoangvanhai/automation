#ifndef TESTCTRLPT_H
#define TESTCTRLPT_H

#include "testbase.h"
#include <QtSerialPort/QSerialPortInfo>

#define GPSDO_RESET_VAL                   true    // For test
//#define GPSDO_RESET_VAL                 false   // For run


class TestCtrlPt : public TestBase
{
    Q_OBJECT
public:
    TestCtrlPt(Controller *controller, TestBase *parent = 0);
    ~TestCtrlPt();

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

    void ControlJigPantilt(ComParam &param);

    void InitAllTestName();

    void GenDefaultConfig();
    void PrintGeneralConfig();
    void LoadCtrlPtConfig();
    void SaveCtrlPtConfig();
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
    void on_ctrlPtDataEvent(uint8_t *data, int len);
    void on_selectComClicked();
    void on_zigTestConnectEvent(int evt);

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


    uint64_t        waitCtrlPtInMs;
    FpgaConfig      m_ctrlptConfig;

};


#endif // TESTCTRLPT_H
