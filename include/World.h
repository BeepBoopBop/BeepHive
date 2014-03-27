#ifndef WORLD_H
#define WORLD_H 

#include <vector>
#include <queue>

#include "BeepHive.h"
#include "Event.h"
#include "Model.h"
#include "BeepModel.h"


typedef std::vector<Model*> ModelArray;
typedef std::priority_queue<Event> EventQueue;

class World {
  public:
    World();
    virtual ~World();
    void step();

    void addModel(Model *,std::string model_name);
    Model* getModel(std::string model_name);
  private:
    Map<Model*> models;
    EventQueue event_queue;
};

#endif /* WORLD_H */
