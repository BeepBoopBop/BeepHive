#ifndef SERIALIZEABLE_H
#define SERIALIZEABLE_H


#include <fstream>
#include <string>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "BeepHive.h"



//class used as an interface for objects that should be serializeable
//the class should extend Serializeable and define the serialization function
class Serializeable{

  public:
   std::string name;

    friend class boost::serialization::access;
    template<class archive>

    //used by save and load in an ambidextrous manner to send member variables to and from xml
    virtual void serialize(archive& ar, const unsigned int version) = 0;


    void save(const Serializeable& sw, const std::string& file_name);

    //should return the class and user is responsible for casting to the subclass
    Serializeable load(const std::string& file_name);

};

#endif /* SERIALIZEABLE_H */
