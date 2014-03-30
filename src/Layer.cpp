#include "Layer.h"

Layer::Layer()
{
  time = 0; 
}



Layer::~Layer() {}


double Layer::getTime() const
{
  return time; 
}



void Layer::setTime(double new_time)
{ 
  time = new_time;
}

//! this is just here to make the compiler happy
double Layer::timeSinceLastUpdate()
{
  return -1;
}



void Layer::update(const Event* event)
{
  this->setTime(event->getTime());
  std::cout << "Layer updating! Time is now: " << event->getTime() << std::endl;
}
