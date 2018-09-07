#include "mapview.h"
#include <marble/MarbleInputHandler.h>
#include <marble/ViewportParams.h>

using namespace Marble;
class MarbleAbstractPresenter;

MapView::MapView(QWidget *parent) :
    QWidget(parent)
{
    initVariable();
    createUiElem();
    createLayout();
    createElemContent();
    createConnection();
}

MapView::~MapView()
{
    m_map->close();
    delete m_map;
    delete m_drawer;

}

void MapView::initVariable()
{
    m_numSensor = System_Three_Sensor;
    isSorted = false;
}

void MapView::createUiElem()
{
    mainLayout = new QHBoxLayout;
    groupMan =  new QGroupBox("CẤU HÌNH VỊ TRÍ");
    foldwidget = new FoldWidget;
    formLayout = new QFormLayout;
    m_map = new MapWidget;
    m_drawer = new DrawLayer1(m_map, dataList);
    m_map->addLayer(m_drawer);
    m_map->installEventFilter(m_drawer);

    editLongSensor0 = new QDoubleSpinBox;
    editLatSensor0 = new QDoubleSpinBox;
    editLongSensor1 = new QDoubleSpinBox;
    editLatSensor1 = new QDoubleSpinBox;
    editLongSensor2 = new QDoubleSpinBox;
    editLatSensor2 = new QDoubleSpinBox;
    editLongSensor3 = new QDoubleSpinBox;
    editLatSensor3 = new QDoubleSpinBox;
    labelSensor3 = new QLabel("Sensor 3");
    labelLat    = new QLabel("latitude");
    labelLong = new QLabel("latitude");

    editLongTxSource = new QDoubleSpinBox;
    editLatTxSource = new QDoubleSpinBox;

    btnSetLocation = new QPushButton("XÁC NHẬN VỊ TRÍ");
    btnGetLocation = new QPushButton("LẤY VỊ TRÍ");

    sideLayout = new QVBoxLayout;

    btnClearAll = new QPushButton("XÓA TOÀN BỘ");
    comNumSensor = new QComboBox;
    btnUpdateSetSensor = new QPushButton("CẬP NHẬT");
    spacer = new QSpacerItem(0, 15);
}

void MapView::createLayout()
{
    groupMan->setLayout(formLayout);
    formLayout->addRow("SỐ LƯỢNG SENSOR", comNumSensor);
    formLayout->addWidget(btnUpdateSetSensor);
    formLayout->addItem(new QSpacerItem(0, 15));
    formLayout->addRow(new QLabel("Sensor 0"));
    formLayout->addRow(new QLabel("longitude"), new QLabel("latitude"));
    formLayout->addRow(editLongSensor0, editLatSensor0);
    formLayout->addItem(new QSpacerItem(0, 15));
    formLayout->addRow(new QLabel("Sensor 1"));
    formLayout->addRow(new QLabel("longitude"), new QLabel("latitude"));
    formLayout->addRow(editLongSensor1, editLatSensor1);
    formLayout->addItem(new QSpacerItem(0, 15));
    formLayout->addRow(new QLabel("Sensor 2"));
    formLayout->addRow(new QLabel("longitude"),new QLabel("latitude") );
    formLayout->addRow(editLongSensor2, editLatSensor2);
    formLayout->addItem(new QSpacerItem(0, 15));

    formLayout->addRow(labelSensor3);
    formLayout->addRow(labelLong, labelLat);
    formLayout->addRow(editLongSensor3, editLatSensor3);
    if(m_numSensor == System_Three_Sensor) {
        labelLat->setHidden(true);
        labelLong->setHidden(true);
        labelSensor3->setHidden(true);
        editLongSensor3->setHidden(true);
        editLatSensor3->setHidden(true);
    }
    formLayout->addItem(new QSpacerItem(0, 15));
    formLayout->addRow(new QLabel("Nguồn phát"));
    formLayout->addRow(new QLabel("longitude"), new QLabel("latitude"));
    formLayout->addRow(editLongTxSource, editLatTxSource);
    formLayout->addItem(new QSpacerItem(0, 20));
    formLayout->addRow(btnClearAll, btnSetLocation);
    //formLayout->addRow(btnClearAll);
    formLayout->setVerticalSpacing(5);
    sideLayout->addWidget(groupMan, 0, Qt::AlignTop);
    foldwidget->setLayout(sideLayout);
    foldwidget->setMaximumWidth(290);
    mainLayout->addWidget(foldwidget);
    mainLayout->addWidget(m_map);
    foldwidget->setContentsMargins(6,6,6,6);
    foldwidget->setExpandedWidth(280);
    foldwidget->setExpanded(true);
    setLayout(mainLayout);    
    setStyleSheet(QLatin1String("font: 9pt;"));
}

void MapView::createElemContent()
{    
    setMinimumSize(1300, 900);
    comNumSensor->addItem(tr("  3 SENSOR"));
    comNumSensor->addItem(tr("  4 SENSOR"));

    editLatSensor0->setMaximum(25);
    editLatSensor0->setMinimum(15);
    editLongSensor0->setMaximum(110);
    editLongSensor0->setMinimum(100);

    editLatSensor1->setMaximum(25);
    editLatSensor1->setMinimum(15);
    editLongSensor1->setMaximum(110);
    editLongSensor1->setMinimum(100);

    editLatSensor2->setMaximum(25);
    editLatSensor2->setMinimum(15);
    editLongSensor2->setMaximum(110);
    editLongSensor2->setMinimum(100);

    editLatSensor3->setMaximum(25);
    editLatSensor3->setMinimum(15);
    editLongSensor3->setMaximum(110);
    editLongSensor3->setMinimum(100);

    editLatTxSource->setMaximum(25);
    editLatTxSource->setMinimum(15);    
    editLongTxSource->setMaximum(110);
    editLongTxSource->setMinimum(100);

    editLatSensor0->setDecimals(8);
    editLongSensor0->setDecimals(8);
    editLatSensor1->setDecimals(8);
    editLongSensor1->setDecimals(8);
    editLatSensor2->setDecimals(8);
    editLongSensor2->setDecimals(8);
    editLatSensor3->setDecimals(8);
    editLongSensor3->setDecimals(8);
    editLatTxSource->setDecimals(8);
    editLongTxSource->setDecimals(8);

    editLatSensor0->setSingleStep(0.01);
    editLatSensor0->setSingleStep(0.01);
    editLongSensor0->setSingleStep(0.01);
    editLatSensor1->setSingleStep(0.01);
    editLongSensor1->setSingleStep(0.01);
    editLatSensor2->setSingleStep(0.01);
    editLongSensor2->setSingleStep(0.01);
    editLatSensor3->setSingleStep(0.01);
    editLongSensor3->setSingleStep(0.01);
    editLatTxSource->setSingleStep(0.01);
    editLongTxSource->setSingleStep(0.01);

    on_RemoveAllData();

    DrawPoint data;
    dataList.push_back(data);
    dataList.push_back(data);
    dataList.push_back(data);
    dataList.push_back(data);
    dataList.push_back(data);
    dataList.push_back(data);

}

void MapView::createConnection()
{
    connect(btnSetLocation, SIGNAL(clicked(bool)), this, SLOT(on_btnSetLocationClicked()));
    connect(btnGetLocation, SIGNAL(clicked(bool)), this, SLOT(on_btnGetLocationClicked()));
    connect(btnClearAll, SIGNAL(clicked(bool)), this, SLOT(on_btnClearAllClicked()));
    connect(m_drawer, SIGNAL(updateSensorLocation(DrawPoint)), this, SLOT(on_UpdateSensor(DrawPoint)));
    connect(m_drawer, SIGNAL(removeAllDataPoint()), this, SLOT(on_RemoveAllData()));
    connect(btnUpdateSetSensor, SIGNAL(clicked(bool)), this, SLOT(on_btnUpdateNumSenClicked()));    
}

void MapView::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}

double MapView::distanceEarth(double lat1, double lon1, double lat2, double lon2)
{
    static double R = 6371000;
    double p1 = deg2rad(lat1);
    double p2 = deg2rad(lat2);
    double dp = deg2rad(lat2 - lat1);
    double dl = deg2rad(lon2 - lon1);
    double a = qSin(dp / 2) * qSin(dp / 2) + qCos(p1) * qCos(p2) * qSin(dl / 2) * qSin(dl / 2);
    double c = 2 * qAtan2(qSqrt(a), qSqrt(1 - a));
    double d = R * c;
    return d / 1000;
}

void MapView::swapPoint(DrawPoint &point1, DrawPoint &point2)
{
    DrawPoint temp;
    temp = point1;
    point1 = point2;
    point2 = temp;
}

DrawPoint MapView::getPoint(int id)
{
    DrawPoint draw;
    draw.m_enabled = false;
    if(dataList.size() >= id)
        return dataList.at(id);

    return draw;
}

void MapView::setResultLocation(double lat, double lon, bool show)
{
    dataList[5].m_id = 5;
    dataList[5].m_lat = lat;
    dataList[5].m_long  = lon;
    dataList[5].m_enabled = show;    
    dataList[5].m_pixmap = dataList[4].m_pixmap;
    dataList[5].m_height = 30;
    dataList[5].m_width = 35;
    dataList[5].m_distance = distanceEarth(dataList.at(4).m_lat,
                          dataList.at(4).m_long,
                          dataList.at(5).m_lat,
                          dataList.at(5).m_long);
    dataList[5].m_type = Type_Source;
    dataList[5].m_color = Qt::red;
    dataList[5].m_text = "Result distance [" + QString::number(dataList[5].m_distance * 1000) + "] m";

    m_drawer->reDraw();
}

void MapView::EnablePanelButton(bool en)
{
    btnSetLocation->setEnabled(en);
    btnGetLocation->setEnabled(en);
    btnUpdateSetSensor->setEnabled(en);
    btnClearAll->setEnabled(en);
}

void MapView::on_btnSetLocationClicked()
{
    if(editLatTxSource->value() != 0 && editLongTxSource->value() != 0) {
        dataList[4].m_lat = editLatTxSource->value();
        dataList[4].m_long = editLongTxSource->value();
    }

    if(editLatSensor0->value() != 0 && editLongSensor0->value() != 0) {
        dataList[0].m_lat = editLatSensor0->value();
        dataList[0].m_long = editLongSensor0->value();
        if(dataList.at(4).m_lat != 0 || dataList.at(4).m_long != 0) {
            dataList[0].m_distance = distanceEarth(dataList.at(4).m_lat,
                                  dataList.at(4).m_long,
                                  dataList.at(0).m_lat,
                                  dataList.at(0).m_long);
        }
    }

    if(editLatSensor1->value() != 0 && editLongSensor1->value() != 0) {
        dataList[1].m_lat = editLatSensor1->value();
        dataList[1].m_long = editLongSensor1->value();
        if(dataList.at(4).m_lat != 0 || dataList.at(4).m_long != 0) {
            dataList[1].m_distance = distanceEarth(dataList.at(4).m_lat,
                                  dataList.at(4).m_long,
                                  dataList.at(1).m_lat,
                                  dataList.at(1).m_long);
        }
    }

    if(editLatSensor2->value() != 0 && editLongSensor2->value() != 0) {
        dataList[2].m_lat = editLatSensor2->value();
        dataList[2].m_long = editLongSensor2->value();
        if(dataList.at(4).m_lat != 0 || dataList.at(4).m_long != 0) {
           dataList[2].m_distance = distanceEarth(dataList.at(4).m_lat,
                                  dataList.at(4).m_long,
                                  dataList.at(2).m_lat,
                                  dataList.at(2).m_long);

        }
    }

    if(editLatSensor3->value() != 0 && editLongSensor3->value() != 0) {
        dataList[3].m_lat = editLatSensor3->value();
        dataList[3].m_long = editLongSensor3->value();
        if(dataList.at(4).m_lat != 0 || dataList.at(4).m_long != 0) {
            dataList[3].m_distance = distanceEarth(dataList.at(4).m_lat,
                                  dataList.at(4).m_long,
                                  dataList.at(3).m_lat,
                                  dataList.at(3).m_long);
        }
    }

    if(dataList[0].m_enabled &&
        dataList[1].m_enabled &&
        dataList[2].m_enabled &&
        dataList[4].m_enabled &&
            !isSorted) {

        std::list<DrawPoint> list;
        list.push_back(dataList[0]);
        list.push_back(dataList[1]);
        list.push_back(dataList[2]);

        if(m_numSensor == System_Four_Sensor) {
            if(dataList[3].m_enabled) {
                list.push_back(dataList[3]);
            }
        }

        list.sort(SortData);

        int idx = 0;
        for(auto var : list) {
            dataList[idx] = var;
            dataList[idx].m_id = idx;
            //qDebug() << "distance: " <<  dataList[idx].m_id  << " " << dataList[idx].m_distance;
            idx++;
        }



        editLatSensor0->setValue(dataList[0].m_lat);
        editLongSensor0->setValue(dataList[0].m_long);
        editLatSensor1->setValue(dataList[1].m_lat);
        editLongSensor1->setValue(dataList[1].m_long);
        editLatSensor2->setValue(dataList[2].m_lat);
        editLongSensor2->setValue(dataList[2].m_long);

        if(m_numSensor == System_Four_Sensor && dataList[3].m_enabled) {
            editLatSensor3->setValue(dataList[3].m_lat);
            editLongSensor3->setValue(dataList[3].m_long);
        }

        //qDebug() << "Sorted == true";
        //isSorted = true;
    }

    m_drawer->reDraw();
}

void MapView::on_btnGetLocationClicked()
{

}

void MapView::on_btnClearAllClicked()
{
    m_drawer->removeAllPoint();
    on_RemoveAllData();        
}

void MapView::on_btnUpdateNumSenClicked()
{
    if(comNumSensor->currentIndex() == 0) {
        m_numSensor = System_Three_Sensor;
        m_drawer->SetNumSensor(m_numSensor);
        labelLat->setHidden(true);
        labelLong->setHidden(true);
        labelSensor3->setHidden(true);
        editLatSensor3->setHidden(true);
        editLongSensor3->setHidden(true);
    } else {
        m_numSensor = System_Four_Sensor;
        m_drawer->SetNumSensor(m_numSensor);
        labelLat->setHidden(false);
        labelLong->setHidden(false);
        labelSensor3->setHidden(false);
        editLatSensor3->setHidden(false);
        editLongSensor3->setHidden(false);
    }
}

void MapView::on_UpdateSensor(DrawPoint point)
{
    switch(point.m_id) {
    case 0:
        editLatSensor0->setValue(point.m_lat);
        editLongSensor0->setValue(point.m_long);
        break;
    case 1:
        editLatSensor1->setValue(point.m_lat);
        editLongSensor1->setValue(point.m_long);
        break;
    case 2:
        editLatSensor2->setValue(point.m_lat);
        editLongSensor2->setValue(point.m_long);
        break;
    case 3:
        editLatSensor3->setValue(point.m_lat);
        editLongSensor3->setValue(point.m_long);
        break;

    case 4:
        editLongTxSource->setValue(point.m_long);
        editLatTxSource->setValue(point.m_lat);
        break;

    default:
        break;
    }
}

void MapView::on_RemoveAllData()
{
    editLatSensor0->clear();
    editLatSensor0->clear();
    editLongSensor0->clear();
    editLatSensor1->clear();
    editLongSensor1->clear();
    editLatSensor2->clear();
    editLongSensor2->clear();
    editLatSensor3->clear();
    editLongSensor3->clear();
    editLongTxSource->clear();
    editLatTxSource->clear();
    isSorted = false;
    //qDebug() << "Sorted = false";
}

