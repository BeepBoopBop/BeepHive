#ifndef SENSOR_H
#define SENSOR_H 

#include "BeepHive.h"
#include "Layer.h"

class Sensor 
{
  public:

    Sensor(Layer* m){model = m;}
    //decontructor
    virtual ~Sensor() = 0;

    //get reading from the model that is readible
    virtual float readLayer() = 0;

  
  protected:
    //the layer that the sensor can read from
    Layer* model;
};

#endif /* SENSOR_H */
