#ifndef OPEROBJ_H
#define OPEROBJ_H

#include "baseobject.h"

class OperObj : public BaseObject
{
    Q_OBJECT
public:
    OperObj(BaseObject* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};

#endif // OPEROBJ_H
