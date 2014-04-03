#include <iostream>

#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "BeepLayer.h"
#include "SyncLayer.h"
#include "World.h"


bool EventComparator::operator()(const Event first, const Event second) const
{
  return second < first;
}



World::World() : layers(), event_queue(), running(true)
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
  Layer* layer=event.getLayer();
  layer->update(&event,this);
  event_queue.push(layer->getNextEvent());

  
  return this->running==false;
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



Layer* World::getLayer(std::string layer_name)
{
  return layers[layer_name];
}



//! quit allows layers to signal to the world that an end condition has been
//  reached
void World::quit()
{
  running=false;
}
