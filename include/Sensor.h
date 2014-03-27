#ifndef SENSOR_H
#define SENSOR_H 

#include "BeepHive.h"
#include "Model.h"

class Sensor 
{
  public:

    Sensor(Model* m){model = m;}
    //decontructor
    virtual ~Sensor() = 0;

    //get reading from the model that is readible
    virtual float readModel() = 0;

  
  protected:
    //the layer that the sensor can read from
    Model* model;
};

#endif /* SENSOR_H */
