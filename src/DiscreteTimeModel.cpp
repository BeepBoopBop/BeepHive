#include "DiscreteTimeModel.h"
#include "Event.h"

DiscreteTimeModel::DiscreteTimeModel() : Model(), event_frequency(1) {}



DiscreteTimeModel::DiscreteTimeModel(double event_frequency)
  : Model(), event_frequency(event_frequency) {}



DiscreteTimeModel::~DiscreteTimeModel() {}



Event DiscreteTimeModel::getNextEvent()
{ 
  return Event(this,time + event_frequency);
}



void DiscreteTimeModel::update(const Event* event)
{
  Model::update(event);
}



double DiscreteTimeModel::getEventFrequency(){
  return event_frequency;
}



void DiscreteTimeModel::setEventFrequency(double event_frequency)
{
  this->event_frequency=event_frequency;
}
