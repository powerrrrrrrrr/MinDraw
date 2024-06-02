#ifndef LINEOBJECT_H
#define LINEOBJECT_H

#include <QPainter>

#include "baseobject.h"

class LineObject : public BaseObject
{
public:
    LineObject(BaseObject* parent = nullptr);
    ~LineObject() override;

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    BaseObject::OBJTYPE objType() const;

    void setPenColor(QColor color);
    QColor getPenColor();
    QColor m_beforecolor;

private:
    QColor m_color = gPen.color();

};

#endif // LINEOBJECT_H
