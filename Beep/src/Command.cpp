#include "BeepHive.h"
#include "Command.h"
#include "Factory.h"
#include "World.h"

void Command::run()
{
  this->run(NULL);
}

CreateCommand::CreateCommand(FactoryParams params)
  : params()
{
  assert(params.size()>=1);
  this->concrete_type=params[0];

  for(int i=1; i<params.size(); ++i){
    this->params.push_back(params[i]);
  }
}


void  CreateCommand::saveHelper(ptree& tree)
{
  tree.put("concrete_type", this->concrete_type);
  for(int i =1; i<this->params.size(); i++)
  {
    std::string array = "params.";
    array.append(std::to_string(i));
    tree.put(array, this->params[i]);
  }
  return;
}



void  CreateCommand::load(std::string JSON)
{
  DEBUG("CREATECOMMAND")
  ptree tree = StringtoPTree(JSON);
  DEBUG("JSON done")
  concrete_type = tree.get<std::string> ("concrete_type");
  DEBUG("2")
  std::cout << concrete_type << "\n";
  BOOST_FOREACH(ptree::value_type &v, tree.get_child("params.")){
  DEBUG("3")
      std::cout << (v.second.data()) << "\n";
  DEBUG("4")
      this->params.push_back(v.second.data());
  }
}
