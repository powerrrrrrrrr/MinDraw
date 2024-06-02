#ifndef ELLIPSEOBJECT_H
#define ELLIPSEOBJECT_H

#include "baseobject.h"

class EllipseObject : public BaseObject
{
public:
    EllipseObject(EllipseObject* parent = nullptr);
    ~EllipseObject() override;

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    BaseObject::OBJTYPE objType() const override;

    void setPenColor(QColor color);

    QColor getPenColor();
    QColor m_beforecolor;

    QColor m_color = gPen.color();
};

#endif // ELLIPSEOBJECT_H
