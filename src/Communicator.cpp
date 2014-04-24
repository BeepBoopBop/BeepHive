#include "Communicator.h"
//#include "BeepHive.h"

void Communicators::run()
{
  //input="[";
  Map<Communicator*>::iterator it;
  for(it=communicators.begin(); it!=communicators.end(); ++it){
    input=input + " " + it->second->run(output);
  }
  output=std::string();
}



void Communicators::addCommunicator(std::string name, Communicator* communicator)
{
  communicators[name]=communicator;
}



std::string Communicators::getInput()
{
  std::string temp=input;
  input="";
  return "I am a string";
}



void Communicators::addToOutput(std::string object)
{
  output += object + " ";
}

void Communicators::setOutput(std::string output)
{
  this->output=output;
}
