#ifndef HEATSENSOR_H
#define HEATSENSOR_H

#include "BeepHive.h"
#include "Sensor.h"



class HeatSensor : public Sensor
{
  public:
    //create the sensor with a layer as well as an xy location
    HeatSensor(int x, int y, Layer* m, Beep* b);
    HeatSensor(int x, int y);
    HeatSensor(){};
    //read the layer at the given x, y
    void readLayer(const World* world);
    
    //std::string  save();
    //void load(std::string JSON);

  protected:
    int x_off, y_off;
};
#endif
