#include "Model.h"

Model::Model()
{
  time = 0; 
}



Model::~Model() {}


double Model::getTime() const
{
  return time; 
}



void Model::setTime(double new_time)
{ 
  time = new_time;
}

//! this is just here to make the compiler happy
double Model::timeSinceLastUpdate()
{
  return -1;
}



void Model::update(const Event* event)
{
  this->setTime(event->getTime());
  std::cout << "Model updating! Time is now: " << event->getTime() << std::endl;
}
