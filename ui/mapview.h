#ifndef MAPVIEW_H
#define MAPVIEW_H
#include <QtWidgets>
#include <QWidget>
#include <foldwidget.h>
#include <map/mapwidget.h>
#include <map/drawlayer1.h>
#include <QtMath>


#define EARTH_RADIUS_KM     6371.0


class MapView : public QWidget
{

    Q_OBJECT
public:
    explicit MapView(QWidget *parent = 0);
    ~MapView();

    void initVariable();
    void createUiElem();
    void createLayout();
    void createElemContent();
    void createConnection();
    void closeEvent(QCloseEvent *event);
    static double deg2rad(double deg) {return (deg * M_PI /180.0);}
    static double rad2deg(double rad) {return (rad * 180.0 / M_PI);}
    static double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
    static void swapPoint(DrawPoint &point1, DrawPoint &point2);

    static bool SortData(const DrawPoint &first, const DrawPoint &second)
    {
        return (first.m_distance < second.m_distance);
    }

    NumSensor GetNumSensor() {return m_numSensor;}
    void SetNumSensor(NumSensor n) {m_numSensor = n;}
    DrawPoint getPoint(int id);
    void setResultLocation(double lat, double lon, bool show);
    void EnablePanelButton(bool en);

signals:
    void close();
    void updateLocation(DrawPoint point);

public slots:
    void on_btnSetLocationClicked();
    void on_btnGetLocationClicked();
    void on_btnClearAllClicked();
    void on_btnUpdateNumSenClicked();
    void on_UpdateSensor(DrawPoint point);
    void on_RemoveAllData();

private:
    QHBoxLayout *mainLayout;
    QVBoxLayout *sideLayout;
    FoldWidget *foldwidget;
    QGroupBox *groupMan;
    QFormLayout *formLayout;
    MapWidget *m_map;
    DrawLayer1 *m_drawer;

    QDoubleSpinBox *editLongSensor0, *editLatSensor0,
            *editLongSensor1, *editLatSensor1,
            *editLongSensor2, *editLatSensor2,
            *editLongSensor3, *editLatSensor3,
            *editLongTxSource, *editLatTxSource;

    QLabel *labelSensor3, *labelLat, *labelLong;
    QSpacerItem *spacer;


    QPushButton *btnSetLocation, *btnGetLocation;
    QPushButton *btnClearAll;

    QComboBox *comNumSensor;
    QPushButton *btnUpdateSetSensor;

    NumSensor m_numSensor;


    QVector<DrawPoint> dataList;
    bool            isSorted;
};




#endif // MAPVIEW_H
