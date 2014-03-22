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
    std::cout << "I am the GUI!" << std::endl;
    return 0;
  }else{
    World world;
    world.step();
    std::cout << "Hello World" << std::endl;
    return 0;
  }

  std::cout << "This should never print. Either gui or back-end should have returned"
            << std::endl;
  return 0;
}
