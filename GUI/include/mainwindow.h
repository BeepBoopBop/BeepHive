#define MAINWINDOW_
#ifndef MAINWINDOW_H

#include "gui_includes.h"
#include "robot.h"
#include "debugwindow.h"



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


public slots:
  void timeToStep();

private:
  Ui::MainWindow *ui;
  QGraphicsScene *scene;
  std::vector<Robot> robots;
  QTimer *timer;
  DebugWindow* newDebug;
};

#endif // MAINWINDOW_H
