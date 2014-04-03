#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include "BeepHive.h"
#include "Sensor.h"
#include "Serializeable.h"


class LightSensor : public Sensor, public Serializeable
{
  public:
    //create the sensor with a layer as well as an xyz location
    LightSensor(int x, int y, int z, Layer* m);
    //read the layer at the given x, y, z

    using Serializeable::serialize;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version);

  protected:
    int x_off, y_off, z_off;
};
#endif
