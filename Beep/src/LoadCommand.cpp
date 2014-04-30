#include <dlfcn.h>

#include "Serializable.h"
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
  return;
}



void  LoadCommand::saveHelper(ptree& tree)
{
  tree.put("file_name", this->file_name);
  return;
}



void LoadCommand::load(std::string JSON)
{
  if(JSON.size() > 0){
    ptree tree = StringToPTree(JSON);
    this->file_name = tree.get<std::string>("file_name");
  }
  return;
}



Command* LoadCommandFactory::create()
{
  return new LoadCommand("");
}



Command* LoadCommandFactory::create(FactoryParams& params)
{
  if(params.size() >= 1){
    return new LoadCommand(params[0]);
  }else{
    return NULL;
  }
}

ADD_TO_FACTORIES(LoadCommand, Command);
