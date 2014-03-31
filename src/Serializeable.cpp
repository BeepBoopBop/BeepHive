#include "Serializeable.h"

//class used as an interface for objects that should be serializeable
//the class should extend Serializeable and define the serialization function

  public std::string name;

  friend class boost::serialization::access;
  template<class archive>

  //used by save and load in an ambidextrous manner to send member variables to and from xml
  virtual void Serializeable::serialize(archive& ar, const unsigned int version) = 0;

  void Serializeable::save(const Serializeable& sw, const string& file_name)
  {
    typedef base::file_stream bafst;
    bafst::file_stream ofs(file_name, bafst::trunc | bafst::out);
    boost::archive::xml_oarchive xml(ofs);
    xml << boost::serialization::make_nvp(name, sw);
  }

  Serializeable Serializeable::load(const string& file_name)
  {
    typedef base::file_stream bafst;
    bafst::file_stream ifs(file_name, bafst::binary | bafst::in);
    boost::archive::xml_oarchive xml(ifs);
    xml >> boost::serialization::make_nvp(name, sw);
  }

}
