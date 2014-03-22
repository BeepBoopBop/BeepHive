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
    model->update();
  }
}



bool EventComparator::operator()(const Event* first, const Event* second) const
{
  return *first < *second;
}
