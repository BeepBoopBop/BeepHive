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
    //while(1){
    for(int i=0;i<11;++i){
      comm.barrier();
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

