#include "Communicator.h"
//#include "BeepHive.h"

Communicators& Communicators::getInstance()
{
  static Communicators instance;
  return instance;
}



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
  input=std::string();
  return temp;
}



void Communicators::addToOutput(std::string object)
{
  output += object + " ";
}

void Communicators::setOutput(std::string output)
{
  this->output=output;
}
