#ifndef WORLD_H
#define WORLD_H 

#include <vector>
#include <queue>

#include "BeepHive.h"
#include "Event.h"
#include "Layer.h"
#include "BeepLayer.h"


typedef std::vector<Layer*> LayerArray;
typedef std::priority_queue<Event,std::vector<Event>,EventComparator> EventQueue;

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
