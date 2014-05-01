#ifndef TEST_H
#define TEST_H 

#include "BeepHive.h"
#include "Factory.h"
#include "Command.h"
#include "Communicator.h"

//Test that commands can be recreated with save and load
void saveLoad(Command* command)
{
  Factories<Command>& factories = Factories<Command>::getInstance();
  std::string command_string = command->save();
  std::cout << "JSON: " << command_string << std::endl;

  Command* second = factories[command->type()]->create();
  second->load(command_string);
  std::string second_string = second->save();
  std::cout << "JSON2: " << second_string << std::endl;
  assert(command_string == second_string);
}

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

  saveLoad(command);

  Communicators::getInstance().addToOutput(command->save());
  command->run(world);

  delete command;

  std::cout << "SUCCESSFULLY RAN: " << command_type << " COMMAND" << std::endl;

  return;
}

#endif /* TEST_H */
