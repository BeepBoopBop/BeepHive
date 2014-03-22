#ifndef WORLD_H_H
#define WORLD_H_H 

#include <vector>
#include <queue>

#include "BeepHive.h"
#include "Event.h"
#include "Model.h"


typedef std::vector<Model*> ModelArray;
typedef std::priority_queue<Event*,std::vector<Event*>,EventComparator> EventQueue;

class World {
  public:
    World();
    ~World();
    void step();
  private:
    ModelArray model_array;
    EventQueue event_queue;
};

#endif /* WORLD_H_H */
