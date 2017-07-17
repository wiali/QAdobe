#include "mainwindow.h"
#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QFile qssFile(":/qss/default.qss");

    if(qssFile.open(QFile::ReadOnly))
    {
       a.setStyleSheet(QLatin1String(qssFile.readAll()));
    }

    MainWindow w;
    w.show();

    return a.exec();
}
