#include "BeepHive.h"
#include "BeepLayer.h"
#include "Beep.h"

BeepLayer::BeepLayer() : DiscreteTimeLayer() {}



BeepLayer::BeepLayer(double event_frequency) : DiscreteTimeLayer(event_frequency) {}



BeepLayer::~BeepLayer() {}



void BeepLayer::update(const Event* event, World* world)
{
  DiscreteTimeLayer::update(event, world);
  DEBUG("Updating BeepLayer");
  Beeps::iterator it;
  for(it=beeps.begin(); it!=beeps.end(); ++it){
    (*it)->readSensors(world);
  }
  for(it=beeps.begin(); it!=beeps.end(); ++it){
    (*it)->runController();
  }
  for(it=beeps.begin(); it!=beeps.end(); ++it){
    (*it)->runManipulators(world);
  }
}
