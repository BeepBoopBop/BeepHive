#ifndef CONTROLLER_H
#define CONTROLLER_H 

#include "BeepHive.h"
#include "Beep.h"
#include "Sensor.h"
#include "Manipulator.h"

class Beep;

class Controller {
  public:
    virtual void run();
    virtual void update();
  private:
    Beep* beep;
};

#endif /* CONTROLLER_H */
