#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QWidget>

#include "GuiIncludes.h"
#include "Robot.h"

namespace Ui {
  class DebugWindow;
}

class DebugWindow : public QWidget
{
  Q_OBJECT

  public:
    explicit DebugWindow(QWidget *parent = 0);
    ~DebugWindow();
    void setRobotToMonitor(Robot* robotToMonitor);
    void updateOutput(); //called by MainWindow to update output

    public slots:
      void updateText();

  private:
    Robot* monitoredRobot;
    Ui::DebugWindow *ui;
};

#endif // DEBUGWINDOW_H
