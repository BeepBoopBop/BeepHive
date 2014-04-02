#include "Serializeable.h"
#include <fstream>
#include <iostream>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/nvp.hpp>


//overload this method on each subclass to list members
template<class Archive>
void Serializeable::serialize(Archive& ar, const unsigned int version){};

void Serializeable::save(const Serializeable& sw, const std::string& file_name)
{
    std::ofstream ofs;
    ofs.open(file_name.c_str(), std::ios_base::out);  
    boost::archive::xml_oarchive xml(ofs);
    xml << boost::serialization::make_nvp("Plugin", sw);
}

Serializeable* Serializeable::load(const std::string& file_name)
{
    Serializeable sw;
    std::ifstream ifs;
    ifs.open(file_name.c_str(), std::ios_base::in);
    boost::archive::xml_iarchive xml(ifs, 1);
    xml >> boost::serialization::make_nvp("Plugin", sw);
}
