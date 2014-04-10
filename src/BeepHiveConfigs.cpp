#include <iostream>
#include <getopt.h>
#include <stdlib.h>

#include "BeepHive.h"
#include "BeepHiveConfigs.h"

BeepHiveConfigs::BeepHiveConfigs() : time_limit(-1), gui_enabled(true){}

/*!
 * Provides access to configs singleton
 */
BeepHiveConfigs& BeepHiveConfigs::getInstance()
{
  static BeepHiveConfigs instance;
  return instance;
}

void BeepHiveConfigs::parseArgs(const int argc, char** argv)
{
  while(1){
    //options struct for getopt
    static struct option long_options[]=
    {
      {"nogui", no_argument, 0, 'n'},
      {0, 0, 0, 0}
    };
    int option_index=0;

    int val=getopt_long(argc, argv, "n", long_options, &option_index);
    if(val == -1){
      break;
    }

    switch(val){
      case 'n':
        this->gui_enabled=false;
        break;
      default:
        //help();
        exit(0);
        break;
    }
  }
}



void BeepHiveConfigs::setTimeLimit(double time_limit)
{
  this->time_limit=time_limit;
}



double BeepHiveConfigs::getTimeLimit()
{
  return time_limit;
}

bool BeepHiveConfigs::guiEnabled()
{
#ifdef GUI
  return gui_enabled;
#else
  return false;
#endif
};
