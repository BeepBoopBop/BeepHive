#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include "Sensor.h"

class LightSensor : public Sensor
{
  public:
    //create the sensor with a layer as well as an xyz location
    LightSensor(int x, int y, Layer* m, Beep* b);
    LightSensor(int x, int y);
    LightSensor(){};
    //read the layer at the given x, y, z
    void readLayer(const World* world);
    
    //std::string  save();
    //void load(std::string JSON);

  protected:
    int x_off, y_off;
};

#endif
