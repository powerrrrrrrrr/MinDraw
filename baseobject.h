#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <QGraphicsObject>
#include <QKeyEvent>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QVector>
#include <QMessageBox>
#include <QColor>

class BaseObject : public QGraphicsObject
{
public:
    enum OBJTYPE{Base, Line, Rect, Text, Ellipse};
    //注册到Qt元对象系统中,使得该枚举类型可以通过字符串进行反向映射
    Q_ENUM(OBJTYPE)

    //构造，析构
    explicit BaseObject(QGraphicsObject* parent = nullptr);
    ~BaseObject() override;

    //动态类型转换
    bool isLine() const;//判断返回类型是否为Line
    bool isRect() const;//判断返回类型是否为Rect

    virtual void drawSelectedRect(QPainter* painter);//画虚线框
    QString nameString() const;//返回类型的字符串表示

    virtual BaseObject::OBJTYPE objType() const;//返回对象的类型

    static QColor gBorderColor;//虚线框颜色
    static QColor gObjectColor;//图元颜色
    static qreal gMoveOffset;//每次移动的偏移量

    QPen gPen;

    QPointF startPos;
    QPointF endPos;


    enum m_handlesArea{None,LeftTop, LeftBottom, RightTop, RightBottom,
                         TopMiddle, BottomMiddle,LeftMiddle, RightMiddle};

    //m_handlesArea getMouseHandle(QPointF p);

    virtual void setPenColor(QColor color) = 0;
    virtual QColor getPenColor() = 0;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

private:
    bool beSelected;//图元是否被选中
    QColor myObjectColor;//图元颜色
    qreal myPenWidthF;//浮点类型的画笔宽度

    /*QPointF m_LeftTop;
    QPointF m_LeftBottom;
    QPointF m_RightTop;
    QPointF m_RightBottom;
    QPointF m_TopMiddle;
    QPointF m_BottomMiddle;
    QPointF m_LeftMiddle;
    QPointF m_RightMiddle;


    QRectF r_LeftTop;
    QRectF r_LeftBottom;
    QRectF r_RightTop;
    QRectF r_RightBottom;
    QRectF r_TopMiddle;
    QRectF r_BottomMiddle;
    QRectF r_LeftMiddle;
    QRectF r_RightMiddle;*/

    m_handlesArea r_curHandle;


    qreal m_HandleSize = 1.0;

    QRectF m_rect;

};

#endif // BASEOBJECT_H
