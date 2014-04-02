#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "robot.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  newDebug = 0;
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

void MainWindow::mousePressEvent(QMouseEvent *event)
{
  qDebug() << "pos: " << event->pos().x() << " " << event->pos().y();

  //create new window
  if(!newDebug){
    newDebug = new DebugWindow();
    newDebug->show();
    connect(timer, SIGNAL(timeout()), newDebug, SLOT(updateText()));
  }

  //assign the window the robot closest to the click point
  int xLoc = event->pos().x();
  int yLoc = event->pos().y();
  int minDistance = 9999;
  Robot* minRobot = NULL;
  for(int i = 0; i < robots.size(); i++){
    robots[i].resetColor();
    int tempDistance = robots[i].distanceFromPoint(xLoc, yLoc);
    if(tempDistance < minDistance){
      minDistance = tempDistance;
      minRobot = &robots[i];
    }
  }
  minRobot->highlightGreen();
  return;
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
