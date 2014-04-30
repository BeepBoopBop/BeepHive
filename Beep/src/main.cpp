#include <string>
#include <sstream>
#include <vector>
#include <boost/serialization/base_object.hpp>
#include <boost/mpi.hpp>
#include <iostream>

#ifdef GUI
#include "mainwindow.h"
#include <QApplication>
#endif

#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "World.h"
#include "Communicator.h"
#include "CentralCommunicator.h"
#include "FileCommunicator.h"

namespace mpi=boost::mpi;



int main(int argc, char** argv)
{
  mpi::environment env;
  mpi::communicator comm;
  int rank=comm.rank();

  BeepHiveConfigs& configs=BeepHiveConfigs::getInstance();
  configs.initialize(argc,argv);

  Communicators& communicators = Communicators::getInstance();
#ifdef GUI
  communicators.addCommunicator("central",new CentralCommunicator());
#endif
  if(rank==0){
#ifdef GUI
    if(configs.guiEnabled()){
      QApplication a(argc, argv);
      MainWindow w;
      w.show();
      return a.exec();
    }
#endif
    else{
      DEBUG("I am the GUI!");
      bool run=true;

      while(run){
        communicators.run();
        while(!communicators.isEmpty()){
          SerialObject object = communicators.popObject();
          std::cout << "TYPE: " << object.type << " STRING: " 
            << object.JSON << std::endl;
          if(object.type == "Exit"){
            run=false;
          }
        }
        DEBUG("Exiting frontend");
      }
      return 0;
    }
  }else{
    World world;
    world.start();
    DEBUG("Exiting backend");
    return 0;
  }

  DEBUG("This should never print. Either gui or back-end should have returned");
  return 0;
}


