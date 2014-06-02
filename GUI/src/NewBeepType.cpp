#include "NewBeepType.h"

//Creates and executes a command based on parameters
static void runCommand(std::string command_type,
                FactoryParams params)
{
  Command* command;
  Factory<Command>* command_factory;

  command_factory = Factories<Command>::getInstance()[command_type];
  command = command_factory->create(params);
  command->run();
  Communicators::getInstance().addToOutput(command->save());

  delete command;

  return;
}

NewBeepType::NewBeepType(QWidget *parent) :
    QDialog(parent)
{
  ui.setupUi(this);
  QStringList sensors;
  QStringList controllers;
  QStringList manipulators;


  Factories<Command>& command_factories = Factories<Command>::getInstance();
  Factories<Command>::iterator it4;

  for(it4=command_factories.begin(); it4!=command_factories.end(); ++it4){
    qDebug() << QString::fromStdString("  ") << QString::fromStdString(it4->first);
  }

  //BeepHiveConfigs& configs=BeepHiveConfigs::getInstance();
  //configs.initialize(argc,argv);
  //configs.setTimeLimit(2);
  Factories<Sensor>& sensor_factories = Factories<Sensor>::getInstance();

  Factories<Sensor>::iterator it;
  for(it=sensor_factories.begin(); it!=sensor_factories.end(); ++it){
    sensors << QString::fromStdString(it->first);
  }
  ui.comboBox->addItems(sensors);

  Factories<Controller>& controller_factories = Factories<Controller>::getInstance();

  Factories<Controller>::iterator it2;
  for(it2=controller_factories.begin(); it2!=controller_factories.end(); ++it2){
    controllers << QString::fromStdString(it2->first);
  }
  ui.comboBox_2->addItems(controllers);


  Factories<Manipulator>& manipulator_factories = Factories<Manipulator>::getInstance();

  Factories<Manipulator>::iterator it3;
  for(it3=manipulator_factories.begin(); it3!=manipulator_factories.end(); ++it3){
    manipulators << QString::fromStdString(it3->first);
  }
  ui.comboBox_3->addItems(manipulators);

}

//Create the new beepType based off of input in the form
//this function is called by the mainwindow
void NewBeepType::createNewBeepType(){
  std::string beepName = ui.lineEdit->text().toUtf8().constData();
  FactoryParams params = {beepName, "Beep"};
  runCommand("CustomBeepCommand",params);

  std::string sensorName = ui.comboBox->currentText().toUtf8().constData();
  if(sensorName.length() > 0) params = {"Sensor","AverageX",sensorName,beepName,"x"};
  runCommand("CustomBeepFeatureCommand",params);

  std::string controllerName = ui.comboBox_2->currentText().toUtf8().constData();
  if(controllerName.length() > 0) params = {"Controller",controllerName,controllerName,beepName};
  runCommand("CustomBeepFeatureCommand",params);

  std::string manipulatorName = ui.comboBox_3->currentText().toUtf8().constData();
  params = {"Manipulator",manipulatorName,manipulatorName,beepName};
  runCommand("CustomBeepFeatureCommand",params);

  /*params = {"RectanglePattern", "2 2 10", "BeepCommand", beepName};
    runCommand("CreateWithPatternCommand",params,&world);*/
}
