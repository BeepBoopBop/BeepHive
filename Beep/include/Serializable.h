#ifndef SERIALIZEABLE_H
#define SERIALIZEABLE_H


#include "BeepHive.h"
#include <sstream>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

/*!
 * Serializable is a class used as an interface for objects that should 
 * be serializeable
 *
 * Inheriting classes should define the serialization function
 */
class Serializable{

  public:
    std::string name;

    //saves the object to the returned string, user responsible for sending it to file or over mpi
    std::string save();
    virtual void saveHelper(ptree& tree) = 0;
    virtual std::string type() = 0;
    
    static std::string PTreeToString(ptree tree);
    static ptree StringtoPTree(std::string JSON);

    //! should return the class and user is responsible for casting to the subclass
    virtual void load(std::string JSON) =0;

};

#endif /* SERIALIZEABLE_H */
