#ifndef EVENT_H
#define EVENT_H 

#include "Model.h"

class Model;

/*!
 * Event class for use in discrete time simulator.
 */
class Event {
  public:
    Event(Model* model, double time);

    bool operator<(Event& event);

    void updateModel();

  private:
    double time;
    Model* model;
};

#endif /* EVENT_H */
