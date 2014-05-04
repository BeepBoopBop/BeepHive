#include "BeepHive.h"
#include "BeepLayer.h"
#include "Beep.h"

BeepLayer::BeepLayer() : DiscreteTimeLayer() {}



BeepLayer::BeepLayer(double event_frequency) : DiscreteTimeLayer(event_frequency) {}



BeepLayer::~BeepLayer() {}



void BeepLayer::update(const Event* event, World* world)
{
  DiscreteTimeLayer::update(event, world);
  DEBUG_OUT("Updating BeepLayer");
  World::BeepIterator it;
  for(it=world->beepBegin(); it!=world->beepEnd(); ++it){
    (*it)->readSensors(world);
  }
  for(it=world->beepBegin(); it!=world->beepEnd(); ++it){
    (*it)->runController();
  }
  for(it=world->beepBegin(); it!=world->beepEnd(); ++it){
    (*it)->runManipulators(world);
  }
}
