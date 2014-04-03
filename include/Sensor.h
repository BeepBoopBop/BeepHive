#ifndef SENSOR_H
#define SENSOR_H 

#include "BeepHive.h"
#include "Layer.h"


class Sensor
{
  public:

    Sensor(Layer* m){layer = m;}


    //get reading from the layer that is readible
    virtual float readLayer() = 0;


  
  protected:
    //the layer that the sensor can read from
    Layer* layer;
};

#endif /* SENSOR_H */
