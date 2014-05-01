//class to sense the variable of specific cells of the light layer

#include "BeepHive.h"
#include "Sensor.h"
#include "HeatSensor.h"
#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;

    //create the sensor with a layer as well as an xyz location
    HeatSensor::HeatSensor(int x, int y, Layer* m, Beep* b) : Sensor(m,b)
    {
      x_off = x;
      y_off = y;
    }

    HeatSensor::HeatSensor(int x, int y)
    {
      x_off = x;
      y_off = y;
    }
    //read the layer at the given x, y, z
    void HeatSensor::readLayer(const World* world)
    {
      reading = layer->getValue(x_off, y_off);
    }


#if 0
    std::string  HeatSensor::save()
    {
      
      ptree tree;
      tree.put("x_off", x_off);
      tree.put("y_off", y_off);
      return PTreeToString(tree);
    
    }
    void  HeatSensor::load(std::string JSON)
    {
      ptree tree = StringToPTree(JSON);
      x_off = tree.get<int> ("x_off");
      y_off = tree.get<int> ("y_off");
    }
#endif
