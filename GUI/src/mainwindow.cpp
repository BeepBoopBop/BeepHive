#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    setCentralWidget(ui->graphicsView);

    //automatically trigger updates for now
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeToStep()));
    timer->start(10);

    connect(ui->actionStep,SIGNAL(triggered()),this,SLOT(timeToStep()));


    QGraphicsEllipseItem *tempEllipse = new QGraphicsEllipseItem();
    for(int i = 0; i < 10; i++){
        Robot tempRobot = Robot();
        tempRobot.setBody(tempEllipse);
        robots.push_back(tempRobot);
    }

    for(int i = 0; i<robots.size(); i++){
        robots[i].updateDrawPosition(scene);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::moveAgents(){
    scene->clear();
}

void MainWindow::timeToStep(){
    if(scene) delete scene;
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    for(int i = 0; i<robots.size(); i++){
        robots[i].randUpdateDrawPosition(scene);
    }
}
