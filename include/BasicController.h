#ifndef BASICCONTROLLER_H
#define BASICCONTROLLER_H 

#include "Controller.h"
#include "Beep.h"

class Controller;
class Beep;

class BasicController : public Controller
{
  public:
    virtual void run(Beep* beep);
};
#endif /* BASICCONTROLLER_H */
