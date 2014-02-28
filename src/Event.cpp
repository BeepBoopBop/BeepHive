#include "Event.h"
#include "Model.h"


Event::Event(Model* model, double time)
  : model(model), time(time) {}



bool Event::operator<(Event& event)
{
  return this->time < event.time;
}



void Event::updateModel()
{
  if(model!=0){
    model->updateModel();
  }
}
