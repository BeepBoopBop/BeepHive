#include <boost/serialization/base_object.hpp>
#include <boost/mpi.hpp>
#include <string>
#include <iostream>
#include <sstream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "robot.h"

namespace mpi=boost::mpi;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  newDebug = NULL;
  newAgent = NULL;
  newEnvironment = NULL;

  started = false;

  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  setCentralWidget(ui->graphicsView);

  //automatically trigger updates for now
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(timeToStep()));
  timer->start(10);

  //connect menus to their corresponding slots
  connect(ui->actionStep,SIGNAL(triggered()),this,SLOT(timeToStep()));
  connect(ui->actionAgent, SIGNAL(triggered()), this, SLOT(createNewAgentWindow()));
  connect(ui->actionEnvironment, SIGNAL(triggered()), this, SLOT(createNewEnvironmentWindow()));
  connect(ui->actionStart, SIGNAL(triggered()), this, SLOT(startSimulation()));


  QGraphicsEllipseItem *tempEllipse = new QGraphicsEllipseItem();
  for(int i = 0; i < 2; i++){
    Robot tempRobot = Robot();
    tempRobot.setBody(tempEllipse);
    robots.push_back(tempRobot);
  }

  for(int i = 0; i<robots.size(); i++){
    robots[i].updateDrawPosition(scene);
  }

  reDraw();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
  qDebug() << "pos: " << event->pos().x() << " " << event->pos().y();

  //create new window
  if(newDebug) delete newDebug;
  newDebug = new DebugWindow();
  newDebug->show();
  connect(timer, SIGNAL(timeout()), newDebug, SLOT(updateText()));

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
  newDebug->setRobotToMonitor(minRobot);
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

//******************************************
//                  SLOTS                  *
//******************************************
void MainWindow::timeToStep(){
  if(!started) return;
  if(scene) delete scene;
  scene = NULL;


  mpiWaitForUpdates();
  mpiLoadUpdates();
  reDraw();
}


void MainWindow::createNewAgentWindow(){
  if(newAgent) delete newAgent;
  newAgent = new CreateAgent();
  newAgent->show();
  connect(newAgent, SIGNAL(accepted()), this, SLOT(newAgentCreated()));
}

void MainWindow::createNewEnvironmentWindow(){
  if(newEnvironment) delete newEnvironment;
  newEnvironment = new CreateEnvironment();
  newEnvironment->show();
  connect(newEnvironment, SIGNAL(accepted()), this, SLOT(newEnvironmentCreated()));
}

void MainWindow::newAgentCreated(){
  Robot tempRobot = Robot(newAgent->getX(), newAgent->getY());
  robots.push_back(tempRobot);
  reDraw();
}

void MainWindow::newEnvironmentCreated(){
  EnvironmentObject tempEnvironmentObject(newEnvironment->getX(), newEnvironment->getY(),
                                          newEnvironment->getWidth(), newEnvironment->getHeight());
  environmentObjects.push_back(tempEnvironmentObject);
  reDraw();
}

void MainWindow::startSimulation(){
  started = true;
  //implement this function to start
  mpiStart();
}


void MainWindow::reDraw(){
  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  scene->setSceneRect(0,0,400,400);

  //redraw robots

  // NOTE -IF WE FIX UPDATES USE robots[i].updateDrawPosition(scene)
  for(int i = 0; i<robots.size(); i++){
    //robots[i].randUpdateDrawPosition(scene);
    robots[i].updateDrawPosition(scene);
   }

  //redraw environment objects
  for(int i = 0; i<environmentObjects.size(); i++){
    environmentObjects[i].updateDrawPosition(scene);
  }

 }


 //*********************************************************************************
 /**************************************
  *  BACKEND/MPI FUNCTIONS TO IMPLEMENT*
  **************************************/
 //*********************************************************************************

 //NOTE1: --LEAVE THESE BLANK FOR STAND ALONE GUI WITH RANDOM UPDATES TO AGENTS!--
 //NOTE2: --SEE REDRAW IF THESE ARE IMPLEMENTED CORRECTLY--

/*
 * suggested functions to implement:
        mpiStringToRobot(string)
        robotToMpiString(robot)
 */

//code to start the backend, you will need to pass robot info to it
void MainWindow::mpiStart()
{
   return;
}

//block execution until an update is received
void MainWindow::mpiWaitForUpdates()
{

  mpi::communicator comm;
  std::vector<std::string> updates;
  comm.barrier();

  double x,y;
  //Receive messages from each process
  std::string send;
  gather(comm,send,updates,0);
  for(int i=1;i<updates.size();++i){
    //std::cout << "Rank " << i << " sent: " << updates[i] << std::endl;
    if(updates[i] == "exit"){
      //run=false;
    }
    std::cout << "In String: " << updates[i] << std::endl;
    std::stringstream data(updates[i]);
    int j=0;
    while(data >> x >> y){
      std::cout << "Setting Position: " << x << " " << y << std::endl;
      while(j>=robots.size()){
        Robot robot=Robot();
        robots.push_back(robot);
      }
      robots[j++].setPosition(x,y);
    }
  }

  /*
   * Send updates uniformly to all processes
   * Messages from GUI should be short because they are generated by user
   * input. However, we don't have MPI3 instant collectives which would be
   * required to implement an algorithm that only sends to specific
   * processes
   */

  send="Hi I'm root!";
  broadcast(comm,send,0);

  return;
}

 //load updates into robots and environmentObjects vectors
 //only need to load robot updates, environment objects are fixed!
 void MainWindow::mpiLoadUpdates(){
   return;
 }
