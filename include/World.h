#ifndef WORLD_H
#define WORLD_H 

#include <vector>
#include <queue>

#include "BeepHive.h"
#include "Event.h"
#include "Model.h"
#include "BeepModel.h"


typedef std::vector<Model*> ModelArray;
typedef std::priority_queue<Event,std::vector<Event>,EventComparator> EventQueue;

class World {
  public:
    World();
    virtual ~World();
    int step();
    int start();

    void addModel(Model* model,std::string model_name, double start_time=0);
    Model* getModel(std::string model_name);
  private:
    Map<Model*> models;
    EventQueue event_queue;
};

#endif /* WORLD_H */
