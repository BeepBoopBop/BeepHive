#ifndef CONTROLLER_H
#define CONTROLLER_H 

#include "BeepHive.h"
#include "Beep.h"
#include "Sensor.h"
#include "Manipulator.h"

class Beep;

class Controller {
  public:
    virtual void run(Beep* beep) = 0;
};

#endif /* CONTROLLER_H */
