#ifndef MAINVIEW_H
#define MAINVIEW_H
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QMenu>
#include <QColorDialog>
#include <QPainter>

#include "lineobject.h"
#include "rectobject.h"

class MainView : public QGraphicsView
{
    Q_OBJECT
public:
    QPointF gEndPoint;
    static QColor gXYLineColor;

    MainView(QWidget *parent = nullptr);
    MainView(QGraphicsScene *scene, QWidget *parent = nullptr);

    void init();

    void setMagnify();
    void setReduce();

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

signals:
    void viewPosChange(QPointF pos);

private:

    bool IS_MOVE;

    QPointF mLastPoint;


};

#endif // MAINVIEW_H
