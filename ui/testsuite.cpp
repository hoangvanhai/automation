#include "testsuite.h"

TestSuite::TestSuite(QWidget *parent) :
    QWidget(parent)
{
    createUiElem();
    createLayout();
    createComponentContent();
    createConnection();
    contentsWidget->setCurrentRow(UiConfig::getInstance()->loadGeneralTabUsed());
}

TestSuite::~TestSuite()
{
    delete controller;
}

void TestSuite::createUiElem()
{
    controller = nullptr;

    controller = new Controller();
    if(controller == nullptr) {
        return;
    }    

    mainLayout = new QVBoxLayout(this);
    hLayout = new QHBoxLayout();
    contentsWidget = new QListWidget;
    stacker = new SlidingStackedWidget(this);
    testIfrf = new TestIfrf(controller);
    testFpga = new TestFpga(controller);
    calibSensor = new CalibSensor(controller);
    testSensor = new TestSensor(controller);
    testSystem = new TestSystem(controller);
    testGpsdo = new TestGpsdo(controller);
    testCtrlPt = new TestCtrlPt(controller);
    status = new QStatusBar(this);
}

void TestSuite::createComponentContent()
{

}

void TestSuite::createLayout()
{
    createIcons();
    contentsWidget->setCurrentRow(0);    
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(60, 55));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(80);
    contentsWidget->setSpacing(6);

    stacker->addWidget(testIfrf);
    stacker->addWidget(testFpga);
    stacker->addWidget(testGpsdo);
    stacker->addWidget(testCtrlPt);
    stacker->addWidget(calibSensor);
    stacker->addWidget(testSensor);
    stacker->addWidget(testSystem);
    stacker->setSpeed(600);
    stacker->setVerticalMode(false);
    stacker->setAnimation(QEasingCurve::OutBack);

    hLayout->addWidget(contentsWidget);
    hLayout->addWidget(stacker, 1);
    mainLayout->addLayout(hLayout);
    status->setMaximumHeight(20);

    mainLayout->addWidget(status, Qt::AlignBottom);
    setLayout(mainLayout);
    status->showMessage("SẴN SÀNG");
}

void TestSuite::createConnection()
{
    connect(contentsWidget, SIGNAL(currentRowChanged(int)), stacker, SLOT(slideInIdx(int)));
    connect(contentsWidget, SIGNAL(currentRowChanged(int)), this, SLOT(on_changeItem(int)));
    connect(testIfrf, SIGNAL(updateStatusBar(QString, QColor)), this, SLOT(on_updateStatusBar(QString, QColor)));
    connect(testFpga, SIGNAL(updateStatusBar(QString, QColor)), this, SLOT(on_updateStatusBar(QString, QColor)));
    connect(calibSensor, SIGNAL(updateStatusBar(QString, QColor)), this, SLOT(on_updateStatusBar(QString, QColor)));
    connect(testSensor, SIGNAL(updateStatusBar(QString, QColor)), this, SLOT(on_updateStatusBar(QString, QColor)));
    connect(testSystem, SIGNAL(updateStatusBar(QString, QColor)), this, SLOT(on_updateStatusBar(QString, QColor)));
}

void TestSuite::createIcons()
{
    btnTestIfrf = new QListWidgetItem(contentsWidget);
    btnTestIfrf->setIcon(QIcon(":/images/board2.png"));
    btnTestIfrf->setText(tr("TEST\nIFRF"));
    btnTestIfrf->setTextAlignment(Qt::AlignHCenter);
    btnTestIfrf->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    btnTestFpga = new QListWidgetItem(contentsWidget);
    btnTestFpga->setIcon(QIcon(":/images/fpga.png"));
    btnTestFpga->setText(tr("TEST\nFPGA"));
    btnTestFpga->setTextAlignment(Qt::AlignHCenter);
    btnTestFpga->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    btnTestGpsdo = new QListWidgetItem(contentsWidget);
    btnTestGpsdo->setIcon(QIcon(":/images/gpsdo.png"));
    btnTestGpsdo->setText(tr("TEST\nGSPDO"));
    btnTestGpsdo->setTextAlignment(Qt::AlignHCenter);
    btnTestGpsdo->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    btnTestCtrlPt = new QListWidgetItem(contentsWidget);
    btnTestCtrlPt->setIcon(QIcon(":/images/anten.png"));
    btnTestCtrlPt->setText(tr("TEST CTRL\nPAN/TILT"));
    btnTestCtrlPt->setTextAlignment(Qt::AlignHCenter);
    btnTestCtrlPt->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    btnCalibSensor = new QListWidgetItem(contentsWidget);
    btnCalibSensor->setIcon(QIcon(":/images/sensor.png"));
    btnCalibSensor->setText(tr("CALIB\nSENSOR"));
    btnCalibSensor->setTextAlignment(Qt::AlignHCenter);
    btnCalibSensor->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    btnTestSensor = new QListWidgetItem(contentsWidget);
    btnTestSensor->setIcon(QIcon(":/images/sensor.png"));
    btnTestSensor->setText(tr("TEST\nSENSOR"));
    btnTestSensor->setTextAlignment(Qt::AlignHCenter);
    btnTestSensor->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    btnTestSystem = new QListWidgetItem(contentsWidget);
    btnTestSystem->setIcon(QIcon(":/images/system2.png"));
    btnTestSystem->setText(tr("TEST\nSYSTEM"));
    btnTestSystem->setTextAlignment(Qt::AlignHCenter);
    btnTestSystem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

void TestSuite::mousePressEvent(QMouseEvent *event)
{
    (void)event;
    emit sigClickOnScreen();
}

void TestSuite::on_updateStatusBar(QString cont, QColor color)
{
    if(!cont.isEmpty()) {
        QPalette palette;
        palette.setColor(QPalette::WindowText, color);
        status->setPalette(palette);
        status->showMessage(cont);

    }
}

void TestSuite::on_clickedOnControl()
{
    emit sigClickOnScreen();
}

void TestSuite::on_changeItem(int idx)
{    
    UiConfig::getInstance()->saveGeneralTabUsed(idx);
    //LREP("Tab {}\n", idx);
}

