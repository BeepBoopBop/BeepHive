#include "BeepHive.h"
#include "Command.h"
#include "Factory.h"
#include "World.h"

CreateCommand::CreateCommand(FactoryParams params)
{
  assert(params.size()>=2);
  this->type=params[0];

  FactoryParams::iterator it;
  for(it=params.begin(); it!=params.end(); ++it){
    this->params.push_back(*it);
  }
}



BeepCommand::BeepCommand(FactoryParams params) : CreateCommand(params) {}



void BeepCommand::run(World* world)
{
  Beep* beep = Factories<Beep>::getInstance()[type]->create(params);
  world->addBeep(beep);
}



Command* BeepCommandFactory::create()
{
  FactoryParams params;
  return create(params);
}



Command* BeepCommandFactory::create(FactoryParams& params)
{
  return new BeepCommand(params);
}



ADD_TO_FACTORIES(BeepCommand, Command);
