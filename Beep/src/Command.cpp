#include "BeepHive.h"
#include "Command.h"
#include "Factory.h"
#include "World.h"
#include <boost/foreach.hpp>

void Command::run()
{
  this->run(NULL);
}

CreateCommand::CreateCommand(FactoryParams params)
  : params()
{
  assert(params.size()>=1);
  this->type=params[0];

  for(int i=1; i<params.size(); ++i){
    this->params.push_back(params[i]);
  }
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
