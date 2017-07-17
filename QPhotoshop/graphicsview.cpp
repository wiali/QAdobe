#include "graphicsview.h"

#include <QGraphicsItem>
#include <QMouseEvent>
#include <QDebug>
GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);

    qDebug()<< parent->width()<< parent->height();
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

      QGraphicsRectItem *rect = scene->addRect(0, 0, 100,80);
      rect->setFlags(QGraphicsItem::ItemIsSelectable| QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
//      rect->setRect(100,20,50,500);
//      rect->boundingRect().adjust(10,10,10,10);
      rect->setSelected(true);

//      rect->setCursor(Qt::SizeHorCursor);
//      rect->setFlag(QGraphicsItem::ItemIsFocusScope, true);
scene->addLine(10,10,58,65)->setFlags(QGraphicsItem::ItemIsSelectable| QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);//<< QGraphicsRectItem::Type << QGraphicsLineItem::Type;
//      rect->prepareGeometryChange();
    this->setMouseTracking(true);
}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
   setCursor(Qt::ArrowCursor);
   QGraphicsItem *item = itemAt(event->pos());

   if(item == nullptr) return;

//  qDebug()<< item->boundingRect().size() << item->scenePos();
   setCursorShape(event->pos(),QRect(item->pos().toPoint(),item->boundingRect().toRect().size()));
   if(event->buttons() ==  Qt::LeftButton)
   {
        setCursor(Qt::ClosedHandCursor);
   }
   QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::setCursorShape(const QPoint &pos, const QRect &rect)
{
    qDebug() << pos << rect;
    if(rect.contains(pos)){

        setCursor(Qt::OpenHandCursor);
    }
}

//void GraphicsView::mousePressEvent(QMouseEvent *event)
//{
//    QGraphicsView::mousePressEvent(event);

////     for(QGraphicsItem *item : scene->items()){
////         qDebug()<<item << item->pos();

//////         item->setPos(event->pos());

////     }
//}
