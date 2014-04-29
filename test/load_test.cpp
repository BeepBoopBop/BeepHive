#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "World.h"
#include "Factory.h"
#include "CustomBeepFactory.h"
#include "Beep.h"
#include "Sensor.h"
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

  Factories<Command>& command_factories = Factories<Command>::getInstance();
  Factories<Sensor>& sensor_factories = Factories<Sensor>::getInstance();

  //assert(sensor_factories["AverageSensor"] == NULL);
  
  std::cout << "TESTING SHARED LIBRARY LOADING" << std::endl;

  FactoryParams params;
  params.push_back(file_name);
  runCommand("LoadCommand",params,NULL);

  std::cout << "LOADED LIBRARY, " << file_name << ", TESTING" << std::endl;

  assert(sensor_factories["AverageSensor"] != NULL);

  std::cout << "SUCCESSFULLY RAN COMMAND FROM " << file_name << std::endl;
  std::cout << "DONE" << std::endl;
}
