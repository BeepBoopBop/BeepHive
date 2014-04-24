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


bool EventComparator::operator()(const Event first, const Event second) const
{
  return second < first;
}



World::World() : layers(), event_queue(), running(true)
{
  std::string temp;
  std::cout << Factories<Controller>::getInstance().begin()->first << std::endl;
  Layer* sync_layer=new SyncLayer;
  this->addLayer("SyncLayer",sync_layer);
  Layer* beep_layer=new BeepLayer;
  this->addLayer("BeepLayer",beep_layer);

  /*
  Factories<Beep>& factories=Factories<Beep>::getInstance();

  Factories<Beep>::iterator it;
  std::cout << "Factories in factories: " << std::endl;
  for(it=factories.begin(); it!=factories.end(); ++it){
    std::cout << it->first << std::endl;
  }

  CustomBeepFactory* flocking_beep=new CustomBeepFactory("FlockingBeep","Beep");

  FactoryParams x_sensor;
  x_sensor.push_back("x");
  flocking_beep->addSensor("AverageX","AverageSensor",x_sensor);
  FactoryParams y_sensor;
  y_sensor.push_back("y");
  flocking_beep->addSensor("AverageY","AverageSensor",y_sensor);

  flocking_beep->setController("FlockingController");
  flocking_beep->addManipulator("OmegaVelocityManipulator","OmegaVelocityManipulator");

  CustomBeepFactory* simple_beep=new CustomBeepFactory("BasicBeep","Beep");
  simple_beep->addSensor("AverageX","AverageSensor",x_sensor);
  simple_beep->addSensor("AverageY","AverageSensor",y_sensor);
  simple_beep->addManipulator("OmegaVelocityManipulator","OmegaVelocityManipulator");
  simple_beep->setController("BasicController");

  std::cout << "Factories in factories: " << std::endl;
  for(it=factories.begin(); it!=factories.end(); ++it){
    std::cout << it->first << std::endl;
  }

  Beep* beep;
  for(int i=0;i<20;++i){
    for(int j=0;j<20;++j){
      if((i+j)%2){
        beep=factories["FlockingBeep"]->create();
      } else {
        beep=factories["BasicBeep"]->create();
      }

      beep->setState("x",20*i);
      beep->setState("y",20*j);

      beeps.push_back(beep);
    }
  }
  */
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
