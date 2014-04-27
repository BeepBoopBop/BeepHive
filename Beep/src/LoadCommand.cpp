#include <dlfcn.h>

#include "LoadCommand.h"
#include "BeepHive.h"
#include "World.h"

LoadCommand::LoadCommand(std::string file_name)
  : file_name(file_name) {}



void LoadCommand::run(World* world)
{
  void* handle;
  char* error;
  handle = dlopen(file_name.c_str(), RTLD_NOW);
  if(handle){
    std::cout << "LOADED: " << file_name << std::endl;
  }else{
    std::cout << "ERROR LOADING PLUGIN: " << dlerror() << std::endl;
  }
}



NOT_IMPLEMENTED(Command* LoadCommandFactory::create())



Command* LoadCommandFactory::create(FactoryParams& params)
{
  if(params.size() >= 1){
    return new LoadCommand(params[0]);
  }else{
    return NULL;
  }
}

ADD_TO_FACTORIES(LoadCommand, Command);
