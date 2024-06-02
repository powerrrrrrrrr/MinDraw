#include "rectobject.h"

RectObject::RectObject(RectObject* parent)
    : BaseObject(parent)
{

}

RectObject::~RectObject()
{

}

QRectF RectObject::boundingRect() const
{
    return QRectF(startPos, endPos);
}

void RectObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing, true);
    gPen.setColor(m_color);
    painter->setPen(gPen);
    painter->drawRect(this->boundingRect());

    if(this->isSelected()){
        drawSelectedRect(painter);
    }
}

BaseObject::OBJTYPE RectObject::objType() const
{
    return BaseObject::Rect;
}

void RectObject::setPenColor(QColor color)
{
    m_beforecolor = m_color;
    m_color = color;
}

QColor RectObject::getPenColor()
{
    QColor col = m_beforecolor;
    m_beforecolor = m_color;
    m_color = col;
    return col;
}

