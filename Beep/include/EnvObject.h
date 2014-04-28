#ifndef ENV_OBJECT_H
#define ENV_OBJECT_H

#include "BeepHive.h"
#include "Serializable.h"

/*! 
 * Simple class for rectangle environment object
 * Bypasses factory
 */

class EnvObject : public Serializable
{

  public:
    EnvObject(double x, double y, double widthIn, double heightIn, bool isSource);
    double getX();
    double getY();
    double getWidth();
    double getHeight();
    double getTemp();
    bool isSource();
    void load(std::string JSON);
    void saveHelper( ptree &tree );
    std::string type();
    
  private:
    double xCoordinate;
    double yCoordinate;
    double width;
    double height;
    double temp;
    bool source;

};

#endif
