#define MAINWINDOW_
#ifndef MAINWINDOW_H

#include "gui_includes.h"
#include "robot.h"
#include "environmentobject.h"
#include "debugwindow.h"
#include "createagent.h"
#include "createenvironment.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void moveAgents();
  void mousePressEvent(QMouseEvent *event);
  void reDraw();



public slots:
  void timeToStep();

  void createNewAgentWindow();
  void createNewEnvironmentWindow();

  void newAgentCreated();
  void newEnvironmentCreated();

  void startSimulation();

private:
  bool started; //set true to start simulation

  //*********************************************************************************
  /**************************************
   *  BACKEND/MPI FUNCTIONS TO IMPLEMENT*
   **************************************/
  //*********************************************************************************

  //implement this function to start the backend
  void mpiStart();

  //use this function to block redrawing until an update is received
  void mpiWaitForUpdates();

  //use this function to load the updates into the robots and environmentObjects vectors
  void mpiLoadUpdates();



  Ui::MainWindow *ui;
  QGraphicsScene *scene;
  std::vector<Robot> robots;
  std::vector<EnvironmentObject> environmentObjects;
  QTimer *timer;

  //windows that the mainwindow owns
  DebugWindow* newDebug;
  CreateAgent* newAgent;
  CreateEnvironment* newEnvironment;
};

#endif // MAINWINDOW_H
