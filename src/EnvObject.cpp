#include "EnvObject.h"

EnvObject::EnvObject(double x, double y, double widthIn, double heightIn, bool sourceIn)
{
  xCoordinate = x;
  yCoordinate = y;
  width = widthIn;
  height = heightIn;
  source = sourceIn;
}

double EnvObject::getX(){ return xCoordinate; }
double EnvObject::getY(){ return yCoordinate; }
double EnvObject::getWidth(){ return width; }
double EnvObject::getHeight(){ return height; }
double EnvObject::getTemp(){ return temp; }
bool EnvObject::isSource(){ return source; }
