#include "graphicsview.h"

#include <QGraphicsItem>
#include <QMouseEvent>
#include <QDebug>
#define HANDLESIZE 12
GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);

    this->setFixedSize(parent->width(), parent->height());
    scene->setSceneRect(0,0,parent->width(), parent->height());

    this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setScene(scene);

    this->currentItem = scene->addPixmap(QPixmap(":/img/000181.jpg"));
    this->currentItem->setFlags(QGraphicsItem::ItemIsFocusable| QGraphicsItem::ItemIsSelectable| QGraphicsItem::ItemIsMovable);
    this->currentItem = scene->addRect(100, 80, 100,80);
    this->currentItem->setFlags(QGraphicsItem::ItemIsFocusable| QGraphicsItem::ItemIsSelectable| QGraphicsItem::ItemIsMovable);
    this->currentItem->setSelected(true);
    this->createHandles(currentItem);
    this->currentGroup->setFlags(QGraphicsItem::ItemIsMovable);
}

GraphicsView::~GraphicsView()
{
    if(currentGroup != nullptr){
        this->scene->destroyItemGroup(currentGroup);
        delete currentGroup;
    }

    while(!this->handles.isEmpty()){
        delete handles.takeFirst();
    }

    if(currentItem != nullptr){
        delete currentItem;
    }
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
   setCursorShape(event->pos());

   QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() ==  Qt::LeftButton)
    {
        leftPressed = true;
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    leftPressed = false;

    QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::createHandles(QGraphicsItem *item)
{
    QPen pen(Qt::green);
    if(!this->handles.isEmpty()){
        for(int i=0; i<8; i++)
        this->scene->removeItem(handles[i]);
        this->handles.clear();
        if(currentGroup != nullptr)
            this->scene->destroyItemGroup(currentGroup);
    }
    this->handles << scene->addRect(-HANDLESIZE/2,-HANDLESIZE/2,HANDLESIZE,HANDLESIZE,pen);
    this->handles << scene->addRect(-HANDLESIZE/2,-HANDLESIZE/2,HANDLESIZE,HANDLESIZE,pen);
    this->handles << scene->addRect(-HANDLESIZE/2,-HANDLESIZE/2,HANDLESIZE,HANDLESIZE,pen);
    this->handles << scene->addRect(-HANDLESIZE/2,-HANDLESIZE/2,HANDLESIZE,HANDLESIZE,pen);
    this->handles << scene->addRect(-HANDLESIZE/2,-HANDLESIZE/2,HANDLESIZE,HANDLESIZE,pen);
    this->handles << scene->addRect(-HANDLESIZE/2,-HANDLESIZE/2,HANDLESIZE,HANDLESIZE,pen);
    this->handles << scene->addRect(-HANDLESIZE/2,-HANDLESIZE/2,HANDLESIZE,HANDLESIZE,pen);
    this->handles << scene->addRect(-HANDLESIZE/2,-HANDLESIZE/2,HANDLESIZE,HANDLESIZE,pen);

    this->handles << item;

    this->currentGroup = this->scene->createItemGroup(handles);

    this->handleSelectedItems(currentItem->boundingRect());
}


void GraphicsView::setCursorShape(const QPoint &pos)
{

    if(leftPressed) {
        if(cursor().shape() == Qt::OpenHandCursor){
            return setCursor(Qt::ClosedHandCursor);
        }else if(cursor().shape() == Qt::ClosedHandCursor){
            return;
        }else{
//            this->setDragMode(QGraphicsView::NoDrag);
            this->currentGroup->setFlag(QGraphicsItem::ItemIsMovable,false);
            return resizeCurrentItem(pos);
        }
    }
//    qDebug() << "set cursor";
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
        this->currentGroup->setFlag(QGraphicsItem::ItemIsMovable);
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

        }else if(this->currentHandle == BottmLeft){
            xpos = pos.x()+HANDLESIZE/2;
            ypos = pos.y()+HANDLESIZE/2;

            if(xpos > rect.right() || rect.bottom() < ypos) return;

            this->handles[BottmLeft]->setPos(xpos, ypos);
            rect.setBottomLeft(QPoint(xpos,ypos));
            rect.setRight(rect.right()-1);
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
        handleSelectedItems(this->currentItem->boundingRect());
        this->createHandles(this->currentItem);
    }

}

void GraphicsView::handleSelectedItems(const QRectF &rect)
{
    handles[Top]->setPos(rect.center().x(), rect.top());
    handles[TopLeft]->setPos(rect.left(),rect.top());//
    handles[TopRight]->setPos(rect.right(), rect.top());
    handles[Left]->setPos(rect.left(), rect.center().y());
    handles[Right]->setPos(rect.right(), rect.center().y());
    handles[BottmLeft]->setPos(rect.left(),rect.bottom());
    handles[BottomRight]->setPos(rect.right(),rect.bottom());
    handles[Bottom]->setPos(rect.center().x(), rect.bottom());

}


