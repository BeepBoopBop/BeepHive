

//class to sense the variable of specific cells of the light layer

#include "BeepHive.h"
#include "Sensor.h"
#include "Serializeable.h"
#include "LightSensor.h"

    //create the sensor with a layer as well as an xyz location
    LightSensor::LightSensor(int x, int y, int z, Layer* m) : Sensor(m)
    {
      x_loc = x;
      y_loc = y;
      z_loc = z;
    }

    //read the layer at the given x, y, z
    float readEnvironment()
    {
      //return environment->getCellValue(x_loc, y_loc, z_loc);
    }

    //using Serializeable::serialize; 
    template<class Archive>
    void LightSensor::serialize(Archive& ar, const unsigned int version){int i =0;}

