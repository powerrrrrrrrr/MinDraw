#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsView>
#include <QObject>
#include <QMetaObject>
#include <QGraphicsLineItem>

#include "baseobject.h"
#include "rectobject.h"
#include "ellipseobject.h"
#include "lineobject.h"


class MainScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum DrawType{None, Line, Rect, Trash, Ellipse,HorDistance,VerDistance};
    MainScene(QObject* parent = nullptr);

    static int gGridSize;//单个小矩形的边长
    static int gGridSquares;//由深色线构成的矩形的边长由几个小矩形构成，意思就是大矩形的边长是几个小矩形的边长
    static QColor gBackgroundColor;
    static QColor gForegroundColorDark;//暗色前景色
    static QColor gForegroundColorLight;//亮色前景色

    void setDrawType(DrawType type);
    bool isDrawing(){return isDraw;}

    void setMyPenColor(QColor color);

    void saveScene(QRect rect);

protected:
    void drawBackground(QPainter* painter, const QRectF &rect);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
    DrawType m_DrawType;

    QPointF m_startPos;
    QPointF m_endPos;

    BaseObject* arect;
    BaseObject* aellipse;
    BaseObject* aline;

    QGraphicsLineItem* m_lines;

    bool isDraw;

    QColor penColor = Qt::white;

    QPen measurePen;
    QColor measurePenColor;
};

#endif // MAINSCENE_H
