#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include "statemachine.h"
#include "singleton.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    singleton_t<PhotoshopStateMachine>::instance().start();

//    machine.start();
    QFile qssFile(":/qss/default.qss");

    if(qssFile.open(QFile::ReadOnly))
    {
       a.setStyleSheet(QLatin1String(qssFile.readAll()));
    }

    MainWindow w;
    w.show();

    return a.exec();
}
