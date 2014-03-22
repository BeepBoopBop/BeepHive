#include "Model.h"

Model::Model()
{
  time = 0; 
}



Model::~Model() {}


double Model::getTime()
{ 
  return time; 
}



void Model::setTime(double new_time)
{ 
  time = new_time;
}



void Model::update(Event* event)
{
  this->setTime(event->getTime());
}
