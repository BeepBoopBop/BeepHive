#include "createagent.h"
#include "ui_createagent.h"

CreateAgent::CreateAgent(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::CreateAgent)
{
  ui->setupUi(this);
}

CreateAgent::~CreateAgent()
{
  delete ui;
}

int CreateAgent::getX(){
  return ui->lineEdit->text().toInt();
}

int CreateAgent::getY(){
  return ui->lineEdit_2->text().toInt();
}
