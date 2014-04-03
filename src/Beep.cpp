#include "BeepHive.h"
#include "Beep.h"

Beep::Beep() : controller(0), sensors(), manipulators(), states() {}



void Beep::readSensors(World* world)
{
  Map<Sensor*>::iterator it;
  for(it=sensors.begin(); it!=sensors.end(); ++it){
    //(*(it.second))->
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



void Beep::setState(std::string state_name, double initial_state)
{
  states[state_name]=initial_state;
}



double Beep::getState(std::string state_name)
{
  //states default to zero for now
  if(states.find(state_name) == states.end())
    states[state_name]=0;
  return states[state_name];
}
