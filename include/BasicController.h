#ifndef BASICCONTROLLER_H
#define BASICCONTROLLER_H 

#include "Controller.h"
#include "Beep.h"

class Controller;
class Beep;

/*!
 * This is a simple controller used for testing purposes
 *
 * This controller sends constant inputs to an OmegaVelocity Manipulator
 * such that the Beep eternally drives in circles
 */
class BasicController : public Controller
{
  public:
    virtual void run(Beep* beep);
};


DEFINE_FACTORY(BasicController, Controller);

#endif /* BASICCONTROLLER_H */
