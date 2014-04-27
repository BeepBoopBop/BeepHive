#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "World.h"
#include "Factory.h"
#include "CustomBeepFactory.h"
#include "Beep.h"
#include "test.h"

int main(int argc, char** argv)
{
  BeepHiveConfigs& configs=BeepHiveConfigs::getInstance();
  configs.parseArgs(argc,argv);
  configs.setTimeLimit(2);

  Factories<Command>& command_factories = Factories<Command>::getInstance();

  std::cout << "AVAILABLE COMMANDS:" << std::endl;
  Factories<Command>::iterator it;
  for(it=command_factories.begin(); it!=command_factories.end(); ++it){
    std::cout << "  " << it->first << std::endl;
  }

  std::cout << "\nTESTING COMMANDS:\n" << std::endl;

  World world;

  FactoryParams params = {"MyBeep", "Beep"};
  runCommand("CustomBeepCommand",params,&world);

  params = {"Sensor","AverageX","AverageSensor","MyBeep","x"};
  runCommand("CustomBeepFeatureCommand",params,&world);

  params = {"Sensor","AverageY","AverageSensor","MyBeep","y"};
  runCommand("CustomBeepFeatureCommand",params,&world);

  params = {"Manipulator","OmegaVelocityManipulator",
            "OmegaVelocityManipulator","MyBeep"};
  runCommand("CustomBeepFeatureCommand",params,&world);

  params = {"Controller","FlockingController","FlockingController","MyBeep"};
  runCommand("CustomBeepFeatureCommand",params,&world);

  params = {"MyBeep"};
  runCommand("BeepCommand",params,&world);

  params = {"RectanglePattern", "2 2 10", "BeepCommand", "MyBeep"};
  runCommand("CreateWithPatternCommand",params,&world);

  params = {"HeatLayer","HeatLayer","1"};
  Command* command=command_factories["LayerCommand"]->create(params);
  //command->run(&world);
  //std::cout << "SUCCESSFULLY ADDED HEAT LAYER TO WORLD" << std::endl;


  std::cout << "\nRUNNING WORLD" << std::endl;
  world.start();
  std::cout << "RAN WORLD SUCCESSFULLY" << std::endl;

  return 0;
}
