#include <iostream>

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

  for(int i=0;i<20;++i){
    for(int j=0;j<20;++j){
      Beep* beep=new Beep();


      Controller* controller;
      if((i+j)%2){
        controller=new FlockingController();
      } else {
        controller=new BasicController();
      }
      assert(controller!=NULL);
      beep->setController(controller);

      Manipulator* omega_vel=new OmegaVelocityManipulator();
      beep->addManipulator("OmegaVelocity",omega_vel);

      Sensor* sensor=new AverageSensor(beep_layer,"x");
      beep->addSensor("AverageX",sensor);
      sensor=new AverageSensor(beep_layer,"y");
      beep->addSensor("AverageY",sensor);

      beep->setState("x",20*i);
      beep->setState("y",20*j);

      beeps.push_back(beep);
    }
  }
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
  beeps.push_back(beep);
}



void World::addMessageToGui(std::string message)
{
  messages_to_gui+=message+" ";
}



const std::string& World::getMessagesToGui()
{
  return messages_to_gui;
}



void World::clearMessagesToGui()
{
  messages_to_gui="";
}



const std::string& World::getMessagesFromGui()
{
  return messages_from_gui;
}



void World::setMessagesFromGui(std::string messages)
{
  messages_from_gui=messages;
}

//! quit allows layers to signal to the world that an end condition has been
//  reached
void World::quit()
{
  running=false;
}
