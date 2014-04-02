#ifndef EVENT_H
#define EVENT_H 

#include "BeepHive.h"
#include "Layer.h"
#include "World.h"

class Layer;
class World;

/*!
 * Event class for use in discrete time simulator.
 */
class Event {
  public:
    Event(Layer* layer, double time);

    bool operator<(const Event& event) const;

    void updateLayer(World* world);
    Event getNextEvent();

    void setTime(double time);
    double getTime() const;

  private:
    double time;
    Layer* layer;
};

#endif /* EVENT_H */
