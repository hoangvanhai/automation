#ifndef FLASHFPGA_H
#define FLASHFPGA_H

#include <QWidget>
#include <QtWidgets>
#include <program/tcp/TcpProgItem.h>
#include "network/controller.h"

class FlashFpga : public QWidget
{
    Q_OBJECT
public:
    explicit FlashFpga(QWidget *parent = 0);
    ~FlashFpga();

    void initVariable();
    void createUiElem();
    void createLayout();
    void createContent();
    void createConnection();

    void startProg();
    void stopProg();
    bool FindText(QString &s);

public slots:    
    void on_btnStartProgClicked();
    void on_btnBrowseFileClicked();
    void on_finishProg(QString result, QString detail);
    void on_updateProgProgess(int fPercent, int fSpeed);
    void on_errorProg(QString error);
    void on_btnWriteSensorTypeClicked();
    void on_btnWriteSensorIpClicked();
    void on_btnReadSensorTypeClicked();
    void on_btnReadSensorIpClicked();
    void on_etherDataEvent(uint8_t *data, int len);    

private:
    QVBoxLayout *mainLayout;
    QFormLayout *formMain;

    QGroupBox  *groupConfigFpga;
    QGridLayout *gridConfigFpga;
    QComboBox   *comNetworkCard, *comSensorType;
    QLineEdit   *editFpgaIp;
    QLineEdit   *editFpgaPort;
    QPushButton *btnWriteFpgaType, *btnReadFpgaType,
                *btnWriteFpgaIp, *btnReadFpgaIp;

    /**
     * @brief groupProgramFpga
     */   
    QGroupBox   *groupProgramFpga;
    QFormLayout *formProgramFpga;
    QLineEdit   *editSensorAddr;
    QLineEdit   *editSensorPort;
    QLineEdit   *editSensorId;
    QLineEdit   *editFilePath;
    QCheckBox   *checkUseForwarder;
    QLabel      *labelStatus;
    QProgressBar *prgProgramFpga;
    QPushButton *btnBrowseFile;
    QPushButton *btnStartStop;

    /**
     * @brief groupSerialFpga
     */
    QGroupBox   *groupSerialFpga;
    QFormLayout *formSerialFpga;

    QPushButton *btnWriteFpgaSerial;

    QPushButton *btnReadFpgaSerial;
    QLineEdit   *editFpgaSerial;

    /**
     * @brief groupSerialIfrf
     */
    QGroupBox   *groupSerialIfrf;
    QFormLayout *formSerialIfrf;

    QPushButton *btnWriteIfrfSerial;
    QPushButton *btnReadIfrfSerial;
    QLineEdit   *editIfrfSerial;



//    /**
//     * @brief groubTestReadWrite
//     */
//    QGroupBox *groupTestReadWrite;
//    QFormLayout *formTestReadWrite;

//    QPushButton *btnSendCommand;
//    QLineEdit *editSendCommand, *editRecvCommand;



    /**
     * @brief Infomation
     */    
    QStatusBar  *status;


    TcpProgItem *m_tcpProg;
    bool        m_programming;

    QString     m_lastFilePath;

    Controller  *m_control;

    std::string m_cfgCurrSensorIp;
    int         m_cfgCurrSensorPort;




};

#endif // FLASHFPGA_H
