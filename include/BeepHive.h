#ifndef BEEPHIVE_H_H
#define BEEPHIVE_H_H 

#include <iostream>

#include "BeepHiveConfigs.h"

#define NOT_IMPLEMENTED(foo) \
  /*! This function has not yet been implemented. */\
  foo {\
    std::cout << "The function, " << #foo \
    << " has not yet been implemented!" << std::endl; \
  }

#endif /* BEEPHIVE_H_H */
