#ifndef FLOCKINGCONTROLLER_H
#define FLOCKINGCONTROLLER_H 

#include "Controller.h"
#include "Beep.h"

class Controller;
class Beep;

class FlockingController : public Controller
{
  public:
    virtual void run(Beep* beep);
};
#endif /* FLOCKINGCONTROLLER_H */
