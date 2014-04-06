#ifndef FLOCKINGCONTROLLER_H
#define FLOCKINGCONTROLLER_H 

#include "Controller.h"
#include "Beep.h"

class Controller;
class Beep;

/*!
 * This Controller is intended to implement basic flocking
 *
 * Currently, only pseudo-flocking is implemented where robots spin and take
 * the dot product of orientation to the vector to the average Beep position.
 *
 * \todo Finish flocking
 */
class FlockingController : public Controller
{
  public:
    virtual void run(Beep* beep);
};
#endif /* FLOCKINGCONTROLLER_H */
