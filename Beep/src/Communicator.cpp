#include "Communicator.h"
//#include "BeepHive.h"


Communicators::Communicators()
{
  outputTree.put("count", -1);
}


void Communicators::run()
{
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
  return temp;
}


void Communicators::addToOutput(std::string object)
{
    int count = outputTree.get<int>("count");
    count++;
    outputTree.put("count", count);
    std::string array = "objects.";
    array.append(std::to_string(count));
    outputTree.put(array, object);

}


void Communicators::setOutput(std::string output)
{
  this->output=output;
}


std::string Communicators::getStringOutput()
{
    return Serializable::PTreeToString(outputTree);
}



CommunicatorCommand::CommunicatorCommand(FactoryParams params)
  : CreateCommand(params) {}
  


void CommunicatorCommand::run(World* world)
{
  Factories<Communicator>& factories = Factories<Communicator>::getInstance();
  Communicator* communicator = factories[concrete_type]->create(params);
  Communicators::getInstance().addCommunicator(params[0], communicator);
}



NOT_IMPLEMENTED(Command* CommunicatorCommandFactory::create())



Command* CommunicatorCommandFactory::create(FactoryParams& params)
{
  return new CommunicatorCommand(params);
}
