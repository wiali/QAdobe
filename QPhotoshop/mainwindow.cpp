#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>
#include "singleton.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graphicsView = new GraphicsView(this);
    groupTools = new QButtonGroup(this);
 


    this->setCentralWidget(graphicsView);
    nameTools << "\ue63d"<< "\ue64c"<<"\ue614"<<"\ue605"<<"\ue600" << "\ue633" << "\ue649";
    for(int i =0 ; i < nameTools.length(); i++)
    {
       
        QPushButton *bt = new QPushButton(nameTools[i]);
        bt->setFont(QFont("iconfont"));
        bt->setCheckable(true);

        groupTools->addButton(bt, i);
        ui->dockWidgetContents_Tools->layout()->addWidget(bt);
    }
    connect(groupTools, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
          [=](int id){qDebug() << id; /* ... */ });

}

MainWindow::~MainWindow()
{
//    delete signalMapper;
    delete graphicsView;
    delete groupTools;
    delete ui;

}

 
