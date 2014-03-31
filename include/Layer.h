/*!
 * \class Layer
 * \brief Base layer class for use in discrete time simulator.
 */
#ifndef MODEL_H
#define MODEL_H 

#include "Event.h"

class Event;

class Layer {
  public:
    Layer();
    virtual ~Layer();

    double getTime() const;
    virtual void setTime(double new_time);
    virtual double timeSinceLastUpdate();

    virtual void update(const Event* event);
    virtual Event getNextEvent() = 0;

  protected:
    double time;
};

#endif /* MODEL_H */