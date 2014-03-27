#ifndef BEEP_H
#define BEEP_H 

#include <iostream>

#include "BeepHive.h"
#include "World.h"
#include "Manipulator.h"
#include "Sensor.h"


class Beep {
  public:
    void step();
    void update();
    Sensor* getSensor(std::string sensor_name);
    Manipulator* getManipulator(std::string manipulator_name);
  private:
    World* world;
    Controller* controller;
    Map<Sensor*> sensors;
    Map<Manipulator*> manipulators;
};
#endif /* BEEP_H */
