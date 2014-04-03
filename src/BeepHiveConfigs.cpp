#include <iostream>

#include "BeepHive.h"
#include "BeepHiveConfigs.h"

BeepHiveConfigs::BeepHiveConfigs() : time_limit(-1){}

/*!
 * Provides access to configs singleton
 */
BeepHiveConfigs& BeepHiveConfigs::getInstance()
{
  static BeepHiveConfigs instance;
  return instance;
}

NOT_IMPLEMENTED(void BeepHiveConfigs::parseArgs(const int argc, char** argv))



void BeepHiveConfigs::setTimeLimit(double time_limit)
{
  this->time_limit=time_limit;
}



double BeepHiveConfigs::getTimeLimit()
{
  return time_limit;
}
