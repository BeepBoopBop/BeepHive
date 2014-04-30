#include "Communicator.h"
#include "BeepHive.h"
#include "Serializable.h"


Communicators::Communicators()
{
  reset(output_tree);
  reset(input_tree);
}



void Communicators::reset(ptree& tree)
{
  tree.clear();
}



void Communicators::run()
{
  Map<Communicator*>::iterator it;
  std::string output = Serializable::PTreeToString(output_tree);

  reset(input_tree);

  for(it=communicators.begin(); it!=communicators.end(); ++it)
  {
    if(output.size() > 0){
      std::string input_string = it->second->run(output);
      ptree input = Serializable::StringToPTree(input_string);

      BOOST_FOREACH(ptree::value_type &v, input)
      {
        addToInput(Serializable::PTreeToString(v.second));
      }
    }
  }

  reset(output_tree);

  constructStack();
}



void Communicators::constructStack()
{
  BOOST_FOREACH(ptree::value_type &v, input_tree)
  {
    const ptree& tree = v.second;
    SerialObject n;
    n.type = tree.get<std::string>("type");
    n.JSON = Serializable::PTreeToString(v.second);
    input_stack.push(n); 
  }
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



SerialObject Communicators::popObject()
{
  SerialObject so;
  so = input_stack.top();
  input_stack.pop();
  return so;
}



void Communicators::addToInput(std::string object)
{
  if(object.size() > 0){
    ptree p = Serializable::StringToPTree(object);
    std::string array = "obj";
    input_tree.put_child(array, p);
  }
}



void Communicators::addToOutput(std::string object)
{
  if(object.size() > 0){
    ptree p = Serializable::StringToPTree(object);
    std::string array = "obj";
    output_tree.put_child(array, p);
  }
}



std::string Communicators::getStringOutput()
{
  return Serializable::PTreeToString(output_tree); 
}

bool Communicators::isEmpty(){
  return input_stack.empty();
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
