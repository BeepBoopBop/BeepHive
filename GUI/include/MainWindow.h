#define MAINWINDOW_
#ifndef MAINWINDOW_H

#include "CreateAgent.h"
#include "CreateEnvironment.h"
#include "DebugWindow.h"
#include "EnvironmentObject.h"
#include "GuiIncludes.h"
#include "NewBeepType.h"
#include "Robot.h"

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
    void createNewBeepTypeWindow();

    void newAgentCreated();
    void newEnvironmentCreated();
    void newBeepTypeCreated();

    void startSimulation();
    void pauseSimulation();
    void unPauseSimulation();

    QPen getPenFromTemp(int temp);
    void updateTemperatures();

  private:
    bool started; //set true to start simulation

    //*********************************************************************************
    /**************************************
     *       BACKEND/MPI FUNCTIONS        *
     **************************************/
    //*********************************************************************************

    //implement this function to start the backend
    void mpiStart();

    //use this function to block redrawing until an update is received
    void mpiWaitForUpdates();

    //use this function to load the updates into the robots and environmentObjects vectors
    void mpiLoadUpdates();


    //std::vector <QPointF> tempBackground;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    std::vector<Robot> robots;
    std::vector<EnvironmentObject> environmentObjects;
    QTimer *timer;

    //used to store the temperatures at specific points
    std::vector<std::pair<std::pair<int, int>, int> > pointTemps;
    //uses pointTemps to generate the mix values for the map
    std::map<std::pair<int, int>, int > mixValues;
    //number of times a point has had values written to it
    std::map<std::pair<int, int>, int > countValues;

    //GUI must be started before it can be paused
    bool paused;

    //windows that the mainwindow owns
    DebugWindow* newDebug;
    CreateAgent* newAgent;
    NewBeepType* newBeep;
    CreateEnvironment* newEnvironment;
};

#endif // MAINWINDOW_H
