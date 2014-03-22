#include <iostream>

#include "BeepHive.h"
#include "World.h"



World::World() : model_array(), event_queue() {}



World::~World() {}



void World::step()
{
  std::cout << "Stepping World" << std::endl;
}
