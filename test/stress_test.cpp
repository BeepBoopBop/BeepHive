#include "time.h"

#include "BeepHive.h"
#include "BeepHiveConfigs.h"
#include "World.h"
#include "Factory.h"
#include "CustomBeepFactory.h"
#include "Beep.h"
#include "test.h"


int main(int argc, char** argv)
{
  double target = 100;
  double eps = 0.05;
  if(argc >= 3){
    target = atoi(argv[1]);
    eps = atof(argv[2]);
  }

  BeepHiveConfigs& configs=BeepHiveConfigs::getInstance();
  configs.initialize(argc,argv);

  World world;

  //Create Beep type for the test
  FactoryParams params = {"MyBeep", "Beep"};
  runCommand("CustomBeepCommand",params,&world);

  params = {"Sensor","AverageX","AverageSensor","MyBeep","x"};
  runCommand("CustomBeepFeatureCommand",params,&world);

  params = {"Sensor","AverageY","AverageSensor","MyBeep","y"};
  runCommand("CustomBeepFeatureCommand",params,&world);

  params = {"Manipulator","OmegaVelocityManipulator",
            "OmegaVelocityManipulator","MyBeep"};
  runCommand("CustomBeepFeatureCommand",params,&world);

  params = {"Controller","FlockingController","FlockingController","MyBeep"};
  runCommand("CustomBeepFeatureCommand",params,&world);

  params = {"RectanglePattern", "2 2 10", "BeepCommand", "MyBeep"};

  unsigned beeps_added = 0;
  unsigned dim = 1;
  clock_t time;
  double elapsed;
  bool good = true;
  std::stringstream stream;

  //Run the stress test adding beeps until it fails
  do{
    stream.str("");
    stream << dim << " " << dim << " " << 10;
    params[1]=stream.str();
    runCommand("CreateWithPatternCommand",params,&world);

    std::cout << "ATTEMPTING: ADDING " << dim*dim << " BEEPS TO "
      << beeps_added << " EXISTING" << std::endl;

    for(int i=0; i<10 ; ++i){
      time = clock();
      //two steps because there are two layers
      world.step();
      world.step();
      elapsed = (double)(clock() - time)/CLOCKS_PER_SEC;

      if(elapsed > eps){
        good = false;
      }
    }

    if(good){
      beeps_added += dim*dim;
      ++dim;
      std::cout << "SUCCESFULLY RUNNING WITH: " << beeps_added << 
        " BEEPS" << std::endl;
    }
  }while(good);

  //Output
  if(beeps_added < target){
    std::cout << "FAILED: " <<  beeps_added << " IS LESS THAN TARGET OF " << target << std::endl;
    return 1;
  }else{
    std::cout << "SUCCESS! RAN WITH: " << beeps_added << " BEEPS" << std::endl;
    return 0;
  }
}
