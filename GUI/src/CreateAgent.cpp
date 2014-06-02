#include "CreateAgent.h"
#include "ui_createagent.h"

CreateAgent::CreateAgent(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::CreateAgent)
{
  ui->setupUi(this);
  QStringList beeps;


  Factories<Beep>& beep_factories = Factories<Beep>::getInstance();

  Factories<Beep>::iterator it;
  for(it=beep_factories.begin(); it!=beep_factories.end(); ++it){
    beeps << QString::fromStdString(it->first);
  }
  ui->comboBox->addItems(beeps);
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

std::string CreateAgent::getBeepType(){
    return ui->comboBox->currentText().toUtf8().constData();
}
