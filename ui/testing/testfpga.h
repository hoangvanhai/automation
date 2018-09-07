#ifndef TESTFPGA_H
#define TESTFPGA_H
#include "testbase.h"


#define FPGA_RESET_VAL                   true    // For test
//#define FPGA_RESET_VAL                 false   // For run



class TestFpga : public TestBase
{

    Q_OBJECT
public:
    TestFpga(Controller *controller, TestBase *parent = 0);
    ~TestFpga();

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

    void ControlFpga(ComParam &param);

    void InitAllTestName();

    void GenDefaultConfig();
    void PrintGeneralConfig();
    void LoadFpgaConfig();
    void SaveFpgalConfig();
    void GetUserConfig();

    void StopAllTest(bool save = true);
    void StartAllTest(const QString &serial, const QString &who);

public slots:    
    void on_btnLoadTestParamClicked();
    void on_btnTestClicked();
    void on_btnStartTestClicked();    
    void on_btnConnectFpgaClicked();

    void on_updateUserSetting();
    void on_FpgaConnectEvent(int evt);
    void on_FpgaDataEvent(uint8_t *data, int len);

    void on_setSerialNumber(QString serial);

private:
    QGroupBox       *groupConfig;
    QGroupBox       *groupSetting;
    QGroupBox       *groupMan;
    QTableView      *tableView;
    QHBoxLayout     *hLayout;
    QVBoxLayout     *mainLayout, *mainSettingLayout;
    QFormLayout     *settingLayout, *manLayout;
    QLabel          *labelHeader;    

    QLabel          *labelInstrIp;
    QLineEdit       *editInstrIp, *editInstrPort;

    QLabel          *labelInstrStatus;
    QPushButton     *btnConnectInstr, *btnStartTest;


    QCheckBox       *checkKeepTest;
    QPushButton     *btnTest;
    QLineEdit       *editSerial;

    QCheckBox       *checkRetestIfFailed;
    QCheckBox       *checkPauseTest;
    QLineEdit       *editWhoTest;    


    uint64_t        waitFpgaInMs;    
    FpgaConfig      m_fpgaConfig;    
    bool            isSaveCfg;
};



#endif // TESTFPGA_H
