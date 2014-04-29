#include "BeepHive.h"
#include "DataPoint.h"
#include <boost/property_tree/ptree.hpp>

using boost::property_tree::ptree;


void  DataPoint::load(std::string JSON)
{
  ptree tree = StringToPTree(JSON);
  x = tree.get<double>("x");
  y = tree.get<double>("y");
  value = tree.get<double>("value");
}

void DataPoint::saveHelper( ptree &tree ){
  tree.put("x", x);
  tree.put("y", y);
  tree.put("value", value);
}

std::string DataPoint::type(){
  return("DataPoint");
}
