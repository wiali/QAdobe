#include "graphicsview.h"

#include <QGraphicsItem>
#include <QMouseEvent>
#include <QDebug>
#define HANDLESIZE 12
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

      currentItem = scene->addRect(100, 100, 100,80);
      currentItem->setFlags(QGraphicsItem::ItemIsFocusable| QGraphicsItem::ItemIsSelectable| QGraphicsItem::ItemIsMovable);
//      rect->setRect(100,20,50,500);
//      rect->boundingRect().adjust(10,10,10,10);
//      rect->setFlag(QGraphicsItem::ItemIsMovable);
//      rect->setFlags(QGraphicsItem::ItemIsSelectable);
//      rect->setFocus();
//      rect->setSelected(true);

//      rect->setCursor(Qt::SizeHorCursor);
//      rect->setFlag(QGraphicsItem::ItemIsFocusScope, true);
//     scene->addLine(10,10,58,65)->setFlags(QGraphicsItem::ItemIsFocusScope| QGraphicsItem::ItemIsMovable);//<< QGraphicsRectItem::Type << QGraphicsLineItem::Type;
//      rect->prepareGeometryChange();
//    this->setMouseTracking(true);


        qDebug() << currentItem->pos() << currentItem->boundingRect();
         handleSelectedItems(currentItem->boundingRect());
//         currentGroup->setSelected(true);
         currentGroup->addToGroup(currentItem);
         this->setDragMode(QGraphicsView::RubberBandDrag);
}

GraphicsView::~GraphicsView()
{
    if(currentGroup != nullptr){
        delete currentGroup;
    }
    if(currentItem != nullptr){
        delete currentItem;
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug() << "mouseMoveEvent" << leftPressed;

//   currentItem->setSelected(true);
   setCursorShape(event->pos());



   QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mousePressEvent";
    if(event->buttons() ==  Qt::LeftButton)
    {
        leftPressed = true;
 //        setCursor(Qt::ClosedHandCursor);
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "mouseReleaseEvent";
    leftPressed = false;

    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::initHandles()
{
    QPen pen(Qt::green);

    handles << scene->addRect(-HANDLESIZE/2,-HANDLESIZE/2,HANDLESIZE,HANDLESIZE,pen);
    handles << scene->addRect(-HANDLESIZE/2,-HANDLESIZE/2,HANDLESIZE,HANDLESIZE,pen);
    handles << scene->addRect(-HANDLESIZE/2,-HANDLESIZE/2,HANDLESIZE,HANDLESIZE,pen);
    handles << scene->addRect(-HANDLESIZE/2,-HANDLESIZE/2,HANDLESIZE,HANDLESIZE,pen);
    handles << scene->addRect(-HANDLESIZE/2,-HANDLESIZE/2,HANDLESIZE,HANDLESIZE,pen);
    handles << scene->addRect(-HANDLESIZE/2,-HANDLESIZE/2,HANDLESIZE,HANDLESIZE,pen);
    handles << scene->addRect(-HANDLESIZE/2,-HANDLESIZE/2,HANDLESIZE,HANDLESIZE,pen);
    handles << scene->addRect(-HANDLESIZE/2,-HANDLESIZE/2,HANDLESIZE,HANDLESIZE,pen);

    currentGroup = this->scene->createItemGroup(handles);

    currentGroup->setFlags(QGraphicsItem::ItemIsMovable);


//    for(int i =0; i <8; i++)
//        handles[i]->setFlags(QGraphicsItem::ItemIsMovable);
}


void GraphicsView::setCursorShape(const QPoint &pos)
{
    qDebug() << leftPressed;
    if(leftPressed) {
        if(cursor().shape() == Qt::OpenHandCursor){

            return setCursor(Qt::ClosedHandCursor);
        }/*else if(cursor().shape() == Qt::ClosedHandCursor){
            return
        }*/else{
            this->setDragMode(QGraphicsView::NoDrag);
            return resizeCurrentItem(pos);
        }
    }
    if(itemAt(pos) == handles[Top]){

        currentHandle = Top;
        setCursor(Qt::SizeVerCursor);

    } else if( handles[Bottom] == itemAt(pos)){//left top

        currentHandle = Bottom;
        setCursor(Qt::SizeVerCursor);

    }else if(itemAt(pos) == handles[Right] ){

        currentHandle = Right;
        setCursor(Qt::SizeHorCursor);

    }else if( handles[Left] == itemAt(pos)){

        currentHandle = Left;
        setCursor(Qt::SizeHorCursor);

    }else if(itemAt(pos) == handles[TopLeft]){

        currentHandle = TopLeft;
        setCursor(Qt::SizeFDiagCursor);

    } else if( handles[BottomRight] == itemAt(pos)){

        currentHandle = BottomRight;
        setCursor(Qt::SizeFDiagCursor);

    }else if(itemAt(pos) == handles[BottmLeft]){

        currentHandle = BottmLeft;
        setCursor(Qt::SizeBDiagCursor);

    }else if( handles[TopRight] == itemAt(pos)){

        currentHandle = TopRight;
        setCursor(Qt::SizeBDiagCursor);

    }else if(currentItem->boundingRect().contains(pos)){

        setCursor(Qt::OpenHandCursor);
    }else{
        setCursor(Qt::ArrowCursor);
    }

}

void GraphicsView::resizeCurrentItem(const QPointF &pos)
{
    bool resizing = false;
    qreal xpos, ypos;
    QRect rect = this->currentItem->sceneBoundingRect().toRect();
    if(cursor().shape() == Qt::SizeVerCursor){
        resizing = true;
        if(this->currentHandle == Top){
            xpos = handles[Top]->pos().x();
            ypos = pos.y()+HANDLESIZE/2;

            if(ypos > rect.bottom()) return;

            this->handles[Top]->setPos(xpos, ypos);

            rect.setTop(ypos);
            rect.setBottomRight(QPoint(rect.right()-1,rect.bottom()-1));

        }else if(this->currentHandle == Bottom){
            xpos = handles[Bottom]->pos().x();
            ypos = pos.y()+HANDLESIZE/2;

            if(ypos < rect.top()) return;

            this->handles[Bottom]->setPos(xpos, ypos);

            rect.setBottom(ypos);
            rect.setRight(rect.right()-1);
        }
    }else if(cursor().shape() == Qt::SizeHorCursor){
        resizing = true;
        if(this->currentHandle == Left){
            xpos = pos.x()+HANDLESIZE/2;
            ypos = handles[Left]->pos().y();

            if(xpos > rect.right()) return;

            this->handles[Left]->setPos(xpos, ypos);
            rect.setLeft(xpos);
            rect.setBottomRight(QPoint(rect.right()-1,rect.bottom()-1));
        }else if(this->currentHandle == Right){
            xpos = pos.x()+HANDLESIZE/2;
            ypos = handles[Right]->pos().y();

            if(xpos < rect.left()) return;

            this->handles[Right]->setPos(xpos, ypos);

            rect.setRight(xpos);
            rect.setBottom(rect.bottom()-1);
        }
    }else if(cursor().shape() == Qt::SizeFDiagCursor){
        resizing = true;
        if(this->currentHandle == TopLeft){
            xpos = pos.x()+HANDLESIZE/2;
            ypos = pos.y()+HANDLESIZE/2;

            if(xpos > rect.right() || rect.bottom() < ypos) return;

            this->handles[TopLeft]->setPos(xpos, ypos);
            rect.setTopLeft(QPoint(xpos,ypos));
            rect.setBottomRight(QPoint(rect.right()-1,rect.bottom()-1));

        }else if(this->currentHandle == BottomRight){
            xpos = pos.x()+HANDLESIZE/2;
            ypos = pos.y()+HANDLESIZE/2;

            if(xpos < rect.left() || rect.top() > ypos) return;

            this->handles[BottomRight]->setPos(xpos, ypos);
            rect.setBottomRight(QPoint(xpos,ypos));
//            rect.setRight(rect.right()-1);
//            rect.setBottom(rect.bottom()-1);
        }
    }else if(cursor().shape() == Qt::SizeBDiagCursor){
        resizing = true;
        if(this->currentHandle == TopRight){
            xpos = pos.x()+HANDLESIZE/2;
            ypos = pos.y()+HANDLESIZE/2;

            if(xpos < rect.left() || rect.bottom() < ypos) return;

            this->handles[TopRight]->setPos(xpos, ypos);
            rect.setTopRight(QPoint(xpos,ypos));
            rect.setBottom(rect.bottom()-1);
//            rect.setBottomRight(QPoint(rect.right()-1,rect.bottom()-1));

        }else if(this->currentHandle == BottmLeft){
            xpos = pos.x()+HANDLESIZE/2;
            ypos = pos.y()+HANDLESIZE/2;

            if(xpos > rect.right() || rect.bottom() < ypos) return;

            this->handles[BottmLeft]->setPos(xpos, ypos);
            rect.setBottomLeft(QPoint(xpos,ypos));
            rect.setRight(rect.right()-1);
//            rect.setRight(rect.right()-1);
//            rect.setBottom(rect.bottom()-1);
        }
    }
    if(resizing){

        this->scene->removeItem(this->currentItem);
        switch (currentItem->type())
        {
        case QGraphicsRectItem::Type:

             this->currentItem = this->scene->addRect(rect);


            break;
        default:
            break;
        }
    }
    this->currentGroup->addToGroup(this->currentItem);
    handleSelectedItems(currentItem->boundingRect());
}

void GraphicsView::handleSelectedItems(const QRectF &rect)
{
//    qDebug() << rect;

    handles[Top]->setPos(rect.center().x(), rect.top());
    handles[TopLeft]->setPos(rect.left(),rect.top());//
    handles[TopRight]->setPos(rect.right(), rect.top());
    handles[Left]->setPos(rect.left(), rect.center().y());
    handles[Right]->setPos(rect.right(), rect.center().y());
    handles[BottmLeft]->setPos(rect.left(),rect.bottom());
    handles[BottomRight]->setPos(rect.right(),rect.bottom());
    handles[Bottom]->setPos(rect.center().x(), rect.bottom());

}


