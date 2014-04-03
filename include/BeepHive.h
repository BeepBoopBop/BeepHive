#ifndef BEEPHIVE_H
#define BEEPHIVE_H 

/*!
 * This file includes most of the basic things needed by most files and provides
 * definitions used throughout BeepHive
 */

#include <iostream>
#include <map>
#include <stdio.h>
#include <boost/mpi.hpp>
#include <assert.h>

#define NOT_IMPLEMENTED(foo) \
  /*! This function has not yet been implemented. */\
  foo {\
    std::cout << "The function, " << #foo \
    << " has not yet been implemented!" << std::endl; \
  }

#ifndef NDEBUG
#define DEBUG(x) {fprintf(stderr,"FILE: %s LINE: %d MSG: %s\n",__FILE__, __LINE__,x);}
#else
#define DEBUG(x) ((void)0)
#endif


template<class T>
class Map: public std::map<std::string,T> {};

#endif /* BEEPHIVE_H */
