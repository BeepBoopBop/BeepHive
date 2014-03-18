/*!
 * \class Model
 * \brief Base model class for use in discrete time simulator.
 */
#ifndef MODEL_H
#define MODEL_H 

#include "Event.h"

class Event;

class Model {
  public:
    Model();

    double getTime();
    void setTime(double new_time);

    virtual void update() = 0;
    virtual Event getNextEvent() = 0;

  protected:
    double time;
};

#endif /* MODEL_H */
