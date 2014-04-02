#ifndef WORLD_H
#define WORLD_H 

#include <vector>
#include <queue>

#include "BeepHive.h"
#include "Event.h"
#include "Layer.h"

class Layer;
class Event;

class EventComparator
{
  public:
    bool operator()(const Event first, const Event second) const;
};

typedef std::vector<Layer*> LayerArray;
typedef std::priority_queue<Event,std::vector<Event>,EventComparator> EventQueue;
//typedef std::priority_queue<Event,std::vector<Event> > EventQueue;

class World {
  public:
    World();
    virtual ~World();
    int step();
    int start();

    void addLayer(std::string layer_name, Layer* layer, double start_time=0);
    Layer* getLayer(std::string layer_name);
  private:
    Map<Layer*> layers;
    EventQueue event_queue;
};

#endif /* WORLD_H */
