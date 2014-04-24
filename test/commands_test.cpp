#include <string>
#include <vector>
//#include <boost/serialization/base_object.hpp>
//#include <boost/mpi.hpp>
#include <iostream>

#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "World.h"
#include "Factory.h"
#include "CustomBeepFactory.h"
#include "Beep.h"

//namespace mpi=boost::mpi;

int main(int argc, char** argv)
{
  BeepHiveConfigs& configs=BeepHiveConfigs::getInstance();
  configs.parseArgs(argc,argv);
  configs.setTimeLimit(2);

  Factories<Command>& command_factories = Factories<Command>::getInstance();
  Factories<Beep>& beep_factories = Factories<Beep>::getInstance();

  std::cout << "AVAILABLE COMMANDS:" << std::endl;
  Factories<Command>::iterator it;
  for(it=command_factories.begin(); it!=command_factories.end(); ++it){
    std::cout << "  " << it->first << std::endl;
  }

  std::cout << "\nTESTING COMMANDS:\n" << std::endl;

  World world;

  Command* command;
  FactoryParams params;
  params.push_back("MyBeep");
  params.push_back("Beep");
  command=command_factories["CustomBeepCommand"]->create(params);
  command->run(&world);
  assert(beep_factories["MyBeep"]);
  std::cout << "SUCCESSFULLY ADDED MYBEEP" << std::endl;

  delete command;
  params.clear();

  params.push_back("Sensor");
  params.push_back("Average");
  params.push_back("AverageSensor");
  params.push_back("MyBeep");
  params.push_back("x");
  command=command_factories["CustomBeepFeatureCommand"]->create(params);
  command->run(&world);
  std::cout << "SUCCESSFULLY ADDED SENSOR x" << std::endl;

  delete command;

  params[4]="y";
  command=command_factories["CustomBeepFeatureCommand"]->create(params);
  command->run(&world);
  std::cout << "SUCCESSFULLY ADDED SENSOR y" << std::endl;

  delete command;
  params.clear();

  params.push_back("Manipulator");
  params.push_back("OmegaVelocityManipulator");
  params.push_back("OmegaVelocityManipulator");
  params.push_back("MyBeep");
  command=command_factories["CustomBeepFeatureCommand"]->create(params);
  command->run(&world);
  std::cout << "SUCCESSFULLY ADDED MANIPULATOR" << std::endl;

  delete command;
  params.clear();

  params.push_back("MyBeep");
  command=command_factories["BeepCommand"]->create(params);
  command->run(&world);
  std::cout << "SUCCESSFULLY ADDED BEEP TO WORLD" << std::endl;

  delete command;
  params.clear();

  std::cout << "\nRUNNING WORLD" << std::endl;
  world.start();
  std::cout << "RAN WORLD SUCCESSFULLY" << std::endl;

  return 0;
}
