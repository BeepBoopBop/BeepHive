#include <string>
#include <boost/serialization/base_object.hpp>
#include <boost/mpi.hpp>

#include "BeepHive.h"
#include "SyncLayer.h"

SyncLayer::SyncLayer() : DiscreteTimeLayer(1) {}

SyncLayer::SyncLayer(double event_frequency) : DiscreteTimeLayer(event_frequency) {}

void SyncLayer::update(const Event* event)
{
  DEBUG("Updating SyncLayer");
  DiscreteTimeLayer::update(event);
  boost::mpi::communicator comm;

  comm.barrier();

  //Send a message to the GUI
  std::string send="SyncLayer just sent a message";
  if(event->getTime() > 9){
    send="exit";
  }
  gather(comm,send,&send,0);

  //receive updates sent from GUI to all processes
  std::string recv;
  broadcast(comm,recv,0);
  std::cout << "Received: " << recv << std::endl;
}
