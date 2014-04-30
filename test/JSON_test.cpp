#include <string>
#include <vector>
#include <boost/serialization/base_object.hpp>
#include <boost/mpi.hpp>
#include <iostream>
#include "LightSensor.h"
#include "AverageSensor.h"
#include "SyncLayer.h"

#include "Beep.h"
#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "World.h"
#include "Communicator.h"
#include "CentralCommunicator.h"
#include "Command.h"
#include "Beep.h"

namespace mpi=boost::mpi;
int main(int argc, char** argv)
{

  //necessary configuration to run program
  BeepHiveConfigs& configs=BeepHiveConfigs::getInstance();
  configs.initialize(argc,argv);
  configs.setTimeLimit(10);

  //create a beep command with these factoryparams
  std::vector<std::string> v {"int", "one", "two", "three"};
  BeepCommand beep = BeepCommand(v);

  //save and print the serialization
  std::string json1 = beep.save();
  std::cout<< json1;
  //construct new beep by loading serialization
  BeepCommand beep2 = BeepCommand();
  beep2.load(json1);

  //resave to see if it worked
  std::cout << beep2.save();

  Beep* mybeep = new Beep();
  mybeep->setState("meh",2.0);
  mybeep->setState("arg",3.0);
  std::cout << mybeep->save();
  Beep* mybeep2 = new Beep();
  mybeep2->load(mybeep->save());
  std::cout << mybeep2->save();



  ptree p;
  p.put("type", "double");
  p.put("objects.0", 3.14);
  p.put("objects.1", 6.28);
  ptree p2;
  p2.put("type", "int");
  p2.put("objects.0", 1);
  p2.put("objects.1", 2);
  SerialObject n;
  //n.type = "int";
  //n.JSON = Serializable::PTreeToString(p);
  //test out communicator serialization
  //Communicators::getInstance().addToOutput(Serializable::PTreeToString(p));
  //Communicators::getInstance().addToOutput(Serializable::PTreeToString(p2));
  std::string str = Communicators::getInstance().getStringOutput();
  
  std::cout << str;
  Communicators::getInstance().constructStack();
  //n = Communicators::getInstance().popObject();
  //std::cout << n.type << " " << n.JSON;
  //n = Communicators::getInstance().popObject();
  //std::cout << n.type << " " << n.JSON;

}
