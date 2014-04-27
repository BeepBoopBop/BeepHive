

//class to sense the variable of specific cells of the light layer

#include "BeepHive.h"
#include "Sensor.h"
#include "LightSensor.h"
#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;

    //create the sensor with a layer as well as an xyz location
    LightSensor::LightSensor(int x, int y, int z, Layer* m) : Sensor(m)
    {
      x_off = x;
      y_off = y;
      z_off = z;
    }

    LightSensor::LightSensor(int x, int y, int z)
    {
      x_off = x;
      y_off = y;
      z_off = z;
    }
    //read the layer at the given x, y, z
    void LightSensor::readLayer(const World* world)
    {
      //return environment->getCellValue(x_loc, y_loc, z_loc);
    }

    std::string  LightSensor::save()
    {
      
      ptree tree;
      tree.put("x_off", x_off);
      tree.put("y_off", y_off);
      tree.put("z_off", z_off);
      return PTreeToString(tree);
    
    }
    void  LightSensor::load(std::string JSON)
    {
      ptree tree = StringtoPTree(JSON);
      x_off = tree.get<int> ("x_off");
      y_off = tree.get<int> ("y_off");
      z_off = tree.get<int> ("z_off");
      std::cout << "Loaded with values " << x_off <<" " << y_off <<" " << z_off <<"\n";
    }








