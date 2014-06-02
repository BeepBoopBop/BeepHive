#include <boost/mpi.hpp>
#include <boost/serialization/base_object.hpp>
#include <string>

#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "Communicator.h"
#include "Event.h"
#include "Factory.h"
#include "SyncLayer.h"
#include "World.h"

SyncLayer::SyncLayer() : DiscreteTimeLayer(1) {}

SyncLayer::SyncLayer(double event_frequency) : DiscreteTimeLayer(event_frequency) {}

void SyncLayer::update(const Event* event, World* world)
{
  DEBUG_OUT("Updating SyncLayer");
  DiscreteTimeLayer::update(event, world);
  Communicators& communicators = Communicators::getInstance();
  Factories<Command>& command_factory = Factories<Command>::getInstance();

  //!Exit based on configuration
  double time_limit=BeepHiveConfigs::getInstance().getTimeLimit();
  if(time_limit>0 && event->getTime() >= time_limit){
    std::cout << "The time is " << event->getTime() << 
      " which is greater than the limit: " << time_limit << std::endl;
    communicators.addToOutput("{\"type\":\"Exit\"}");
    world->quit();
  }

  world->write();
  communicators.run();

  while(!communicators.isEmpty()){
    SerialObject object = communicators.popObject();
    Command* command = command_factory[object.type]->create();
    //std::cout << "JSON: " << object.JSON << std::endl;
    command->load(object.JSON);
    command->run(world);
    delete command;
  }
}
