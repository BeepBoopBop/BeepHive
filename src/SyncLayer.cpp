#include <string>
#include <boost/serialization/base_object.hpp>
#include <boost/mpi.hpp>

#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "SyncLayer.h"
#include "Communicator.h"

SyncLayer::SyncLayer() : DiscreteTimeLayer(1) {}

SyncLayer::SyncLayer(double event_frequency) : DiscreteTimeLayer(event_frequency) {}

void SyncLayer::update(const Event* event, World* world)
{
  DEBUG("Updating SyncLayer");
  DiscreteTimeLayer::update(event, world);

  //!Exit based on configuration
  double time_limit=BeepHiveConfigs::getInstance().getTimeLimit();
  if(time_limit>0 && event->getTime() > time_limit){
    Communicators::getInstance().setOutput("exit");
    world->quit();
  }

  Communicators::getInstance().run();
}
