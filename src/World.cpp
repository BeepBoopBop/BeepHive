#include <iostream>

#include "BeepHive.h"
#include "World.h"



World::World() : models(), event_queue() 
{
  Model* beep_model=new BeepModel;
  models["beep"]=beep_model;
  event_queue.push(beep_model->getNextEvent());
}



World::~World() {}



void World::step()
{
  std::cout << "Stepping World" << std::endl;
}
