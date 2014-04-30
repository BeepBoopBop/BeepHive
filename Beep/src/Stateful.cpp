#include "Stateful.h"
#include "BeepHive.h"
#include "Command.h"
#include "World.h"
#include "Factory.h"
#include "Serializable.h"

void Stateful::setState(std::string state_name, double initial_state)
{
  states[state_name]=initial_state;
}



double Stateful::getState(std::string state_name)
{
  //states default to zero for now
  if(states.find(state_name) == states.end())
    states[state_name]=0;
  return states[state_name];
}



void Stateful::addChild(std::string stateful_name, Stateful* stateful)
{
  children[stateful_name]=stateful;
}



Stateful* Stateful::getChild(std::string stateful_name)
{
  Map<Stateful*>::iterator it;
  it = children.find(stateful_name);
  assert(it != children.end());
  return it->second;
}



//!This is not yet complete
void  Stateful::saveHelper(ptree& tree)
{
  //create tree
  //add states map
  //add children recursively
  ptree state_tree;
  StateIterator it;
  for(it=states.begin(); it!=states.end(); ++it){
    state_tree.put(it->first, it->second);
  }
  tree.add_child("states",state_tree);
  
  return;
}



void Stateful::load(std::string JSON)
{
  if(JSON.size() > 0){
    ptree tree = StringToPTree(JSON);
    const ptree& children = tree.get_child("states");
    //std::cout << PTreeToString(children);
    BOOST_FOREACH(const ptree::value_type &v, children){
      double val;
      std::stringstream stream(v.second.data());
      stream >> val;
      states[v.first] = val;
    }
  }
}




Map<double>::iterator Stateful::findState(std::string state_name)
{
  size_t scope_location = state_name.find(SCOPE);
  if(scope_location == std::string::npos){
    Map<double>::iterator it;
    return states.find(state_name);
  }else{
    std::string child_name = state_name.substr(0,scope_location-1);
    Map<Stateful*>::iterator it = children.find(child_name);

    if(it == children.end()){
      return states.end();
    }else{
      size_t child_name_start = scope_location + std::string(SCOPE).length();
      std::string child_state_name = state_name.substr(child_name_start);
      return it->second->findState(child_state_name);
    }
  }
}
