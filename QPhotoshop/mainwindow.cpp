#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    signalMapper = new QSignalMapper(this);
    graphicsView = new GraphicsView(this);
    this->setCentralWidget(graphicsView);
    nameTools << "直线"<<"矩形"<<"圆形"<<"椭圆";
    for(QString name: nameTools)
    {
        QPushButton *bt = new QPushButton(name);
         connect(bt, SIGNAL(clicked()), signalMapper, SLOT(map()));
//        connect(bt, &QPushButton::clicked ,signalMapper, &QSignalMapper::map);
        signalMapper->setMapping(bt, name);
        ui->dockWidgetContents->layout()->addWidget(bt);
    }
    connect(signalMapper,SIGNAL(mapped( QString )), this, SLOT(onClicked( QString )));
}

MainWindow::~MainWindow()
{
    delete signalMapper;
    delete graphicsView;
    delete ui;
}

MainWindow::onClicked(const QString &name)
{


}

