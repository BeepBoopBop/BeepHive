#ifndef SERIALIZEABLE_H
#define SERIALIZEABLE_H


#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/nvp.hpp>

#include "BeepHive.h"


/*!
 * Serializable is a class used as an interface for objects that should 
 * be serializeable
 *
 * Inheriting classes should define the serialization function
 */
class Serializeable{

  public:
   std::string name;

    friend class boost::serialization::access;

    //! used by save and load in an two-way manner to send member variariables via xml
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version);


    void save(const Serializeable& sw, const std::string& file_name);

    //! should return the class and user is responsible for casting to the subclass
    Serializeable* load(const std::string& file_name);

};

#endif /* SERIALIZEABLE_H */
