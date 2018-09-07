#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QDebug>
#include <QErrorMessage>
#include <QMessageBox>
#include <QCheckBox>
#include <QToolBar>
#include <QStatusBar>
#include <QtSerialPort/QSerialPortInfo>
#include "configuration.h"
#include "testsuite.h"
#include "program/flashfpga.h"
#include "calibsensor.h"

class MainDialog : public QDialog
{
    Q_OBJECT
public:
    MainDialog(QWidget *parent = 0);
    ~MainDialog();

    void ShowCommError();
    void ShowReadUserBoxError();    
    bool closeWindow();
    void createUiElem();
    void createConnection();
    void createLayout();
    void closeEvent(QCloseEvent *event);

    static bool copy_dir_recursive(QString from_dir, QString to_dir,
                                   bool replace_on_conflit = false);

public slots:
    void on_testSuiteClicked();

signals:
    void sigUpdateLastScreenUsed(int);
private:

    QHBoxLayout     *mainLayout;
    Configuration   *wgConfig;
    TestSuite       *wgTestSuite;
    FlashFpga       *wgFlashFpga;
    QTabWidget      *mainTab;
};

#endif // MAINDIALOG_H
