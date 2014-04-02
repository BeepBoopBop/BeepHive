#include "debugwindow.h"
#include "ui_debugwindow.h"

DebugWindow::DebugWindow(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::DebugWindow)
{
  ui->setupUi(this);
  monitoredRobot = NULL;
  ui->textEdit->setText("test");

}

DebugWindow::~DebugWindow()
{
  delete ui;
}

 void DebugWindow::setRobotToMonitor(Robot *robotToMonitor){
   this->monitoredRobot = robotToMonitor;
 }


 void DebugWindow::updateOutput(){

 }

 void DebugWindow::updateText(){
    std::string temp = monitoredRobot->obtainUpdateString();
    qDebug() << QString::fromStdString( temp );
    ui->textEdit->setText(QString::fromStdString( temp ));
 }
