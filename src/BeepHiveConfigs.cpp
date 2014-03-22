#include <iostream>

#include "BeepHive.h"
#include "BeepHiveConfigs.h"

BeepHiveConfigs& BeepHiveConfigs::getInstance()
{
  static BeepHiveConfigs instance;
  return instance;
}

void BeepHiveConfigs::parseArgs(const int argc, char** argv)
{
  NOT_IMPLEMENTED(BeepHiveConfigs::parseArgs);
}

BeepHiveConfigs::BeepHiveConfigs() {}
