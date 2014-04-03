#ifndef AVERAGESENSOR_H
#define AVERAGESENSOR_H 

#include "BeepHive.h"
#include "World.h"
#include "Sensor.h"


class AverageSensor : public Sensor
{
  public:
    //create the sensor with a layer as well as an xyz location
    AverageSensor(Layer* beep_layer,std::string state);
    //read the layer at the given x, y, z
    float readLayer(World* world);

  protected:
    std::string state;
};
#endif /* AVERAGESENSOR_H */
