#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
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
     QGraphicsScene *scene;

     void setCursorShape(const QPoint &pos, const QRect &rect);
};

#endif // GRAPHICSVIEW_H
