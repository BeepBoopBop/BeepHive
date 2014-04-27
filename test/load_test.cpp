#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "World.h"
#include "Factory.h"
#include "CustomBeepFactory.h"
#include "Beep.h"
#include "test.h"

int main(int argc, char** argv)
{
  std::string file_name;
  if(argc >= 2){
    file_name = argv[1];
  }else{
    std::cout << "Enter name of shared library: ";
    std::cin >> file_name;
  }

  BeepHiveConfigs& configs=BeepHiveConfigs::getInstance();
  configs.initialize(argc,argv);
  configs.setTimeLimit(2);

  Factories<Command>& command_factories = Factories<Command>::getInstance();

  World world;

  FactoryParams params = {"MyBeep", "Beep"};
  runCommand("CustomBeepCommand",params,&world);

  std::cout << "TESTING SHARED LIBRARY LOADING" << std::endl;
  params.clear();
  params.push_back(file_name);
  runCommand("LoadCommand",params,&world);

  std::cout << "LOADED LIBRARY, " << file_name << ", TESTING" << std::endl;

  params = {"Controller","FlockingController","FlockingController","MyBeep"};
  runCommand("CustomBeepFeatureCommand",params,&world);

  params = {"Sensor","AverageX","AverageSensor","MyBeep","x"};
  runCommand("CustomBeepFeatureCommand",params,&world);

  std::cout << "SUCCESSFULLY RAN COMMAND FROM " << file_name << std::endl;

  world.start();

  std::cout << "DONE" << std::endl;
}
