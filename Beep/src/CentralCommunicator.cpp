#include <boost/mpi.hpp>
#include <boost/serialization/base_object.hpp>
#include <vector>

#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "CentralCommunicator.h"
#include "World.h"

std::string CentralCommunicator::run(std::string& message)
{
  boost::mpi::communicator comm;

  comm.barrier();

  std::vector<std::string> central_recv;
  gather(comm,message,central_recv,0);

  //receive updates sent from GUI to all processes
  std::string backend_recv = message;
  broadcast(comm,backend_recv,0);
  if(comm.rank() == 0){
    //! \todo aggregate results from all processes
    if(central_recv.size() > 1){
      return central_recv[1];
    }else{
      return "";
    }
  }else{
    return backend_recv;
  }
}
