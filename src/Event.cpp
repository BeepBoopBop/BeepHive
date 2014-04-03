//#include "BeepHive.h"
#include "Event.h"
#include "Layer.h"


Event::Event(Layer* layer, double time)
  : time(time), layer(layer) {}



bool Event::operator<(const Event& event) const
{
  return this->time < event.time;
}



Layer* Event::getLayer()
{
  return layer;
}

void Event::setTime(double time)
{
  this->time=time;
}



double Event::getTime() const
{
  return time;
}

