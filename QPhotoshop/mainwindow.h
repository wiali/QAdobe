#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
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
    onClicked(const QString &name);
private:
    Ui::MainWindow *ui;
    QSignalMapper *signalMapper;
    QStringList nameTools;
    GraphicsView *graphicsView;
};

#endif // MAINWINDOW_H
