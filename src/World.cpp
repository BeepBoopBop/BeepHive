#include <iostream>

#include "BeepHive.h"
#include "BeepLayer.h"
#include "SyncLayer.h"
#include "World.h"



World::World() : models(), event_queue() 
{
  Layer* sync_model=new SyncLayer;
  this->addLayer("sync",sync_model);
  Layer* beep_model=new BeepLayer;
  this->addLayer("beep",beep_model);
}



World::~World() {}


int World::step()
{
  //DEBUG("Stepping World");
  Event event=event_queue.top();

  event_queue.pop();
  event.updateLayer();
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



void World::addLayer(std::string model_name, Layer* model, double start_time){
  models[model_name]=model;
  event_queue.push(Event(model,start_time));
}
