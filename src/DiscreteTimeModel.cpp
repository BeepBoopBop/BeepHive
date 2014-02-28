#include "DiscreteTimeModel.h"
#include "Event.h"

Event DiscreteTimeModel::getNextEvent()
{ 
  return Event(this,time + event_frequency);
}
