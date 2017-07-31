#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QButtonGroup> 
#include "graphicsview.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
     
private:
    Ui::MainWindow *ui;
//    QSignalMapper *signalMapper;
    QStringList nameTools;
    GraphicsView *graphicsView;
    QButtonGroup *groupTools;
};

#endif // MAINWINDOW_H
