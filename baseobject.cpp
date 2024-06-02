#include "baseobject.h"

#include "mainview.h"
#include "mainscene.h"

static const char objTypeString_string[] = {
    "Base\0"
    "Line\0"
    "Rect\0"
    "Text\0"
    "Ellipse\0"
};

static const short objTypeString_indices[] = {
    0, 5, 10, 15, 20, 28, 0
};

QColor BaseObject::gBorderColor = QColor(8,255,200);
QColor BaseObject::gObjectColor = Qt::white;
qreal BaseObject::gMoveOffset = 10;


BaseObject::BaseObject(QGraphicsObject* parent)
    : QGraphicsObject(parent)
    , beSelected(false)
    , myObjectColor(BaseObject::gObjectColor)
    , myPenWidthF(1)
{
    //设置鼠标和交互行为
    //设置接受鼠标左键和右键事件
    this->setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
    //设置items接受鼠标悬停事件
    this->setAcceptHoverEvents(true);
    //设置items可以被移动、被选择、接受焦点
    this->setFlags(QGraphicsItem::ItemIsMovable |
                   QGraphicsItem::ItemIsSelectable |
                   QGraphicsItem::ItemIsFocusable);


    gPen.setBrush(Qt::NoBrush);
    gPen.setColor(myObjectColor);
    gPen.setWidthF(myPenWidthF);
}

BaseObject::~BaseObject()
{

}

bool BaseObject::isLine() const
{
    return objType() == BaseObject::Line;
}

bool BaseObject::isRect() const
{
    return objType() == BaseObject::Rect;
}

void BaseObject::drawSelectedRect(QPainter *painter)
{
    QRectF rect = this->boundingRect();

    painter->setPen(QPen(BaseObject::gBorderColor, 0, Qt::DashLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(rect.adjusted(-1,-1,1,1));//向内缩一个像素，避免被剪裁
}

QString BaseObject::nameString() const
{
    return QLatin1String(objTypeString_string + objTypeString_indices[this->objType()]);
}

BaseObject::OBJTYPE BaseObject::objType() const
{
    return BaseObject::Base;
}


/*BaseObject::m_handlesArea BaseObject::getMouseHandle(QPointF p)
{
    QRectF rect = this->boundingRect();

    qreal left = rect.left();
    qreal right = rect.right();
    qreal top = rect.top();
    qreal bottom = rect.bottom();

    if(p.x() >= left - m_HandleSize && p.x() <= left + m_HandleSize){
        if(p.y() > bottom + m_HandleSize && p.y() < top - m_HandleSize){
            return BaseObject::LeftMiddle;
            qDebug() << "LeftMiddle";
        }
        else if(p.y() <= bottom + m_HandleSize && p.y() >= bottom - m_HandleSize){
            return BaseObject::LeftBottom;
            qDebug() << "LeftBottom";
        }
        else if(p.y() >= top - m_HandleSize && p.y() <= top + m_HandleSize){
            return BaseObject::LeftTop;
            qDebug() << "LeftTop";
        }
    }
    else if(p.x() >= right - m_HandleSize && p.x() <= right + m_HandleSize){
        if(p.y() > bottom + m_HandleSize && p.y() < top - m_HandleSize){
            return BaseObject::RightMiddle;
            qDebug() << "RightMiddle";
        }
        else if(p.y() <= bottom + m_HandleSize && p.y() >= bottom - m_HandleSize){
            return BaseObject::RightBottom;
            qDebug() << "RightBottom";
        }
        else if(p.y() >= top - m_HandleSize && p.y() <= top + m_HandleSize){
            return BaseObject::RightTop;
        }
    }
    else if(p.x() > left + m_HandleSize && p.x() < right - m_HandleSize){
        if(p.y() <= bottom + m_HandleSize && p.y() >= bottom - m_HandleSize){
            return BaseObject::BottomMiddle;
        }
        else if(p.y() >= top - m_HandleSize && p.y() <= top + m_HandleSize){
            return BaseObject::TopMiddle;
        }
    }
}*/


void BaseObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    beSelected = true;
    QGraphicsView* view = this->scene()->views()[0];//获取图元所属的view
    view->viewport()->setCursor(Qt::SizeAllCursor);//设置鼠标为手型

    QGraphicsObject::mousePressEvent(event);
}

void BaseObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    QGraphicsObject::mouseMoveEvent(event);
}

void BaseObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseReleaseEvent(event);
}

void BaseObject::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{

    if(!this->isSelected()){
        //gPen.setColor(Qt::red);
        this->setPenColor(Qt::red);
        update();
    }

    return QGraphicsItem::hoverEnterEvent(event);
}

void BaseObject::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QColor col = this->getPenColor();
    gPen.setColor(col);
    update();
    if(!beSelected) return;

    QGraphicsView* view = this->scene()->views()[0];
    view->viewport()->setCursor(Qt::ArrowCursor);

    return QGraphicsItem::hoverLeaveEvent(event);
}
