#include "Communicator.h"
//#include "BeepHive.h"


Communicators::Communicators()
{
  outputTree.put("count",-1);
  inputTree.put("count", -1);
}


void Communicators::run()
{
  Map<Communicator*>::iterator it;
  for(it=communicators.begin(); it!=communicators.end(); ++it)
  {
    ptree input = Serializable::StringtoPTree(it->second->run(output));

    //input=input + " " + it->second->run(output);
    //loop through all of the objects in the input and add them to inputTree 
    BOOST_FOREACH(ptree::value_type &v, input.get_child("obj"))
    {
      addToInput(v.second.data());
    }
  }
  output=std::string();
  
  constructStack();
  
  
}

void Communicators::constructStack()
{
 // const ptree& children = inputTree.get_child("obj");
  BOOST_FOREACH(ptree::value_type &v, inputTree.get_child("obj"))
  {
    const ptree& tree = v.second;
    SerialObject n;
    n.type = tree.get<std::string>("type");//.second.data();
    n.JSON = Serializable::PTreeToString(v.second);
    std::cout << (Serializable::PTreeToString(v.second));
    inputStack.push(n); 
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
  so = inputStack.top();
  inputStack.pop();
 return so;
}

void Communicators::addToInput(std::string object)
{
    int count = inputTree.get<int>("count");
    count++;
    inputTree.put("count", count);
    std::string array = "obj.";
    array.append(std::to_string(count));
    inputTree.put(array, object);

}


void Communicators::addToOutput(std::string object)
{
    ptree p = Serializable::StringtoPTree(object);
    int count = outputTree.get<int>("count");
    count++;
    outputTree.put("count", count);
    std::string array = "obj.";
    array.append(std::to_string(count));
    //std::cout << array << " " << object << '\n';
    //outputTree.put(array, " ");
    //outputTree.push_back(ptree::value_type(array, p));
    outputTree.put_child(array, p);

}


void Communicators::setOutput(std::string output)
{
  this->output=output;
}


std::string Communicators::getStringOutput()
{
    return Serializable::PTreeToString(outputTree); 
}

bool Communicators::isEmpty(){
  return inputStack.empty();
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
