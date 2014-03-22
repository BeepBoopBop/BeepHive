#include <iostream>

#include "BeepHive.h"
#include "BeepHiveConfigs.h"

/*!
 * Provides access to configs singleton
 */
BeepHiveConfigs& BeepHiveConfigs::getInstance()
{
  static BeepHiveConfigs instance;
  return instance;
}

NOT_IMPLEMENTED(void BeepHiveConfigs::parseArgs(const int argc, char** argv))

BeepHiveConfigs::BeepHiveConfigs() {}
