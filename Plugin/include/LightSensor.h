#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include "BeepHive.h"
#include "Sensor.h"



class LightSensor : public Sensor
{
  public:
    //create the sensor with a layer as well as an xyz location
    LightSensor(int x, int y, int z, Layer* m);
    LightSensor(int x, int y, int z);
    LightSensor(){};
    //read the layer at the given x, y, z
    void readLayer(const World* world);
    
    std::string  save();
    void load(std::string JSON);

  protected:
    int x_off, y_off, z_off;
};
#endif
