#include "BeepHive.h"
#include "DataPoint.h"
#include <boost/property_tree/ptree.hpp>

using boost::property_tree::ptree;

std::string DataPoint::save(){

  ptree tree;
  tree.put("x", x);
  tree.put("y", y);
  tree.put("value", value);

  saveHelper(tree);
  return PTreeToString(tree);

}

void  DataPoint::load(std::string JSON)
{

  ptree tree = StringtoPTree(JSON);
  x = tree.get<double>("x");
  y = tree.get<double>("y");
  value = tree.get<double>("value");

}

void DataPoint::saveHelper( ptree &tree ){

}

std::string type(){
  return("DataPoint");
}
