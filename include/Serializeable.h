#ifndef SERIALIZEABLE_H
#define SERIALIZEABLE_H


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

    //saves the object to the returned string, user responsible for sending it to file or over mpi
    virtual std::string save() =0;

    //! should return the class and user is responsible for casting to the subclass
    virtual Serializeable* load(std::string JSON) =0;

};

#endif /* SERIALIZEABLE_H */
