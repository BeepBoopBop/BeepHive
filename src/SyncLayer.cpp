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
}
