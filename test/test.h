#ifndef TEST_H
#define TEST_H 

#include "BeepHive.h"
#include "Factory.h"
#include "Command.h"

//Creates and executes a command based on parameters
void runCommand(std::string command_type, 
                FactoryParams params, World* world)
{
  Command* command;
  Factory<Command>* command_factory;

  std::cout << "RUNNING: " << command_type << " COMMAND" << std::endl;
  std::cout << "ARGS:";
  for(size_t i=0; i<params.size(); ++i){
    std::cout << " " << params[i];
  }
  std::cout << std::endl;

  command_factory = Factories<Command>::getInstance()[command_type];
  command = command_factory->create(params);
  command->run(world);

  delete command;

  std::cout << "SUCCESSFULLY RAN: " << command_type << " COMMAND" << std::endl;

  return;
}

#endif /* TEST_H */
