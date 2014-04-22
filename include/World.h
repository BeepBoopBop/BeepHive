#ifndef WORLD_H
#define WORLD_H 

#include <vector>
#include <queue>
#include <string>

#include "BeepHive.h"
#include "Event.h"
#include "Layer.h"
#include "Beep.h"

class Layer;
class Event;
class Beep;

//! Used by World to compare events, does not compile if in Event files
class EventComparator
{
  public:
    bool operator()(const Event first, const Event second) const;
};

typedef std::vector<Beep*> Beeps;
typedef std::vector<Layer*> LayerArray;
typedef std::priority_queue<Event,std::vector<Event>,EventComparator> EventQueue;

/*!
 * The World is the top level class of BeepHive simulations
 *
 * The World contains Layers, Environment Objects and Beeps.
 * Updates to Layers are based on scheduling of Events in the priority queue
 */
class World {
  public:
    World();
    virtual ~World();
    int step();
    int start();

    void addLayer(std::string layer_name, Layer* layer, double start_time=0);
    Layer* getLayer(std::string layer_name);

    typedef Beeps::const_iterator BeepIterator;
    BeepIterator beepBegin() const;
    BeepIterator beepEnd() const;
    void addBeep(Beep* beep);

    void quit();
  private:
    Beeps beeps;
    Map<Layer*> layers;
    EventQueue event_queue;

    bool running;
};

#endif /* WORLD_H */
