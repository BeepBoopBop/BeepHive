#ifndef SENSOR_H
#define SENSOR_H 


class Sensor 
{
  public:

    Sensor(Layer* e){environment = e;}
    //decontructor
    virtual ~Sensor() = 0;

    //get reading from the environment that is readible
    virtual float readEnvironment() = 0;

  
  protected:
    //the layer that the sensor can read from
    Layer* environment;
}

#endif /* SENSOR_H */
