#include "Pattern.h"
#include "Command.h"

CreateWithPatternCommand::CreateWithPatternCommand(FactoryParams params)
  : CreateCommand(params) {}

void CreateWithPatternCommand::run(World* world)
{
  if(world != NULL){
    Factories<Pattern>& pattern_factories = Factories<Pattern>::getInstance();
    Factories<Command>& command_factories = Factories<Command>::getInstance();

    Factory<Command>* command_factory;
    Factory<Pattern>* pattern_factory = pattern_factories[concrete_type];
    Pattern* pattern;
    Command* command;

    FactoryParams::iterator it = params.begin();

    pattern_factory = pattern_factories[concrete_type];

    //use first string for pattern params
    FactoryParams pattern_params;
    pattern_params.push_back(*it++);
    pattern = pattern_factory->create(pattern_params);

    //use second string for command params
    command_factory = command_factories[*it++];

    //remaining params go to the object to be created
    FactoryParams template_params;
    template_params.insert(template_params.begin(),it,params.end());

    //create objects, tacking on pattern params
    while(!pattern->isEmpty()){
      FactoryParams command_params = template_params;
      FactoryParams pattern_data = pattern->getNext();
      for(size_t i=0; i<pattern_data.size(); ++i){
        command_params.push_back(pattern_data[i]);
      }
      command = command_factory->create(command_params);
      command->run(world);
      delete command;
    }
  }
}



Command* CreateWithPatternCommandFactory::create()
{
  FactoryParams params;
  return new CreateWithPatternCommand(params);
}



Command* CreateWithPatternCommandFactory::create(FactoryParams& params)
{
  return new CreateWithPatternCommand(params);
}



ADD_TO_FACTORIES(CreateWithPatternCommand, Command);
