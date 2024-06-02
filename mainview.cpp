#include "mainview.h"

#include <QDebug>

QColor MainView::gXYLineColor = QColor(0,255,255);

MainView::MainView(QWidget *parent)
    : QGraphicsView(parent)
    , IS_MOVE(false)
{
    init();
}

MainView::MainView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(parent)
    , IS_MOVE(false)
{
    this->setScene(scene);
    init();
}

void MainView::init()
{
    //设置渲染选项：抗锯齿，平滑像素变换，文本抗锯齿，无损图像渲染
    this->setRenderHints(QPainter::Antialiasing |
                         QPainter::SmoothPixmapTransform |
                         QPainter::TextAntialiasing |
                         QPainter::LosslessImageRendering);
    //设置坐标变换的锚点为鼠标位置
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //设置视图更新模式为全视图更新模式
    //视图中任意部分发生变化，整个视图都会进行更新
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    //禁用滚动条
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //设置可以使用鼠标拖动一个矩形来选择图形项
    this->setDragMode(QGraphicsView::RubberBandDrag);
    //设置了上下文菜单策略为自定义上下文菜单
    this->setContextMenuPolicy(Qt::CustomContextMenu);

}

void MainView::setMagnify()
{
    scale(1.1,1.1);
}

void MainView::setReduce()
{
    scale(0.9,0.9);
}

void MainView::mouseMoveEvent(QMouseEvent *event)
{
    emit viewPosChange(mapToScene(event->pos()));

    if(event->buttons() == Qt::MiddleButton && IS_MOVE){
        //设置新的中心点，实现视图移动效果

        this->setCursor(Qt::ClosedHandCursor);

        QPointF posOffset = event->pos() - mLastPoint;
        mLastPoint = event->pos();

        int w = viewport()->rect().width() / 2;
        int h = viewport()->rect().height() / 2;

        QPoint newCenter(w - posOffset.x() + 0.5, h - posOffset.y() + 0.5);
        centerOn(mapToScene(newCenter));

        this->scene()->update();
    }
    else{
        QGraphicsView::mouseMoveEvent(event);
    }
}

void MainView::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::MiddleButton){
        mLastPoint = event->pos();
        IS_MOVE = true;
        this->setCursor(Qt::OpenHandCursor);
    }
    else{
        QGraphicsView::mousePressEvent(event);
    }
}



void MainView::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCursor(Qt::ArrowCursor);
    if(event->buttons() == Qt::MiddleButton){
        IS_MOVE = false;
    }
    else{
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void MainView::wheelEvent(QWheelEvent *event)
{
    qDebug() << "wheel";
    event->angleDelta().y() > 0 ? scale(1.1, 1.1) : scale(0.9, 0.9);
}
