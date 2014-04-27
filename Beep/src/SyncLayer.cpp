#include <string>
#include <boost/serialization/base_object.hpp>
#include <boost/mpi.hpp>

#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "SyncLayer.h"
#include "Communicator.h"
#include "Factory.h"

SyncLayer::SyncLayer() : DiscreteTimeLayer(1) {}

SyncLayer::SyncLayer(double event_frequency) : DiscreteTimeLayer(event_frequency) {}

void SyncLayer::update(const Event* event, World* world)
{
  DEBUG("Updating SyncLayer");
  DiscreteTimeLayer::update(event, world);
  Communicators& communicators = Communicators::getInstance();
  Factories<Command>& command_factory = Factories<Command>::getInstance();

  //!Exit based on configuration
  double time_limit=BeepHiveConfigs::getInstance().getTimeLimit();
  if(time_limit>0 && event->getTime() > time_limit){
    communicators.setOutput("exit");
    world->quit();
  }

  communicators.run();
  std::string input = communicators.getInput();
  //do json stuff to get factories
  FactoryParams params;
  //params.push_back("Beep");
  //Factories<Command>::iterator it = command_factory.begin();
  //assert(it != command_factory.end());
  //std::cout << "The first command type is named: " <<  it->second->type() << std::endl;
  //Command* command = command_factory["BeepCommand"]->create(params);
  //command->run(world);
  //delete command;
}
