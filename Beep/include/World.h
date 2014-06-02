#ifndef WORLD_H
#define WORLD_H 

#include <queue>
#include <string>
#include <vector>

#include "BeepHive.h"
#include "Event.h"
#include "Stateful.h"

class Beep;
class EnvObject;
class Event;
class Layer;

typedef std::vector<Beep*> Beeps;
typedef std::vector<Layer*> LayerArray;
typedef std::priority_queue<Event,std::vector<Event>,EventComparator> EventQueue;
typedef std::vector<EnvObject*> ObjectArray;

/*!
 * The World is the top level class of BeepHive simulations
 *
 * The World contains Layers, Environment Objects and Beeps.
 * Updates to Layers are based on scheduling of Events in the priority queue
 */
class World : public Stateful{
  public:
    World();
    ~World();
    int step();
    int start();

    void addLayer(std::string layer_name, Layer* layer, double start_time=0);
    Layer* getLayer(std::string layer_name);

    void write();

    typedef Beeps::const_iterator BeepIterator;
    BeepIterator beepBegin() const;
    BeepIterator beepEnd() const;
    void addBeep(Beep* beep);

    typedef ObjectArray::const_iterator ObjectIterator;
    ObjectIterator objectBegin() const;
    ObjectIterator objectEnd() const;
    void addObject( EnvObject* object );

    void quit();
  private:
    Beeps beeps;
    Map<Layer*> layers;
    ObjectArray env_objects;
    EventQueue event_queue;

    bool running;
};

#endif /* WORLD_H */
