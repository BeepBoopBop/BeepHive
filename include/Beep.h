#ifndef BEEP_H
#define BEEP_H 

#include <iostream>

#include "BeepHive.h"
#include "World.h"
#include "Manipulator.h"
#include "Sensor.h"
#include "Controller.h"

class Manipulator;

class Beep {
  public:
    Beep();
    ~Beep();
    void step();
    void update();

    void addSensor(std::string sensor_name, Sensor* sensor);
    Sensor* getSensor(std::string sensor_name);

    void addManipulator(std::string manipulator_name, Manipulator* manipulator);
    Manipulator* getManipulator(std::string manipulator_name);

    //! Adds a new state variable to the state map, creating if necessary
    void setState(std::string state_name, double initial_state=0);
    //! Get the value of an existing state variable.
    double getState(std::string state_name);
  private:
    World* world;
    Controller* controller;
    Map<Sensor*> sensors;
    Map<Manipulator*> manipulators;
    Map<double> states;
};
#endif /* BEEP_H */
