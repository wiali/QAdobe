#include "graphicsview.h"

#include <QGraphicsItem>
#include <QMouseEvent>
#include <QDebug>
#define HaddleSize 12
GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);

    initHandles();
//    qDebug()<< parent->width()<< parent->height();
    this->setFixedSize(parent->width(), parent->height());
    scene->setSceneRect(0,0,parent->width(), parent->height());
//    scene->setSceneRect(0,0,static_cast<QWidget *>(scene->parent())->size().width(),static_cast<QWidget *>(scene->parent())->size().height());

    this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    this->setScene(scene);

//    QMatrix matrix;
//    matrix.scale(1.2, 1.2);
//    matrix.rotate(60);

//    this->setMatrix(matrix);

//    this->setDragMode(QGraphicsView::ScrollHandDrag);

      QGraphicsRectItem *rect = scene->addRect(100, 100, 100,80);
//      rect->setFlags(QGraphicsItem::ItemIsFocusable| QGraphicsItem::ItemIsSelectable| QGraphicsItem::ItemIsMovable);
//      rect->setRect(100,20,50,500);
//      rect->boundingRect().adjust(10,10,10,10);
//      rect->setFlag(QGraphicsItem::ItemIsMovable);
//      rect->setFlags(QGraphicsItem::ItemIsSelectable);
//      rect->setFocus();
//      rect->setSelected(true);
        currentItem = rect;
//      rect->setCursor(Qt::SizeHorCursor);
//      rect->setFlag(QGraphicsItem::ItemIsFocusScope, true);
//     scene->addLine(10,10,58,65)->setFlags(QGraphicsItem::ItemIsFocusScope| QGraphicsItem::ItemIsMovable);//<< QGraphicsRectItem::Type << QGraphicsLineItem::Type;
//      rect->prepareGeometryChange();
    this->setMouseTracking(true);

        qDebug() << currentItem->pos() << currentItem->boundingRect();
}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{

//   currentItem->setSelected(true);
   setCursorShape(event,currentItem);

//   if(event->buttons() ==  Qt::LeftButton)
//   {
//        setCursor(Qt::ClosedHandCursor);
//   }
   QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::initHandles()
{
    QPen pen(Qt::green);

    handles[Top] =  scene->addRect(-HaddleSize/2,-HaddleSize/2,HaddleSize,HaddleSize,pen);
    handles[TopLeft] =  scene->addRect(-HaddleSize/2,-HaddleSize/2,HaddleSize,HaddleSize,pen);
    handles[TopRight] =  scene->addRect(-HaddleSize/2,-HaddleSize/2,HaddleSize,HaddleSize,pen);
    handles[Left] =  scene->addRect(-HaddleSize/2,-HaddleSize/2,HaddleSize,HaddleSize,pen);
    handles[Right] =  scene->addRect(-HaddleSize/2,-HaddleSize/2,HaddleSize,HaddleSize,pen);
    handles[Bottom] =  scene->addRect(-HaddleSize/2,-HaddleSize/2,HaddleSize,HaddleSize,pen);
    handles[BottmLeft] =  scene->addRect(-HaddleSize/2,-HaddleSize/2,HaddleSize,HaddleSize,pen);
    handles[BottomRight] =  scene->addRect(-HaddleSize/2,-HaddleSize/2,HaddleSize,HaddleSize,pen);

//    for(int i =0; i <8; i++)
//        handles[i]->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
}


void GraphicsView::setCursorShape(QMouseEvent *event, QGraphicsItem * item)
{
    QPoint pos = event->pos();
    if(handles[Top] == itemAt(pos)){
        setCursor(Qt::SizeVerCursor);
        qreal xpos = item->pos().x();
        qreal ypos = event->y()+HaddleSize/2;
        qDebug() << handles[Top]->pos() << pos;
        handles[Top]->setPos(xpos, ypos);
        item->boundingRect().setTop(ypos);
    }


//    QRectF rect(item->pos().toPoint(),item->boundingRect().toRect().size());
    handleSelectedItems(item->boundingRect());

    /*setCursor(Qt::ArrowCursor);
    if(itemAt(pos) == handles[Top] || handles[Bottom] == itemAt(pos)){//left top
        setCursor(Qt::SizeVerCursor);

    }else if(itemAt(pos) == handles[Right] || handles[Left] == itemAt(pos)){
        setCursor(Qt::SizeHorCursor);
    }else if(itemAt(pos) == handles[TopLeft] || handles[BottomRight] == itemAt(pos)){
        setCursor(Qt::SizeFDiagCursor);
    }else if(itemAt(pos) == handles[BottmLeft] || handles[TopRight] == itemAt(pos)){
        setCursor(Qt::SizeBDiagCursor);
    }else if(rect.contains(pos)){
        setCursor(Qt::OpenHandCursor);
    }*/

}

void GraphicsView::handleSelectedItems(const QRectF &rect)
{
    qDebug() << rect;
    handles[Top]->setPos(rect.center().x(), rect.top());
    handles[TopLeft]->setPos(rect.left(),rect.top());//
    handles[TopRight]->setPos(rect.right(), rect.top());
    handles[Left]->setPos(rect.left(), rect.center().y());
    handles[Right]->setPos(rect.right(), rect.center().y());
    handles[BottmLeft]->setPos(rect.left(),rect.bottom());
    handles[BottomRight]->setPos(rect.right(),rect.bottom());
    handles[Bottom]->setPos(rect.center().x(), rect.bottom());

}

//void GraphicsView::mousePressEvent(QMouseEvent *event)
//{
//    QGraphicsView::mousePressEvent(event);
////     for(QGraphicsItem *item : scene->items()){
////         qDebug()<<item << item->pos();
//////         item->setPos(event->pos());
////     }
//}
