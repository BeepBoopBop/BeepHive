#ifndef DATA_POINT_H
#define DATA_POINT_H

#include "Layer.h"
#include "Serializable.h"

class DataPoint : public Serializable
{

  public:

    DataPoint(){};
    DataPoint( double xVal, double yVal ){ x = xVal; y = yVal; };

    double getX(){return x;}
    void setX( double newX ){x = newX;}
    double getY(){return y;}
    void setY( double newY ){y = newY;}
    double getValue(){return value;}
    void setValue( double newValue ){value = newValue;}

    std::string save();
    void load(std::string JSON);
    void saveHelper(ptree& tree);
    std::string type();

  private:
    double x, y, value;

};

#endif
