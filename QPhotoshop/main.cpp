#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QDebug>

#include "statemachine.h"
#include "singleton.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    
    for(int i =1 ; i <31; i++){
        double v = (3.24 + (i-1)*0.0) / (i*7.3404+40) *100;
        qDebug() << "第" <<i << "年投资回报率："<< v << "%";
    }
    
    int font_id = QFontDatabase::addApplicationFont(":/fonts/FontAwesome.otf");
    int alifont_id = QFontDatabase::addApplicationFont(":/fonts/font_ali.ttf");

    QStringList fonts = QFontDatabase::applicationFontFamilies(alifont_id);
    for(QString name : fonts)
        qDebug() << name;

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
