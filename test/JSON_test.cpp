#include <string>
#include <vector>
#include <boost/serialization/base_object.hpp>
#include <boost/mpi.hpp>
#include <iostream>
#include "LightSensor.h"
#include "AverageSensor.h"
#include "SyncLayer.h"

#include "Beep.h"
#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "World.h"
#include "Communicator.h"
#include "CentralCommunicator.h"
#include "Command.h"

namespace mpi=boost::mpi;
int main(int argc, char** argv)
{
  mpi::environment env;
  mpi::communicator comm;

  BeepHiveConfigs& configs=BeepHiveConfigs::getInstance();
  configs.parseArgs(argc,argv);
  configs.setTimeLimit(10);

  Communicators::getInstance().addCommunicator("central",new CentralCommunicator());
  std::vector<std::string> v {"int", "one", "two", "three"};
  BeepCommand beep = BeepCommand(v);
  std::string json1 = beep.save();
  std::cout<< json1;
  BeepCommand beep2 = BeepCommand();
  beep2.load(json1);




  //LightSensor l = LightSensor(5,10,15);
 // std::string json = l.save();
  //std::cout << json << "\n";
 // LightSensor l2;
  //l2.load(json);
}
