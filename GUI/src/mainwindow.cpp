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
  newBeep = NULL;

  started = false;
  paused = false;

  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  setCentralWidget(ui->graphicsView);

  //automatically trigger updates for now
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(timeToStep()));
  timer->start(10);

  //connect menus to their corresponding slots
  connect(ui->actionStep,SIGNAL(triggered()),this,SLOT(timeToStep()));
  connect(ui->actionAgent_2, SIGNAL(triggered()), this, SLOT(createNewAgentWindow()));
  connect(ui->actionAdd_Environment, SIGNAL(triggered()), this, SLOT(createNewEnvironmentWindow()));
  connect(ui->actionStart, SIGNAL(triggered()), this, SLOT(startSimulation()));
  connect(ui->actionCreate_New_Beep, SIGNAL(triggered()), this, SLOT(createNewBeepTypeWindow()));

  /*for(int i = 5; i < 26; i++)
    for(int j = 15; j < 26; j++)
      pointTemps.push_back(std::make_pair (std::make_pair (i,j), 100));*/

  QGraphicsEllipseItem *tempEllipse = new QGraphicsEllipseItem();
  for(unsigned i = 0; i < 2; i++){
    Robot tempRobot = Robot();
    tempRobot.setBody(tempEllipse);
    robots.push_back(tempRobot);
  }

  for(unsigned i = 0; i<robots.size(); i++){
    robots[i].updateDrawPosition(scene);
  }
  reDraw();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
  if(!started) return;
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
  for(unsigned i = 0; i < robots.size(); i++){
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

void MainWindow::createNewBeepTypeWindow(){
  if(newBeep) delete newBeep;
  newBeep = new newBeepType();
  newBeep->show();
  connect(newBeep, SIGNAL(accepted()), this, SLOT(newBeepTypeCreated()));
}

void MainWindow::newAgentCreated(){
  Robot tempRobot = Robot(newAgent->getX(), newAgent->getY());
  robots.push_back(tempRobot);
  reDraw();
}

void MainWindow::newEnvironmentCreated(){
  EnvironmentObject tempEnvironmentObject(newEnvironment->getX(), newEnvironment->getY(),
                                          newEnvironment->getWidth(), newEnvironment->getHeight(), newEnvironment->getSource());
  environmentObjects.push_back(tempEnvironmentObject);
  reDraw();
}

void MainWindow::newBeepTypeCreated(){
  newBeep->createNewBeepType();
}

//toggle start to pause/start the simulation
void MainWindow::startSimulation(){
  if (started == false)
    started = true;
  else
    started = false;
  //implement this function to start
  mpiStart();
}

QPen MainWindow::getPenFromTemp(int temp){
  //assume temp goes from 0 to 100
  int redComponent = ((double)temp / 100) * 255;
  //to make white
  int otherComponent = 0;
  if(redComponent > 180)
     otherComponent = redComponent - 180;

  QColor myColor( redComponent, 100+otherComponent, 100+otherComponent,  255 );
  QBrush myBrush(  myColor, Qt::SolidPattern );
  QPen pen(myBrush, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  return pen;
}


//We will have a set number of points to draw temperatures for
//there will be fewer points than there are pixels on the graphics view
//Solution: have one pixel color in all surrounding pixels as well
void MainWindow::updateTemperatures(){

  //go through all the pointTemps and add their values to the locations around them
  for(int i=0;i<pointTemps.size();i++){
    for(int j = -2; j < 3; j++)
        for(int k = -2; k < 3; k++){
          int x = pointTemps[i].first.first + j;
          int y = pointTemps[i].first.second + k;
          if(x < 0) x = 0;
          if(y < 0) y = 0;
          std::pair<int, int> coordinate=std::make_pair (x,y);
          std::map<std::pair<int, int>, int > ::iterator it = mixValues.find(coordinate);

          //check to see if there is a value for the point assigned already
          if(it == mixValues.end())
          {
             mixValues[coordinate] = pointTemps[i].second;
             countValues[coordinate] = 1;
          }
          //otherwise the value already exists, do rudimentary mixing (average existing value and new value)
          else{
            mixValues[coordinate] = (mixValues[coordinate] + pointTemps[i].second);
            int temp = mixValues[coordinate];
            countValues[coordinate] += 1;
            int tempCount = countValues[coordinate];
            tempCount++;
          }
        }
  }

  //draw the colors on the map
  for(std::map<std::pair<int, int>, int > ::iterator it = mixValues.begin(); it != mixValues.end(); it++){
     int x = it->first.first;
     int y = it->first.second;
     std::pair<int, int> coordinate=std::make_pair (x,y);
     int numTimesAssigned = countValues[coordinate];
     QPen color = getPenFromTemp(it->second/numTimesAssigned);
     scene->addLine(x,y,x,y, color);
  }
}

void MainWindow::reDraw(){
  scene = new QGraphicsScene(this);
  //set background color
  QColor myColor( 50, 100, 100,  255 );
  ui->graphicsView->setBackgroundBrush(QBrush(myColor, Qt::SolidPattern));
  ui->graphicsView->setScene(scene);

  //set window to view
  scene->setSceneRect(0,0,400,400);

  //update background colors according to their temperatures
  updateTemperatures();


  //redraw robots

  // NOTE -IF WE FIX UPDATES USE robots[i].updateDrawPosition(scene)
  for(unsigned i = 0; i<robots.size(); i++){
    //robots[i].randUpdateDrawPosition(scene);
    robots[i].updateDrawPosition(scene);
   }

  //redraw environment objects
  for(unsigned i = 0; i<environmentObjects.size(); i++){
    environmentObjects[i].updateDrawPosition(scene);
  }

 }

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
  for(unsigned i=1;i<updates.size();++i){
    //std::cout << "Rank " << i << " sent: " << updates[i] << std::endl;
    if(updates[i] == "exit"){
      //run=false;
    }
    //std::cout << "In String: " << updates[i] << std::endl;
    std::stringstream data(updates[i]);
    unsigned j=0;
    while(data >> x >> y){
      //std::cout << "Setting Position: " << x << " " << y << std::endl;
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
