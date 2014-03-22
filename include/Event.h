#ifndef EVENT_H
#define EVENT_H 

#include "BeepHive.h"
#include "Model.h"

class Model;

/*!
 * Event class for use in discrete time simulator.
 */
class Event {
  public:
    Event(Model* model, double time);

    bool operator<(const Event& event) const;

    void updateModel();

  private:
    double time;
    Model* model;
};

class EventComparator
{
  public:
    bool operator()(const Event* first, const Event* second) const;
};

#endif /* EVENT_H */
