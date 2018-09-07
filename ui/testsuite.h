#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

#include <slidingstackedwidget.h>
#include "testing/testifrf.h"
#include "testing/testfpga.h"
#include "testing/testsensor.h"
#include "testing/testsystem.h"
#include "testing/testgpsdo.h"
#include "testing/testctrlpt.h"
#include "calibsensor.h"

class TestSuite : public QWidget
{
    Q_OBJECT
public:
    explicit TestSuite(QWidget *parent = 0);
    ~TestSuite();
    void createUiElem();
    void createComponentContent();
    void createLayout();
    void createConnection();
    void createIcons();
    void mousePressEvent(QMouseEvent *event);
signals:
    void sigClickOnScreen();
public slots:
    void on_updateStatusBar(QString cont, QColor color);
    void on_clickedOnControl(void);
    void on_changeItem(int idx);

private:
    QHBoxLayout     *hLayout;
    QVBoxLayout     *mainLayout;
    SlidingStackedWidget *stacker;
    TestIfrf        *testIfrf;
    TestFpga        *testFpga;
    TestGpsdo       *testGpsdo;
    TestCtrlPt      *testCtrlPt;
    TestSensor      *testSensor;
    CalibSensor     *calibSensor;
    TestSystem      *testSystem;
    QStatusBar      *status;
    QListWidget     *contentsWidget;

    QListWidgetItem *btnTestIfrf;
    QListWidgetItem *btnTestFpga;
    QListWidgetItem *btnTestGpsdo;
    QListWidgetItem *btnTestCtrlPt;
    QListWidgetItem *btnTestSensor;
    QListWidgetItem *btnCalibSensor;
    QListWidgetItem *btnTestSystem;

    Controller      *controller;
};

#endif // TESTSUITE_H
