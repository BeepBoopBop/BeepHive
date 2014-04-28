#include <string>
#include <vector>
#include <boost/serialization/base_object.hpp>
#include <boost/mpi.hpp>
#include <iostream>

#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "World.h"
#include "HeatLayer.h"
#include "Communicator.h"
#include "CentralCommunicator.h"

namespace mpi=boost::mpi;



int main(int argc, char** argv)
{
  mpi::environment env;
  mpi::communicator comm;

  BeepHiveConfigs& configs=BeepHiveConfigs::getInstance();
  configs.initialize(argc,argv);
  configs.setTimeLimit(10);

  Communicators& communicators = Communicators::getInstance();
  communicators.addCommunicator("central",new CentralCommunicator());

  if(comm.rank()==0){
    DEBUG("I am the GUI!");
    std::vector<std::string> updates;
    bool run=true;
    while(run){
      communicators.addToOutput("Hello!");
      communicators.run();
      //comm.barrier();
      std::string recv = communicators.getInput();

      std::cout << "Got:" << recv << std::endl;
      if(recv == " exit"){
        run=false;
      }
    }
    
    DEBUG("Exiting frontend");
    return 0;
  }else{
    World world;
    Layer* heat_layer = new HeatLayer;
    world.addLayer( "HeatLayer", heat_layer );
    world.start();

    DEBUG("Exiting backend");
    return 0;
  }

  DEBUG("This should never print. Either gui or back-end should have returned");
  return 0;
}

