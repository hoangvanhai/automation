#include "maindialog.h"
#include <configuration/uiconfig.h>

MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
{
    Q_INIT_RESOURCE(img);

    UiConfig::getInstance();
    UiConfig::getInstance()->openXmlFile(CONFIG_FILE_NAME);
    UiConfig::getInstance()->loadConfigFromXmlFile();

    GeneralConfig genConfig = UiConfig::getInstance()->getGeneralConfig();

    if(!genConfig.setupInOut) {        
        if(copy_dir_recursive(QString("testlist"), QString(genConfig.inputDir.c_str()))) {
            UiConfig::getInstance()->saveGeneralSetupInOut(1);
        }
        LREP("COPY INOUT\n");
    }

    createUiElem();
    createLayout();
    createConnection();
}

MainDialog::~MainDialog()
{

}


void MainDialog::closeEvent(QCloseEvent *event)
{
    if (closeWindow()) {
    //if (1) {
        UiConfig::getInstance()->closeXmlFile();
        //UiConfig::getInstance()->destroyInstance();
        event->accept();
        qApp->quit();
    } else {
        event->ignore();
    }
}

void MainDialog::on_testSuiteClicked()
{
    wgConfig->setExpanded(false);
}

bool MainDialog::closeWindow()
{
    QMessageBox::StandardButton answer = QMessageBox::question(
        this,
        tr("Thoát chương trình"),
        tr("Bạn muốn thoát chương trình ?"),
        QMessageBox::Yes | QMessageBox::No
    );

    return answer == QMessageBox::Yes;
}


void MainDialog::createUiElem()
{
    wgConfig    = new Configuration(this);
    wgTestSuite = new TestSuite;
    wgFlashFpga = new FlashFpga;
    mainLayout  = new QHBoxLayout;
    mainTab     = new QTabWidget(this);    
}

void MainDialog::createConnection()
{
    connect(wgTestSuite, SIGNAL(sigClickOnScreen()), wgConfig, SLOT(on_Collap()));        
}

void MainDialog::createLayout()
{

    mainTab->addTab(wgTestSuite, tr("ĐO KIỂM TỰ ĐỘNG"));
    mainTab->addTab(wgFlashFpga, tr("VSI3 TOOL"));
    mainLayout->addItem(new QSpacerItem(20, 0));
    mainLayout->addWidget(mainTab);
    setLayout(mainLayout);

    wgConfig->setExpanded(false);
    wgConfig->raise();    

    wgConfig->setMinimumHeight(700);        
    setWindowFlags(Qt::Window);
    setMinimumSize(1300, 900);


    qApp->setStyle(QStyleFactory::create("Fusion"));    
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window,      QColor(47, 47, 47));
    darkPalette.setColor(QPalette::WindowText,  QColor(231, 231, 231));
    darkPalette.setColor(QPalette::Base,        QColor(81,81,81));
    darkPalette.setColor(QPalette::AlternateBase, QColor(68,68,68));
    darkPalette.setColor(QPalette::ToolTipBase, QColor(231, 231, 231));
    darkPalette.setColor(QPalette::ToolTipText, QColor(231, 231, 231));
    darkPalette.setColor(QPalette::Text,        QColor(231, 231, 231));
    darkPalette.setColor(QPalette::Button,      QColor(61, 61, 61));
    darkPalette.setColor(QPalette::ButtonText,  QColor(231, 231, 231));
    darkPalette.setColor(QPalette::BrightText,  Qt::red);
    darkPalette.setColor(QPalette::Link,        QColor(127, 194, 65));
    darkPalette.setColor(QPalette::Highlight,   QColor(127, 194, 65));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    darkPalette.setColor(QPalette::Disabled, QPalette::Button, QColor(88, 88, 88));


    qApp->setPalette(darkPalette);

    setStyleSheet(QLatin1String("font: 9pt;"));

    QIcon icon;
    icon.addFile(QStringLiteral(":/images/operations-icon-9.png"), QSize(), QIcon::Normal, QIcon::Off);
    setWindowIcon(icon);

    //showMaximized();
}



bool MainDialog::copy_dir_recursive(QString from_dir, QString to_dir, bool replace_on_conflit)
{
    QDir dir;
    dir.setPath(from_dir);

    from_dir += QDir::separator();
    to_dir += QDir::separator();

    foreach (QString copy_file, dir.entryList(QDir::Files))
    {
        QString from = from_dir + copy_file;
        QString to = to_dir + copy_file;

        if (QFile::exists(to))
        {
            if (replace_on_conflit)
            {
                if (QFile::remove(to) == false)
                {
                    return false;
                }
            }
            else
            {
                continue;
            }
        }

        if (QFile::copy(from, to) == false)
        {
            return false;
        }
    }

    foreach (QString copy_dir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QString from = from_dir + copy_dir;
        QString to = to_dir + copy_dir;

        if (dir.mkpath(to) == false)
        {
            return false;
        }

        if (copy_dir_recursive(from, to, replace_on_conflit) == false)
        {
            return false;
        }
    }

    return true;
}
