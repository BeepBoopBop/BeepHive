#ifndef ENV_OBJECT_H
#define ENV_OBJECT_H

#include "BeepHive.h"
#include "Serializeable.h"

/*! 
 * Simple class for rectangle environment object
 * Bypasses factory
 */

class EnvObject : public Serializeable
{

  public:
    EnvObject(double x, double y, double widthIn, double heightIn, bool isSource);
    double getX();
    double getY();
    double getWidth();
    double getHeight();
    double getTemp();
    bool isSource();
    
  private:
    double xCoordinate;
    double yCoordinate;
    double width;
    double height
    double temp;
    bool source;

};

#endif
