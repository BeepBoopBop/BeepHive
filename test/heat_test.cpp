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
  configs.setTimeLimit(0.1);

  Communicators& communicators = Communicators::getInstance();
  communicators.addCommunicator("central",new CentralCommunicator());

  if(comm.rank()==0){
    DEBUG_OUT("I am the GUI!");
    std::vector<std::string> updates;
    bool run=true;

    while(run){
      communicators.run();
      while(!communicators.isEmpty()){
        SerialObject object = communicators.popObject();
        std::cout << "TYPE: " << object.type << " STRING: " 
                  << object.JSON << std::endl;
        if(object.type == "Exit"){
          run=false;
        }
      }
    }
    
    DEBUG_OUT("Exiting frontend");
    return 0;
  }else{
    World world;
    EnvObject* Obj1 = new EnvObject( 100, 200, 40, 50, true );
    world.addObject(Obj1);
    EnvObject* Obj2 = new EnvObject( 700, 800, 50, 60, false);
    world.addObject(Obj2);
    Layer* heat_layer = new HeatLayer(0.01);
    world.addLayer( "HeatLayer", heat_layer );
    world.start();

    DEBUG_OUT("Exiting backend");
    return 0;
  }

  DEBUG_OUT("This should never print. Either gui or back-end should have returned");
  return 0;
}

