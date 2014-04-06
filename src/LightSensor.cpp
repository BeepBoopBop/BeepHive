

//class to sense the variable of specific cells of the light layer

#include "BeepHive.h"
#include "Sensor.h"
#include "Serializeable.h"
#include "LightSensor.h"

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

    //using Serializeable::serialize; 
    template<class Archive>
    void LightSensor::serialize(Archive& ar, const unsigned int version)
    {
        using boost::serialization::make_nvp;
        ar & make_nvp("x_off", x_off);
        ar & make_nvp("y_off", y_off);
        ar & make_nvp("z_off", z_off);
    }

