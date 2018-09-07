#include "drawlayer1.h"
#include <QDebug>


DrawLayer1::DrawLayer1(MarbleWidget* widget, QVector<DrawPoint> &data) :
    m_widget(widget), m_drawList(data)
{
    m_x = 0;
    m_y = 0;
    m_long = 0;
    m_lat = 0;
    isUpdate = false;
    m_index = 0;    
    pixmap.load(":/images/sensor.png");
    currSenId = 0;
    m_nSensor = System_Three_Sensor;
}


QStringList DrawLayer1::renderPosition() const
{
    const QStringList layers = QStringList()
        << QStringLiteral("SURFACE")
        << QStringLiteral("HOVERS_ABOVE_SURFACE")
        << QStringLiteral("ORBIT")
        << QStringLiteral("USER_TOOLS")
        << QStringLiteral("STARS");

    int index = m_index % layers.size();
    return QStringList() << layers.at(index);
}

bool DrawLayer1::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj)

    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Plus) {
            return true;
        }
    } else if(event->type() == QEvent::MouseButtonDblClick) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        m_x = mouseEvent->x(); m_y = mouseEvent->y();
        m_widget->viewport()->geoCoordinates(m_x, m_y, m_long, m_lat,GeoDataCoordinates::Degree);
        isUpdate = true;
        return true;
    }

    return false;
}

GeoDataCoordinates DrawLayer1::approximate(const GeoDataCoordinates &base, qreal angle, qreal dist)
{
    GeoDataCoordinates::Unit deg = GeoDataCoordinates::Degree;
    return GeoDataCoordinates ( base.longitude(deg) + 1.5 * dist * sin(angle),
                base.latitude(deg) + dist * cos(angle), 0.0, deg);
}

bool DrawLayer1::render( GeoPainter *painter, ViewportParams *viewport,
    const QString& renderPos, GeoSceneLayer * layer )
{
    (void)renderPos;
    (void)layer;
    (void)viewport;

    if(isUpdate) {
        isUpdate = false;        
        if(currSenId <= m_nSensor) {
            if(currSenId != m_nSensor) {
                m_drawList[currSenId].m_lat = m_lat;
                m_drawList[currSenId].m_long = m_long;
                m_drawList[currSenId].m_id = currSenId;
                m_drawList[currSenId].m_enabled = true;
                m_drawList[currSenId].m_type = Type_Sensor;
                m_drawList[currSenId].m_text = "SENSOR " + QString::number(currSenId);
                pixmap.load(":/images/sensorIcon.png");
                m_drawList[currSenId].m_pixmap = pixmap.scaled(45, 45, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                m_drawList[currSenId].m_height = 30;
                m_drawList[currSenId].m_width = 25;
            } else {
                currSenId = 4;
                m_drawList[currSenId].m_lat = m_lat;
                m_drawList[currSenId].m_long = m_long;
                m_drawList[currSenId].m_id = currSenId;
                m_drawList[currSenId].m_enabled = true;
                m_drawList[currSenId].m_type = Type_Source;
                m_drawList[currSenId].m_text = "NGUỒN PHÁT";
                pixmap.load(":/images/nguonphat.png");
                m_drawList[currSenId].m_pixmap = pixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                m_drawList[currSenId].m_height = 30;
                m_drawList[currSenId].m_width = 35;
            }                        
            emit updateSensorLocation(m_drawList[currSenId]);
            currSenId++;
        } else {
            removeAllPoint();
            emit removeAllDataPoint();
        }

    }

    //qDebug() << m_widget->zoom();
    drawAll(painter, viewport);

    return true;
}

void DrawLayer1::drawOne(DrawPoint &point, GeoPainter *painter, ViewportParams *viewport)
{
    (void)viewport;
    if(point.m_enabled) {
        GeoDataCoordinates position(point.m_long, point.m_lat, 0.0, GeoDataCoordinates::Degree);
        painter->drawPixmap(position, point.m_pixmap);
        painter->setPen(point.m_color);
        painter->setBrush(Qt::SolidPattern);

        if(point.m_type == Type_Sensor && point.m_distance != 0) {
            point.m_text = "SENSOR " + QString::number(point.m_id) +
                    " [" + QString::number(point.m_distance, 'g', 10) + "] km";
        }

        painter->drawText(position, point.m_text, 0 - point.m_width, 0 - point.m_height);
    }
}

void DrawLayer1::drawAll(GeoPainter *painter, ViewportParams *viewport)
{
    for(auto point : m_drawList) {
        drawOne(point, painter, viewport);
    }
}


void DrawLayer1::removePoint(uint32_t id)
{
    for(auto &var : m_drawList) {
        if(var.m_id == id) {
            var.m_enabled = false;
            var.m_distance = 0;
            var.m_lat = 0;
            var.m_long = 0;
            var.m_text = "";
        }
    }
}

void DrawLayer1::removeAllPoint()
{
    for(auto &var : m_drawList) {
        var.m_enabled = false;       
        var.m_distance = 0;
        var.m_lat = 0;
        var.m_long = 0;
        var.m_text = "";
    }
    m_widget->update();
    currSenId = 0;    
}
