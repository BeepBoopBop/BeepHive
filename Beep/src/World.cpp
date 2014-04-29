#include <iostream>
#include <string>
#include <sstream>

#include "AverageSensor.h"
#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "BeepLayer.h"
#include "SyncLayer.h"
#include "World.h"
#include "BasicController.h"
#include "FlockingController.h"
#include "Factory.h"
#include "OmegaVelocityManipulator.h"
#include "CustomBeepFactory.h"
#include "Communicator.h"


bool EventComparator::operator()(const Event first, const Event second) const
{
  return second < first;
}



World::World() : layers(), event_queue(), running(true)
{
  std::string temp;
  //std::cout << Factories<Controller>::getInstance().begin()->first << std::endl;
  Layer* sync_layer=new SyncLayer(0.2);
  this->addLayer("SyncLayer",sync_layer);
  Layer* beep_layer=new BeepLayer(0.2);
  this->addLayer("BeepLayer",beep_layer);
}



World::~World() {}



int World::step()
{
  DEBUG("Stepping World");
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
  std::cout << "Adding: " << layer_name << std::endl;
  layers[layer_name]=layer;
  event_queue.push(Event(layer,start_time));
}



Layer* World::getLayer(std::string layer_name)
{
  return layers[layer_name];
}



void World::write()
{
  Map<Layer*>::iterator it;
  for(it=layers.begin(); it!=layers.end(); ++it){
    it->second->write();
  }
  for(BeepIterator it=this->beepBegin(); it!=this->beepEnd(); ++it){
    Communicators::getInstance().addToOutput((*it)->save());
  }
  Communicators::getInstance().addToOutput("{\"type\":\"Exit\"}");
}



World::BeepIterator World::beepBegin() const
{
  return beeps.begin();
}



World::BeepIterator World::beepEnd() const
{
  return beeps.end();
}

void World::addBeep(Beep* beep)
{
  std::stringstream name;
  name << beeps.size();
  addChild(name.str(), beep);
  beep->setState("id",beeps.size());
  beeps.push_back(beep);
}

World::ObjectIterator World::objectBegin() const
{
  return env_objects.begin();
}

World::ObjectIterator World::objectEnd() const
{
  return env_objects.end();
}

void World::addObject(EnvObject* object)
{
  env_objects.push_back(object);
}

//! quit allows layers to signal to the world that an end condition has been
//  reached
void World::quit()
{
  running=false;
}
