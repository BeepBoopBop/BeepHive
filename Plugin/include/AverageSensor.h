#ifndef AVERAGESENSOR_H
#define AVERAGESENSOR_H 

#include "BeepHive.h"
#include "World.h"
#include "Sensor.h"


/*!
 * The average sensor is a sensor that can be configured to take the average of
 * some value across all Beeps
 *
 * Currently all Beeps are used but in the future a maximum radius will be given
 */
class AverageSensor : public Sensor
{
  public:
    //create the sensor with a layer as well as an xyz location
    AverageSensor(Layer* beep_layer, Beep* beep, std::string state);
    //read the layer at the given x, y, z
    void readLayer(const World* world);
    //std::string  save();
    //void load(std::string JSON);
  protected:
    std::string state;
};

DEFINE_FACTORY(AverageSensor, Sensor);

#endif /* AVERAGESENSOR_H */
