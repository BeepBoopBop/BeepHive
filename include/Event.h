#ifndef EVENT_H
#define EVENT_H 

#include "BeepHive.h"
#include "Layer.h"

class Layer;

/*!
 * Event class for use in discrete time simulator.
 */
class Event {
  public:
    Event(Layer* layer, double time);

    bool operator<(const Event& event) const;

    void updateLayer();
    Event getNextEvent();

    void setTime(double time);
    double getTime() const;

  private:
    double time;
    Layer* layer;
};

class EventComparator
{
  public:
    bool operator()(const Event first, const Event second) const;
};

#endif /* EVENT_H */
