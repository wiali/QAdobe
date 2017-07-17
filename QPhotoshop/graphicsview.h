#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
class QMouseEvent;
class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = nullptr);
    ~GraphicsView();


protected: 
    void mouseMoveEvent(QMouseEvent *event);
signals:

public slots:

private:
     enum ITEM_HANDLE{
         Top,
         TopLeft,
         TopRight,
         Left,
         Right,
         Bottom,
         BottmLeft,
         BottomRight,
     };
     QGraphicsRectItem  *handles[8];
     QGraphicsScene *scene;
     QGraphicsItem *currentItem;

     void initHandles();
     void handleSelectedItems(const QRectF &rect);
     void setCursorShape(QMouseEvent *event, QGraphicsItem *item);


};

#endif // GRAPHICSVIEW_H
