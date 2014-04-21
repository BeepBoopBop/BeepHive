#ifndef BEEP_H
#define BEEP_H 

#include <iostream>

#include "BeepHive.h"
#include "World.h"
#include "Manipulator.h"
#include "Sensor.h"
#include "Controller.h"
#include "Factory.h"
#include "Stateful.h"

class World;
class Controller;
class Manipulator;
class Sensor;

/*!
 * The Beep class is a template for robots in BeepHive
 * 
 * Custom beeps can be created by setting a controller and by adding
 * Sensors and Manipulators
 */
class Beep: public Stateful{
  public:
    Beep();
    ~Beep();
    void readSensors(World* world);
    void runController();
    void runManipulators(World* world);

    void setController(Controller* controller);

    void addSensor(std::string sensor_name, Sensor* sensor);
    Sensor* getSensor(std::string sensor_name);

    void addManipulator(std::string manipulator_name, Manipulator* manipulator);
    Manipulator* getManipulator(std::string manipulator_name);

  private:
    Controller* controller;
    Map<Sensor*> sensors;
    Map<Manipulator*> manipulators;
    Map<double> states;
};



DEFINE_FACTORY(Beep, Beep);

#endif /* BEEP_H */
