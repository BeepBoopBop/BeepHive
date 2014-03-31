#include "Serializeable.h"

template<class archive>

//used by save and load in an ambidextrous manner to send member variables to and from xml
virtual void Serializeable::serialize(archive& ar, const unsigned int version) = 0;

void Serializeable::save(const Serializeable& sw, const std::string& file_name)
{
  typedef base::file_stream bafst;
  bafst::file_stream ofs(file_name, bafst::trunc | bafst::out);
  boost::archive::xml_oarchive xml(ofs);
  xml << boost::serialization::make_nvp(name, sw);
}

Serializeable Serializeable::load(const std::string& file_name)
{
  typedef base::file_stream bafst;
  bafst::file_stream ifs(file_name, bafst::binary | bafst::in);
  boost::archive::xml_oarchive xml(ifs);
  xml >> boost::serialization::make_nvp(name, sw);
}
