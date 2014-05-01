#ifndef SENSOR_H
#define SENSOR_H 

#include "BeepHive.h"
#include "Layer.h"
#include "World.h"
#include "Serializable.h"


class Beep;

class World;

/*!
 * Sensors are responsible for reading and calculating values from the World and
 * returning them to the controller.
 *
 * All sensors are read before controllers are called. Sensors cannot modify
 * the World or any layers.
 */
class Sensor //: public Serializable
{
  public:

    Sensor(Layer* m, Beep* b){layer = m; beep = b;}
    Sensor(){};


    //! Gets and stores reading from the layer/World
    virtual void readLayer(const World* world) = 0;
    //! Returns the last stored reading
    double getReading() {return reading;}


  
  protected:
    //the layer that the sensor can read from
    Layer* layer;
    Beep* beep;
    double reading;
};

#endif /* SENSOR_H */
