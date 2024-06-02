#include "ellipseobject.h"

EllipseObject::EllipseObject(EllipseObject* parent)
    : BaseObject(parent)
{

}

EllipseObject::~EllipseObject()
{

}

QRectF EllipseObject::boundingRect() const
{
    return QRectF(startPos, endPos);
}

void EllipseObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing, true);
    gPen.setColor(m_color);
    painter->setPen(gPen);
    painter->drawEllipse(this->boundingRect());

    if(this->isSelected()){
        drawSelectedRect(painter);
    }
}

BaseObject::OBJTYPE EllipseObject::objType() const
{
    return BaseObject::Ellipse;
}


void EllipseObject::setPenColor(QColor color)
{
    m_beforecolor = m_color;
    m_color = color;

}

QColor EllipseObject::getPenColor()
{
    QColor col = m_beforecolor;
    m_beforecolor = m_color;
    m_color = col;
    return col;
}

