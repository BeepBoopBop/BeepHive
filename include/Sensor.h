#ifndef SENSOR_H
#define SENSOR_H 

#include "BeepHive.h"
#include "Layer.h"
#include "World.h"


class World;

/*!
 * Sensors are responsible for reading and calculating values from the World and
 * returning them to the controller.
 *
 * All sensors are read before controllers are called. Sensors cannot modify
 * the World or any layers.
 */
class Sensor
{
  public:

    Sensor(Layer* m){layer = m;}


    //! Gets and stores reading from the layer/World
    virtual void readLayer(const World* world) = 0;
    //! Returns the last stored reading
    float getReading() {return reading;}


  
  protected:
    //the layer that the sensor can read from
    Layer* layer;
    float reading;
};

#endif /* SENSOR_H */
