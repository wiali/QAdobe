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
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
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
     QGraphicsItemGroup *currentGroup;
     QList<QGraphicsItem *> handles;
     QGraphicsScene *scene;
     QGraphicsItem *currentItem;
     ITEM_HANDLE currentHandle;

     bool leftPressed = false;
     void initHandles();
     void handleSelectedItems(const QRectF &rect);
     void setCursorShape(const QPoint &pos);
     void resizeCurrentItem(const QPointF &pos);

};

#endif // GRAPHICSVIEW_H
