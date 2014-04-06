#include <string>
#include <boost/serialization/base_object.hpp>
#include <boost/mpi.hpp>

#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "SyncLayer.h"

SyncLayer::SyncLayer() : DiscreteTimeLayer(1) {}

SyncLayer::SyncLayer(double event_frequency) : DiscreteTimeLayer(event_frequency) {}

void SyncLayer::update(const Event* event, World* world)
{
  DEBUG("Updating SyncLayer");
  DiscreteTimeLayer::update(event, world);
  boost::mpi::communicator comm;

  comm.barrier();

  //Send a message to the GUI
  std::string send=world->getMessagesToGui();
  world->clearMessagesToGui();

  //!Exit based on configuration
  double time_limit=BeepHiveConfigs::getInstance().getTimeLimit();
  if(time_limit>0 && event->getTime() > time_limit){
    //-- std::cout << "Exiting: time is: " << event-> getTime() << " which is past " << time_limit << std::endl;
    send="exit";
    world->quit();
  }

  gather(comm,send,&send,0);

  //receive updates sent from GUI to all processes
  std::string recv;
  broadcast(comm,recv,0);
  world->setMessagesFromGui(recv);
  //-- std::cout << "Received: " << recv << std::endl;
}
