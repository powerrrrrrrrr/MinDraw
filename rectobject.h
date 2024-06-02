#ifndef RECTOBJECT_H
#define RECTOBJECT_H

#include "baseobject.h"
#include <QPainter>
#include <QPointF>
class RectObject : public BaseObject
{
public:
    RectObject(RectObject* parent = nullptr);
    ~RectObject() override;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    BaseObject::OBJTYPE objType() const override;
    void setPenColor(QColor color);

    QColor getPenColor();
    QColor m_beforecolor;

    QColor m_color = gPen.color();
};

#endif // RECTOBJECT_H
