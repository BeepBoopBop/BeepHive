#include <boost/serialization/base_object.hpp>
#include <boost/mpi.hpp>
#include <vector>
#include "World.h"
#include "BeepHiveConfigs.h"
#include "CentralCommunicator.h"
#include "BeepHive.h"

std::string CentralCommunicator::run(std::string& message)
{
  boost::mpi::communicator comm;

  comm.barrier();

  //!Exit based on configuration
  double time_limit=BeepHiveConfigs::getInstance().getTimeLimit();

  std::vector<std::string> central_recv;
  gather(comm,message,central_recv,0);

  //receive updates sent from GUI to all processes
  std::string backend_recv = message;
  broadcast(comm,backend_recv,0);
  if(comm.rank() == 0){
    return central_recv[1];
  }else{
    return backend_recv;
  }
}
