//class to sense the variable of specific cells of the light layer

#include <boost/property_tree/ptree.hpp>

#include "Beep.h"
#include "BeepHive.h"
#include "Layer.h"
#include "LightSensor.h"
#include "Sensor.h"

using boost::property_tree::ptree;

//create the sensor with a layer as well as an xyz location
LightSensor::LightSensor(int x, int y, Layer* m, Beep* b) : Sensor(m, b)
{
  x_off = x;
  y_off = y;
}

LightSensor::LightSensor(int x, int y)
{
  x_off = x;
  y_off = y;
}

//read the layer at the given x, y, z
void LightSensor::readLayer(const World* world)
{
  reading = layer->getValue(beep->getState("x")+x_off,beep->getState("y")+ y_off);
}

#if 0
std::string  LightSensor::save()
{
  
  ptree tree;
  tree.put("x_off", x_off);
  tree.put("y_off", y_off);
  return PTreeToString(tree);

}
void  LightSensor::load(std::string JSON)
{
  ptree tree = StringToPTree(JSON);
  x_off = tree.get<int> ("x_off");
  y_off = tree.get<int> ("y_off");
}
#endif
