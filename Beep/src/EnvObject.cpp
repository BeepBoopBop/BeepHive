#include "EnvObject.h"

EnvObject::EnvObject(double x, double y, double widthIn, double heightIn, bool sourceIn)
  : temp(50)
{
  xCoordinate = x;
  yCoordinate = y;
  width = widthIn;
  height = heightIn;
  source = sourceIn;
}

double EnvObject::getX(){ return xCoordinate; }
double EnvObject::getY(){ return yCoordinate; }
double EnvObject::getWidth(){ return width; }
double EnvObject::getHeight(){ return height; }
double EnvObject::getTemp(){ return temp; }
bool EnvObject::isSource(){ return source; }

void  EnvObject::load(std::string JSON)
{

  ptree tree = StringtoPTree(JSON);

  xCoordinate = tree.get<double>("x");
  yCoordinate = tree.get<double>("y");
  width = tree.get<double>("width");
  height = tree.get<double>("height");
  source = tree.get<bool>("source");
  temp = tree.get<double>("temp");

}
void EnvObject::saveHelper( ptree &tree ){
  
  tree.put("x", xCoordinate);
  tree.put("y", yCoordinate);
  tree.put("width", width);
  tree.put("height", height);
  tree.put("temp", temp);
  tree.put("source", source);
}

std::string EnvObject::type(){
  return("EnvObject");
}
