#ifndef CONTROLLER_H
#define CONTROLLER_H 

#include "BeepHive.h"
#include "Beep.h"
#include "Sensor.h"
#include "Manipulator.h"

class Beep;

/*!
 * The controller class implements the control logic for a Beep
 *
 * The controller accesses and sets state variables of the Beep, reads 
 * sensor values, and sets inputs to the controllers. The order in which
 * Controllers run should never matter because Sensor readings will have already
 * been taken.
 */
class Controller {
  public:
    virtual void run(Beep* beep) = 0;
};

#endif /* CONTROLLER_H */
