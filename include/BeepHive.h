#ifndef BEEPHIVE_H
#define BEEPHIVE_H 

/*!
 * This file includes most of the basic things needed by most files and provides
 * definitions used throughout BeepHive
 */

#include <iostream>
#include <map>

#include "BeepHiveConfigs.h"

#define NOT_IMPLEMENTED(foo) \
  /*! This function has not yet been implemented. */\
  foo {\
    std::cout << "The function, " << #foo \
    << " has not yet been implemented!" << std::endl; \
  }

#ifdef DEBUG
#define DEBUG_OUT(x) {fprintf(stderr,"FILE: %s LINE: %d MSG: %s\n",__FILE__, __LINE__,x);}
#else
#define DEBUG_OUT(x) ((void)0)
#endif


template<class T>
class Map: public std::map<std::string,T> {};

#endif /* BEEPHIVE_H */
