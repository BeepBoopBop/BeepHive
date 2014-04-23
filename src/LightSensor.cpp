

//class to sense the variable of specific cells of the light layer

#include "BeepHive.h"
#include "Sensor.h"
#include "LightSensor.h"
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

    //create the sensor with a layer as well as an xyz location
    LightSensor::LightSensor(int x, int y, int z, Layer* m) : Sensor(m)
    {
      x_off = x;
      y_off = y;
      z_off = z;
    }
    //read the layer at the given x, y, z
    void Sensor::readLayer(const World* world)
    {
      //return environment->getCellValue(x_loc, y_loc, z_loc);
    }
    std::string  LightSensor::save(){return "not implemented";}
    Serializeable*  LightSensor::load(std::string JSON){return NULL;}
