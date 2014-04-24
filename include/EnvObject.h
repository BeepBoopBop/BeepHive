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
    EnvObject(int x, int y, int widthIn, int heightIn, bool isSource);

  private:
    int xCoordinate;
    int yCoordinate;
    int width;
    int height;
    bool source;

};

#endif
