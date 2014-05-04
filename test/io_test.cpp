#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "World.h"
#include "Factory.h"
#include "CustomBeepFactory.h"
#include "Beep.h"
#include "test.h"
#include "Communicator.h"

int main(int argc, char** argv)
{
  BeepHiveConfigs& configs=BeepHiveConfigs::getInstance();
  configs.initialize(argc,argv);
  configs.setTimeLimit(2);

  //singletons
  Factories<Communicator>& communicator_factories 
    = Factories<Communicator>::getInstance();
  Factories<Command>& command_factories = Factories<Command>::getInstance();
  Communicators& communicators = Communicators::getInstance();

  FactoryParams params = {"file.bh"};
  Communicator* save = communicator_factories["OutFileCommunicator"]->create(params);
  DEBUG_OUT("CREATED INPUT COMMUNICATOR");

  communicators.addCommunicator("save",save);

  //create a command
  params = {"MyBeep", "Beep"};
  Command* command = command_factories["CustomBeepCommand"]->create(params);
  DEBUG_OUT("CREATED COMMAND");


  //output the ocmmand to a file
  communicators.addToOutput(command->save());
  communicators.run();
  DEBUG_OUT("RAN INPUT COMMUNICATOR");

  //load file
  params = {"file.bh"};
  Communicator* load = communicator_factories["InFileCommunicator"]->create(params);
  communicators.addCommunicator("load",load);
  DEBUG_OUT("CREATED OUTPUT COMMUNICATOR");

  communicators.run();

  DEBUG_OUT("RAN OUTPUT COMMUNICATOR");

  //check results
  assert(!communicators.isEmpty());
  SerialObject object = communicators.popObject();

  assert(object.JSON == command->save());

  DEBUG_OUT("PASSED TEST");

  delete command;

  return 0;
}
