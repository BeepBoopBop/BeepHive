#ifndef SENSOR_H
#define SENSOR_H 

#include "BeepHive.h"
#include "Layer.h"
#include "World.h"


class World;

class Sensor
{
  public:

    Sensor(Layer* m){layer = m;}


    //get reading from the layer that is readible
    virtual float readLayer(World* world) = 0;
    float getReading() {return reading;}


  
  protected:
    //the layer that the sensor can read from
    Layer* layer;
    float reading;
};

#endif /* SENSOR_H */
