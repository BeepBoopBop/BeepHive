

//class to sense the variable of specific cells of the light layer

#include "Sensor.h"

class LightSensor : public Sensor
{
  public:
    //create the sensor with a layer as well as an xyz location
    LightSensor(int x, int y, int z, Layer* e) :: Sensor(e)
    {
      x_loc = x;
      y_loc = y;
      z_loc = z;
    }
    //read the layer at the given x, y, z
    float readEnvironment()
    {
      return environment->getCellValue(x_loc, y_loc, z_loc);
    }


  protected:
    int x_loc, y_loc, z_loc;
  

}
