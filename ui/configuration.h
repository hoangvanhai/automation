#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QGroupBox>
#include <QStatusBar>
#include <QtWidgets>
#include <foldwidget.h>
#include <testconfig.h>
#include <configuration/uiconfig.h>



class Configuration : public FoldWidget
{    
    Q_OBJECT
public:
    explicit Configuration(QWidget *parent = 0);
    ~Configuration();
private:
    void initVariable();
    void createUiElem();
    void createLayout();
    void createContent();
    void createConnection();
    void loadConfig();
    void saveConfig();
    void getUserConfig();
    void generateDefsConfig();

public slots:
    void on_Collap();
    void on_ConfirmSetting();
    void on_SelectInputPath();
    void on_SelectOutputPath();

private:

    QVBoxLayout *mainLayout;
    /**
     * @brief groupSetting1
     */
    QGroupBox   *groupSetting1;    
    QFormLayout *formSetting1;

    QLineEdit   *editLocalIp;
    QComboBox   *listSignalGenType;
    QComboBox   *listSpectrumType;
    QComboBox   *listPowerType;
    QComboBox   *listDigitalType;
    QLineEdit   *editSiggenDelay, *editSpectDelay,
                *editServerDelay, *editLoadFileHigh,
                *editLoadFileLow, *editBwHigh, *editBwLow,
                *editTestOutput, *editTestInput;

    QToolButton *btnSelectInput, *btnSelectOutput;
    QPushButton *btnSetGeneral;

    QPushButton *btnClose;
    QStatusBar  *status;    

    bool        isSave;

    GeneralConfig genConfig;
};

#endif // CONFIGURATION_H
