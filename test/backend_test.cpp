#include <string>
#include <vector>
#include <boost/serialization/base_object.hpp>
#include <boost/mpi.hpp>
#include <iostream>

#include "BeepHive.h"
#include "World.h"

namespace mpi=boost::mpi;



int main(int argc, char** argv)
{
  mpi::environment env;
  mpi::communicator comm;

  BeepHiveConfigs::getInstance().parseArgs(argc,argv);

  if(comm.rank()==0){
    DEBUG("I am the GUI!");
    std::vector<std::string> updates;
    bool run=true;
    while(run){
      comm.barrier();

      //Receive messages from each process
      std::string send;
      gather(comm,send,updates,0);
      for(int i=1;i<updates.size();++i){
        std::cout << "Rank " << i << " sent: " << updates[i] << std::endl;
        if(updates[i] == "exit"){
          run=false;
        }

      }

      /*
       * Send updates uniformly to all processes
       * Messages from GUI should be short because they are generated by user
       * input. However, we don't have MPI3 instant collectives which would be
       * required to implement an algorithm that only sends to specific
       * processes
       */
      send="Hi I'm root!";
      broadcast(comm,send,0);

      sleep(1);
    }
    
    DEBUG("Exiting frontend");
    return 0;
  }else{
    World world;
    world.start();
    DEBUG("Exiting backend");
    return 0;
  }

  DEBUG("This should never print. Either gui or back-end should have returned");
  return 0;
}
