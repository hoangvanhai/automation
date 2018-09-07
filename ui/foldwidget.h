#ifndef FOLDWIDGET_H
#define FOLDWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>

class FoldWidget: public QWidget
{
    Q_OBJECT
public:
    explicit FoldWidget(QWidget *parent=0);       

    QColor foldColor;
    QColor foldHoverdColor;
    bool inFoldIcon;
    QPixmap pixmapOpen = QPixmap(":/images/right.png");
    QPixmap pixmapClose = QPixmap(":/images/left.png");

protected:
    void paintEvent(QPaintEvent* );
    void mousePressEvent(QMouseEvent* );
    void mouseMoveEvent(QMouseEvent* );

public:
    bool getExpanded() const;
    void setExpanded(bool value);
    void setExpandedWidth(int value);

private:
    bool expanded;
    void hideAllChildren();
    void showAllChildren();

signals:
    void onFoldChange(bool expanded);

private:
    int expandHeight;
    int expandWidth;

};

#endif // FOLDWIDGET_H
