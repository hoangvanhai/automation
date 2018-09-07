#ifndef TESTIFRF_H
#define TESTIFRF_H
#include <QWidget>
#include <QtWidgets>
#include "csv/csvfile.h"
#include <thread>
#include <mutex>
#include "network/controller.h"
#include "xlsx/xlsxdocument.h"
#include <QtSerialPort/QSerialPortInfo>
#include "testbase.h"

//#define IFRF_RESET_VAL_IFRF                     true    // For test
#define IFRF_RESET_VAL_IFRF                   false   // For run


class TestIfrf : public TestBase
{
    struct MarkerPoint{
        double freq;
        double power;
    };

    Q_OBJECT
public:
    TestIfrf(Controller *controller, TestBase *parent = 0);
    ~TestIfrf();

    void initVariable();
    void createUiElem();
    void createLayout();
    void createElemContent();
    void createTableViewHeader();
    void createConnection();
    void ConfigController();
    void EnableSettingPanel(bool en);
    /********************************************/

    bool loadTestParam(const CSVFile::CsvVector &data);
    void LoadTestConfigFromFile();
    void LoadIfrfConfig();
    void SaveIfrfConfig();

    void PrintTestParamAll();
    /********************************************/

    void DoTestSuiteFunction();


    void InitTestResult();

    void DoTestPowerConsume(ComParam &param);
    void DoTestSensitive(ComParam &param);
    double GetSensitiveValue(double freq, uint64_t ferr,
                             double pwrMin, double pwrMax, double &getSinad);
    void DoTestSelectImage(ComParam &param);
    void DoTestSelectInterFreq(ComParam &param);
    void DoTestSpurious(ComParam &param);
    void DoTestImdInRange(ComParam &param);
    void DoTestImdOutRange(ComParam &param);
    void DoTestThirdInt(ComParam &param);
    void DoTestJamingRange(ComParam &param);
    void DoTestP1Param(ComParam &param);
    void DoTestDynLinear(ComParam &param);
    void DoTestBwCenterFreq(ComParam &param);

    void InitAllTestName();

    void GetResultFromPower();

    void GenDefaultConfig();
    void PrintGeneralConfig();    
    void GetUserConfig();    


    double ConvertToImageFreq(double freq);
    double ConvertToInterFreq(double freq);

    void StartAllTest(const QString &serial, const QString &who, bool createResult = false);
    void StopAllTest(bool save = true);

    bool FindText(QString &s);

    double Spect_CheckFreqAtPower(double power, double perr);
    double Spect_CheckPowerOfFreq(double freq, uint64_t err);
    void   Spect_ClearSignalList() {control->Spect_ClearAllRecvData();}


public slots:
    void on_btnSettingClicked();
    void on_btnLoadTestParamClicked();    
    void on_btnStartTestClicked();    
    void on_btnConnectSpectClicked();
    void on_btnConnectSignalGenClicked();
    void on_btnConnectSerialClicked();

    void on_updateCellData(int row, int colum, QString data);
    void on_clearColumData(int colum, int numrow, int start = 0);

    void on_updateUserSetting();
    void on_SiggenConnectEvent(int evt);
    void on_SpectConnectEvent(int evt);
    void on_SpectRecvData(uint8_t *data, int len);
    void on_selectComClicked(QString);
    void on_IfrfConnectEvent(int evt);
    void on_IfrfRecvDataEvent(uint8_t* data, int len);

    void on_btnTestSendClicked();
    void on_btnPauseClicked();
    void on_btnTestSpectClicked();

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
    QComboBox       *comboTestMode;

    QComboBox       *comboSerialList;
    QLabel          *labelInstrIp;
    QLineEdit       *editInstrIp, *editInstrPort;

    QLineEdit       *editSpectIp, *editSpectPort;
    QLabel          *labelSpectStatus;
    QLabel          *labelInstrStatus;
    QPushButton     *btnConnectInstr, *btnConnectSpect, *btnConnectSerial,
                    *btnTestCaseSetting, *btnLoadTestParam, *btnStartTest, *btnPause;

    QLabel          *labelCheckKeep;
    QCheckBox       *checkKeepTest;
    QPushButton     *btnTest;
    QLabel          *labelSerial;
    QLineEdit       *editSerial;
    QLabel          *labelOpenWhenDone;
    QCheckBox       *checkRetestIfFailed;
    QLabel          *labelWhoTest;
    QLineEdit       *editWhoTest;    


    /**
     * @brief groubTestReadWrite
     */
    QPushButton *btnSendCommand, *btnTestSpect;
    QLineEdit *editSendCommand, *editRecvCommand;


    IfrfConfig      m_ifrfConfig;

    bool            isSaveCfg;

    int             m_waitCode;
    uint64_t        currCenterFreq;
    double          currSensitive;

    std::list<MarkerPoint>              m_listMarker;
    uint64_t        currFreq;

};



#endif // TESTIFRF_H
