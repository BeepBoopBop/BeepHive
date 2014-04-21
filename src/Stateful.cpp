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
