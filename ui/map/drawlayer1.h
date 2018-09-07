#ifndef DRAWLAYER1_H
#define DRAWLAYER1_H

#include <QObject>
#include <marble/MarbleMap.h>
#include <marble/LayerInterface.h>
#include <marble/MarbleWidget.h>
#include <marble/GeoPainter.h>
#include <marble/GeoDataLineString.h>
#include <marble/ViewportParams.h>
#include <QtWidgets>
#include <QList>
#include <stdint.h>

using namespace Marble;

class DrawPoint;

enum NumSensor {
    System_Three_Sensor = 3,
    System_Four_Sensor = 4,
};

enum DrawInstType {
    Type_Sensor,
    Type_Source,
};

enum Shape { Line, Points, Rect, RoundedRect,
             Path, Text, Pixmap };

class DrawPoint {

public:
    DrawPoint() {
        m_lat = 0;
        m_long = 0;
        m_shape = Rect;
        m_width = 10;
        m_height = 10;
        m_text = "Default Caption";
        m_enabled = false;
        m_distance = 0;
        m_color = Qt::black;
    }
    void setShape(Shape& shape) {m_shape = shape;}
    Shape getShape() const {return m_shape;}
    bool m_enabled;
    qreal m_lat;
    qreal m_long;
    Shape m_shape;
    qreal m_width;
    QColor m_color;
    qreal m_height;
    QPixmap m_pixmap;
    uint32_t m_id;
    QString m_text;
    DrawInstType m_type;
    double m_distance;
};


class DrawLayer1 : public QObject, public LayerInterface
{

    Q_OBJECT
public:
    // Constructor
    DrawLayer1(MarbleWidget* widget, QVector<DrawPoint> &data);

    static GeoDataCoordinates approximate(const GeoDataCoordinates &base, qreal angle, qreal dist);

    virtual QStringList renderPosition() const;

    // Implemented from LayerInterface
    virtual bool render( GeoPainter *painter, ViewportParams *viewport,
                        const QString &renderPos, GeoSceneLayer *layer);

    void drawAll(GeoPainter *painter, ViewportParams *viewport);
    void drawOne(DrawPoint& point, GeoPainter *painter, ViewportParams *viewport);
    void addPoint(DrawPoint &point) {m_drawList.push_back(point);}
    void removePoint(uint32_t id);
    void removeAllPoint();
    virtual bool eventFilter(QObject *obj, QEvent *event);
    void resetAllParam();
    void SetNumSensor(NumSensor n) {m_nSensor = n;}
    NumSensor GetNumSensor() {return m_nSensor;}
    void updateDrawPointContent(DrawPoint &point);
    void setDataList(QVector<DrawPoint> &data) {m_drawList = data;}
    void reDraw() {
        m_widget->update();
    }

signals:
    void updateSensorLocation(DrawPoint point);
    void removeAllDataPoint();

public slots:

private:
    MarbleWidget* m_widget;   
    QVector<DrawPoint> &m_drawList;
    int m_x, m_y;
    qreal m_long, m_lat;
    int m_index;
    bool    isUpdate;

    QPixmap pixmap;
    NumSensor m_nSensor;
    uint32_t currSenId;
};


#endif // DRAWLAYER1_H
