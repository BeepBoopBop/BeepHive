#include <iostream>

#include "BeepHive.h"
#include "BeepLayer.h"
#include "SyncLayer.h"
#include "World.h"


bool EventComparator::operator()(const Event first, const Event second) const
{
  return second < first;
}



World::World() : layers(), event_queue() 
{
  Layer* sync_layer=new SyncLayer;
  this->addLayer("sync",sync_layer);
  Layer* beep_layer=new BeepLayer;
  this->addLayer("beep",beep_layer);
  //Beep* beep=new Beep(
}



World::~World() {}


int World::step()
{
  //DEBUG("Stepping World");
  Event event=event_queue.top();

  event_queue.pop();
  event.updateLayer(this);
  event_queue.push(event.getNextEvent());

  //temporarilly have automatic exit
  //if(event.getTime() > 9){
    //return 1;
  //}
  
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



void World::addLayer(std::string layer_name, Layer* layer, double start_time){
  layers[layer_name]=layer;
  event_queue.push(Event(layer,start_time));
}
