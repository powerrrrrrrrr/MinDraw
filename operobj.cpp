#include "operobj.h"

OperObj::OperObj(BaseObject* parent)
    : BaseObject(parent)
{

}

QRectF OperObj::boundingRect() const
{
    return QRectF(-1,-1,2,2);
}

void OperObj::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
