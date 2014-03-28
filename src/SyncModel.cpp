#include "BeepHive.h"
#include "SyncModel.h"

SyncModel::SyncModel() : DiscreteTimeModel(1) {}

SyncModel::SyncModel(double event_frequency) : DiscreteTimeModel(event_frequency) {}

void SyncModel::update(const Event* event)
{
  DEBUG("Updating SyncModel");
  DiscreteTimeModel::update(event);
  boost::mpi::communicator comm;
  comm.barrier();
}
