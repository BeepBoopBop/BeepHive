#include "BeepHiveConfigs.h"
#include "CentralCommunicator.h"

std::string CentralCommunicator::run(std::string& message)
{
  boost::mpi::communicator comm;

  comm.barrier();

  //!Exit based on configuration
  double time_limit=BeepHiveConfigs::getInstance().getTimeLimit();
  //if(time_limit>0 && event->getTime() > time_limit){
    //message="exit";
    //world->quit();
  //}

  std::string temp;
  gather(comm,message,&temp,0);

  //receive updates sent from GUI to all processes
  std::string recv;
  broadcast(comm,recv,0);
  return recv;
}
