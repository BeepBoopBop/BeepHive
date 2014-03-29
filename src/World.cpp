#include <iostream>

#include "BeepHive.h"
#include "BeepModel.h"
#include "SyncModel.h"
#include "World.h"



World::World() : models(), event_queue() 
{
  Model* sync_model=new SyncModel;
  this->addModel("sync",sync_model);
  Model* beep_model=new BeepModel;
  this->addModel("beep",beep_model);
}



World::~World() {}


int World::step()
{
  //DEBUG("Stepping World");
  Event event=event_queue.top();

  event_queue.pop();
  event.updateModel();
  event_queue.push(event.getNextEvent());

  //temporarilly have automatic exit
  if(event.getTime() > 9){
    return 1;
  }
  
  return 0;
}



int World::start()
{
  int ret=0;
  while(ret==0){
    ret=step();
  }
  DEBUG("Exiting start loop");
  return ret;
}



void World::addModel(std::string model_name, Model* model, double start_time){
  models[model_name]=model;
  event_queue.push(Event(model,start_time));
}
