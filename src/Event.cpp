#include "BeepHive.h"
#include "Event.h"
#include "Model.h"


Event::Event(Model* model, double time)
  : time(time), model(model) {}



bool Event::operator<(const Event& event) const
{
  return this->time < event.time;
}



void Event::updateModel()
{
  if(model!=0){
    model->update(this);
  }
}



Event Event::getNextEvent()
{
  return model->getNextEvent();
}



bool EventComparator::operator()(const Event first, const Event second) const
{
  return second < first;
}



void Event::setTime(double time)
{
  this->time=time;
}



double Event::getTime() const
{
  return time;
}
