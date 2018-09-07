#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <marble/MarbleWidget.h>
#include <marble/MarbleModel.h>
#include <marble/ViewportParams.h>
#include <marble/GeoPainter.h>
#include <QtWidgets>

using namespace Marble;
class MapWidget : public MarbleWidget
{
    Q_OBJECT
public:


    MapWidget(MarbleWidget *parent = 0);    

protected:
//    virtual void customPaint(GeoPainter* painter) Q_DECL_OVERRIDE;
//    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//    void notifyMouseClick(int x, int y);

public slots:


private:
};

#endif // MAPWIDGET_H
