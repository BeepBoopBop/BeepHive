#include <sstream>

#include "Communicator.h"
#include "BeepHive.h"
#include "Beep.h"

Beep::Beep() : controller(0), sensors(), manipulators(), states() {}



void Beep::readSensors(World* world)
{
  Map<Sensor*>::iterator it;
  for(it=sensors.begin(); it!=sensors.end(); ++it){
    it->second->readLayer(world);
  }
}



void Beep::runController()
{
  DEBUG("Running Controller");
  if(this->controller){
    controller->run(this);
  }
}

void Beep::runManipulators(World* world)
{
  Map<Manipulator*>::iterator it;
  for(it=manipulators.begin(); it!=manipulators.end(); ++it){
    it->second->updateState(this,world);
  }
  std::stringstream message;
  message << getState("x") << " " << getState("y");
  Communicators::getInstance().addToOutput(message.str());
}



void Beep::setController(Controller* controller)
{
  this->controller=controller;
}



void Beep::addSensor(std::string sensor_name, Sensor* sensor)
{
  sensors[sensor_name]=sensor;
}



Sensor* Beep::getSensor(std::string sensor_name)
{
  return sensors[sensor_name];
}



void Beep::addManipulator(std::string manipulator_name, Manipulator* manipulator)
{
  manipulators[manipulator_name] = manipulator;
}



Manipulator* Beep::getManipulator(std::string manipulator_name)
{
  return manipulators[manipulator_name];
}


Beep* BeepFactory::create()
{
  return new Beep();
}



Beep* BeepFactory::create(FactoryParams& params)
{
  return this->create();
}



ADD_TO_FACTORIES(Beep,Beep);
