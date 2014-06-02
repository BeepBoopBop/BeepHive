#include "CreateEnvironment.h"
#include "ui_createenvironment.h"

CreateEnvironment::CreateEnvironment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateEnvironment)
{
  ui->setupUi(this);
}

CreateEnvironment::~CreateEnvironment()
{
  delete ui;
}

int CreateEnvironment::getX(){
  return ui->lineEdit->text().toInt();
}

int CreateEnvironment::getY(){
  return ui->lineEdit_2->text().toInt();
}

int CreateEnvironment::getWidth(){
  return ui->lineEdit_3->text().toInt();
}

int CreateEnvironment::getHeight(){
  return ui->lineEdit_4->text().toInt();
}

bool CreateEnvironment::getSource(){
  return ui->checkBox->isChecked();
}
