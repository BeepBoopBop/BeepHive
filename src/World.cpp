#include <iostream>

#include "BeepHive.h"
#include "World.h"



World::World() : model_array(), event_queue() 
{
  Model* beep_model=new BeepModel;
  model_array.push_back(beep_model);
  event_queue.push(beep_model->getNextEvent());
}



World::~World() {}



void World::step()
{
  std::cout << "Stepping World" << std::endl;
}
