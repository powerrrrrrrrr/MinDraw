#include "lineobject.h"

#include <QDebug>

LineObject::LineObject(BaseObject* parent)
    : BaseObject(parent)

{
}

LineObject::~LineObject()
{

}

QRectF LineObject::boundingRect() const
{

    return QRectF(startPos,endPos);
}

void LineObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing, true);
    gPen.setColor(m_color);
    painter->setPen(gPen);
    painter->drawLine(startPos, endPos);

    if(this->isSelected()){
        drawSelectedRect(painter);
    }
}

BaseObject::OBJTYPE LineObject::objType() const
{
    return BaseObject::Line;
}


void LineObject::setPenColor(QColor color)
{
    m_beforecolor = m_color;
    m_color = color;

}

QColor LineObject::getPenColor()
{

    QColor col = m_beforecolor;
    m_beforecolor = m_color;
    m_color = col;
    return col;
}
