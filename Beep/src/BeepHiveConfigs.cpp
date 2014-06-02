#include <getopt.h>
#include <iostream>
#include <stdlib.h>

#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "Command.h"
#include "Communicator.h"
#include "Factory.h"

BeepHiveConfigs::BeepHiveConfigs() 
  : time_limit(-1), gui_enabled(true), load_standard_plugin(true) {}

void BeepHiveConfigs::initialize(const int argc, char** argv)
{
  //Parse arguments
  while(1){
    //options struct for getopt
    static struct option long_options[]=
    {
      {"nogui", no_argument, 0, 'n'},
      {"input", required_argument, 0, 'i'},
      {"output", required_argument, 0, 'o'},
      {0, 0, 0, 0}
    };
    int option_index=0;

    int val=getopt_long(argc, argv, "n", long_options, &option_index);
    if(val == -1){
      break;
    }

    Communicator* communicator;
    FactoryParams params;
    switch(val){
      case 'n':
        this->gui_enabled=false;
        break;
      case 'i':
        std::cout << "INPUT FILE: " << optarg << std::endl;
        params = {optarg};
        communicator = Factories<Communicator>::getInstance()
          ["InFileCommunicator"]->create(params);
        Communicators::getInstance().addCommunicator("input",communicator);
        break;
      case 'o':
        std::cout << "OUTPUT FILE: " << optarg << std::endl;
        params = {optarg};
        communicator = Factories<Communicator>::getInstance()
          ["OutFileCommunicator"]->create(params);
        Communicators::getInstance().addCommunicator("output",communicator);
        break;
      default:
        //help();
        exit(0);
        break;
    }
  }

  if(this->load_standard_plugin){
    Factories<Command>& command_factories = Factories<Command>::getInstance();
    FactoryParams params = {BEEP_PLUGIN};
    Command* load = command_factories["LoadCommand"]->create(params);
    load->run();
    delete load;
  }
}

void BeepHiveConfigs::setTimeLimit(double time_limit)
{
  this->time_limit=time_limit;
}

double BeepHiveConfigs::getTimeLimit()
{
  return time_limit;
}

bool BeepHiveConfigs::guiEnabled()
{
#ifdef GUI
  return gui_enabled;
#else
  return false;
#endif
};
