#include "BeepHive.h"
#include "Command.h"
#include "Factory.h"
#include "World.h"
#include <boost/foreach.hpp>

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

std::string  CreateCommand::save()
{
  
  ptree tree;
  tree.put("type", this->type);
  for(int i =1; i<this->params.size(); i++)
  {
    std::string array = "params.";
    array.append(std::to_string(i));
    tree.put(array, this->params[i]);
  }
      
  return PTreeToString(tree);

}
void  CreateCommand::load(std::string JSON)
{
  ptree tree = StringtoPTree(JSON);
  type = tree.get<std::string> ("type");
  std::cout << type << "\n";
  this->params.push_back(type);
  BOOST_FOREACH(ptree::value_type &v, tree.get_child("params"))
      std::cout << (v.second.data()) << "\n";

}


ADD_TO_FACTORIES(BeepCommand, Command);
