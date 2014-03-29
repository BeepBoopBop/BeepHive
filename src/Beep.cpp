#include "BeepHive.h"
#include "Beep.h"



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
  return states[state_name];
}
