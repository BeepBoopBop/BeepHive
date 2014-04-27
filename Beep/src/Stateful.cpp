#include "Stateful.h"

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



Map<double>::iterator Stateful::findState(std::string state_name)
{
  size_t scope_location = state_name.find(SCOPE);
  if(scope_location == std::string::npos){
    Map<double>::iterator it;
    return states.find(state_name);
  }else{
    std::string child_name = state_name.substr(0,scope_location-1);
    std::cout << "Found child: " << child_name << std::endl;
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
