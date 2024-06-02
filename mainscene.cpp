#include "mainscene.h"

#include <QtMath>
#include <QDebug>

int MainScene::gGridSize = 10;
int MainScene::gGridSquares = 5;
QColor MainScene::gBackgroundColor = QColor("#393939");
QColor MainScene::gForegroundColorDark = QColor("#292929");
QColor MainScene::gForegroundColorLight = QColor("#2f2f2f");


MainScene::MainScene(QObject* parent)
    : QGraphicsScene(parent)
{
    isDraw = false;

    measurePenColor = Qt::white;
    measurePen.setColor(measurePenColor);
}

void MainScene::setDrawType(DrawType type)
{
    m_DrawType = type;
    qDebug() << "set draw type :" << type;
}

void MainScene::setMyPenColor(QColor color)
{
    penColor = color;

    qDebug() << "setMyPenColor";
}

void MainScene::saveScene(QRect rect)
{
    QPixmap pixmap(rect.size());
    QPainter painter;
    painter.begin(&pixmap);
    this->render(&painter);
    painter.end();
    pixmap.save("D:/draw/scene.png");
}

void MainScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->setBrush(MainScene::gBackgroundColor);
    painter->setPen(MainScene::gBackgroundColor);
    painter->drawRect(rect);

    int left = qFloor(rect.left());//向下取整
    int right = qCeil(rect.right());//向上取整
    int top = qFloor(rect.top());
    int bottom = qCeil(rect.bottom());

    int _left = left - left % MainScene::gGridSize;//向坐标原点按网格边长取整
    int _top = top - top % MainScene::gGridSize;

    QVector<QLine> lightLines, darkLines;
    int wh = MainScene::gGridSize * MainScene::gGridSquares;

    for(int i = _left; i <= right; i += MainScene::gGridSize){
        if(i % wh == 0){
            darkLines.append(QLine(i, top, i, bottom));
        }
        else{
            lightLines.append(QLine(i, top, i, bottom));
        }
    }

    for(int i = _top; i <= bottom; i += MainScene::gGridSize){
        if(i % wh == 0){
            darkLines.append(QLine(left, i, right, i));
        }
        else{
            lightLines.append(QLine(left, i, right, i));
        }
    }


    painter->setBrush(Qt::NoBrush);
    painter->setPen(MainScene::gForegroundColorLight);
    painter->drawLines(lightLines);

    painter->setPen(MainScene::gForegroundColorDark);
    painter->drawLines(darkLines);
}


void MainScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_startPos = m_endPos = event->scenePos();
    if(event->buttons() == Qt::LeftButton){

        isDraw = true;
        qDebug() <<"isDraw is true";

        switch (m_DrawType) {
        case Rect:
        {
            qDebug() <<"rect is true";
            arect = new RectObject();
            if(!arect){
                qDebug() << "new arect succeed";
                break;
            }
            arect->startPos = event->scenePos();
            arect->endPos = event->scenePos();
            //arect->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
            arect->setPenColor(penColor);
            this->addItem(arect);
            update();
        }
        break;
        case Line:
        {
            qDebug() <<"aline is true";
            aline = new LineObject();
            if(!aline){
                qDebug() << "new aline succeed";
                break;
            }
            aline->startPos = event->scenePos();
            aline->endPos = event->scenePos();
            aline->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
            aline->setPenColor(penColor);
            this->addItem(aline);
            update();
        }
        break;
        case Ellipse:
        {
            qDebug() <<"Ellipse is true";
            aellipse = new EllipseObject();
            if(!aellipse){
                qDebug() << "new Ellipse succeed";
                break;
            }
            aellipse->startPos = event->scenePos();
            aellipse->endPos = event->scenePos();
            aellipse->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
            aellipse->setPenColor(penColor);
            this->addItem(aellipse);
            update();
        }
        break;
        case Trash:
        {
            qDebug() <<"Polygon is true";
            QGraphicsItem* item = itemAt(event->scenePos(), this->views().first()->transform());
            if(item){
                this->removeItem(item);
                update();
            }
        }
        break;
        case HorDistance:
        {
            qDebug() <<"HorDistance is true";

        }
        break;
        case None:
        {
            QGraphicsScene::mousePressEvent(event);
        }
        default:
            break;
        }
    }
}

void MainScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_endPos = event->scenePos();
    if(event->buttons() == Qt::LeftButton && isDraw){

        switch (m_DrawType) {
        case Rect:
        {
            //qDebug() << "moving";
            arect->endPos = event->scenePos();
            update();
        }
        break;
        case Line:
        {
            //qDebug() << "line moving";
            aline->endPos = event->scenePos();
            update();
        }
        break;
        case Ellipse:
        {
            //qDebug() << "ellipse moving";
            aellipse->endPos = event->scenePos();
            update();
        }
        break;
        case None:
        {
            QGraphicsScene::mouseMoveEvent(event);
        }
        case HorDistance:
        {
            //qDebug() << "ellipse moving";

        }
        break;
        default:
            break;
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void MainScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(isDraw){
        isDraw = false;
        qDebug() << "isDraw is false";
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

