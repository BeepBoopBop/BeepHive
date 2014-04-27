#include "DiscreteTimeLayer.h"
#include "Event.h"

DiscreteTimeLayer::DiscreteTimeLayer() : Layer(), event_frequency(1) {}



DiscreteTimeLayer::DiscreteTimeLayer(double event_frequency)
  : Layer(), event_frequency(event_frequency) {}



DiscreteTimeLayer::~DiscreteTimeLayer() {}



double DiscreteTimeLayer::timeSinceLastUpdate()
{
  return this->event_frequency;
}



Event DiscreteTimeLayer::getNextEvent()
{ 
  return Event(this,time + event_frequency);
}



void DiscreteTimeLayer::update(const Event* event, World* world)
{
  Layer::update(event, world);
}



double DiscreteTimeLayer::getEventFrequency(){
  return event_frequency;
}



void DiscreteTimeLayer::setEventFrequency(double event_frequency)
{
  this->event_frequency=event_frequency;
}
