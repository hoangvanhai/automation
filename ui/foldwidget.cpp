#include "foldwidget.h"
#include <QPainter>

#define BORDER_WIDTH 6

#define FOLD_IMAGE_WIDTH 5
#include <QDebug>

FoldWidget::FoldWidget(QWidget *parent): QWidget(parent), expanded(true) {
    //showAllChildren();
    foldColor = QColor("#58595b");
    foldHoverdColor = QColor("#58595b");
    inFoldIcon = false;
    expandWidth = 200;
    setMouseTracking(true);
}

void FoldWidget::paintEvent(QPaintEvent *e){

    QWidget::paintEvent(e);
    QPainter painter(this);
    QPen pen;


    pen.setColor(inFoldIcon ? foldHoverdColor : foldColor);
    pen.setWidth(BORDER_WIDTH);
    pen.setJoinStyle(Qt::MiterJoin);

    painter.setPen(pen);
    if (expanded) {
        painter.drawRect(BORDER_WIDTH / 2, BORDER_WIDTH / 2, width() - BORDER_WIDTH, height() - BORDER_WIDTH);

        QPointF s1(width() - BORDER_WIDTH - FOLD_IMAGE_WIDTH, height() / 2 - 3 * BORDER_WIDTH);
        QPointF s2(width() - BORDER_WIDTH, height() / 2 - 4 * BORDER_WIDTH);
        QPointF s3(width() - BORDER_WIDTH - FOLD_IMAGE_WIDTH, height() / 2 + 3 * BORDER_WIDTH);
        QPointF s4(width() - BORDER_WIDTH, height() / 2 + 4 * BORDER_WIDTH);

        QPainterPath path(s1);
        path.lineTo(s3);
        path.lineTo(s4);
        path.lineTo(s2);
        path.lineTo(s1);

        QBrush brush(inFoldIcon ? foldHoverdColor : foldColor);
        painter.fillPath(path, brush);


        painter.drawPixmap(width() - 13, height() / 2 - 8, pixmapClose.width(), 15, pixmapClose);
    } else {
        painter.drawLine(BORDER_WIDTH / 2, 0, BORDER_WIDTH / 2, height());

        QPointF s1(BORDER_WIDTH * 2, height() / 2 - 3 * BORDER_WIDTH);
        QPointF s2(BORDER_WIDTH, height() / 2 - 4 * BORDER_WIDTH);
        QPointF s3(BORDER_WIDTH * 2, height() / 2 + 3 * BORDER_WIDTH);
        QPointF s4(BORDER_WIDTH, height() / 2 + 4 * BORDER_WIDTH);

        QPainterPath path(s1);
        path.lineTo(s3);
        path.lineTo(s4);
        path.lineTo(s2);
        path.lineTo(s1);

        QBrush brush(inFoldIcon ? foldHoverdColor : foldColor);
        painter.fillPath(path, brush);

        painter.drawPixmap(width() - 13, height() / 2 - 8, pixmapOpen.width(), 15, pixmapOpen);
    }
}



void FoldWidget::mousePressEvent(QMouseEvent *)
{
    if (inFoldIcon) {
        if (expanded) {
            inFoldIcon = false;
            hideAllChildren();
            expanded = false;
            repaint();
            emit onFoldChange(false);
        } else {
            inFoldIcon = false;
            showAllChildren();
            expanded = true;
            repaint();
            emit onFoldChange(true);
        }
    }
}

void FoldWidget::mouseMoveEvent(QMouseEvent *e){
    if (e->x() >= width() - BORDER_WIDTH * 2){
        if (inFoldIcon) return;
        inFoldIcon = true;
        repaint();
    } else {
        if (!inFoldIcon) return;
        inFoldIcon = false;
        repaint();
    }
}


bool FoldWidget::getExpanded() const
{
    return expanded;
}

void FoldWidget::setExpanded(bool value){
    if (value != expanded) {
        expanded = value;
        if (expanded) {
            showAllChildren();
        } else {
            hideAllChildren();
        }
        repaint();
    }
}

void FoldWidget::setExpandedWidth(int value)
{
    expandWidth = value;
}

#include <QLayout>
void FoldWidget::hideAllChildren()
{
    setMinimumWidth(BORDER_WIDTH);
    setMaximumWidth(BORDER_WIDTH * 2);
    setContentsMargins(contentsMargins() - 6);
    for (auto obj: children()) {
        if (obj->isWidgetType()) {
            QWidget* childWidget = qobject_cast<QWidget*>(obj);
            childWidget->hide();
        }
    }
}

void FoldWidget::showAllChildren()
{
    setContentsMargins(contentsMargins() + 6);
    setMinimumWidth(expandWidth);
    setMaximumWidth(expandWidth);
    for (auto obj: children()) {
        if (obj->isWidgetType()) {
            QWidget* childWidget = qobject_cast<QWidget*>(obj);
            childWidget->show();
        }
    }
}





