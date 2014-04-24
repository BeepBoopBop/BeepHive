#include "EnvObject.h"

EnvObject::EnvObject(int x, int y, int widthIn, int heightIn, bool isSource)
{
  xCoordinate = x;
  yCoordinate = y;
  width = widthIn;
  height = heightIn;
  source = isSource;
}
