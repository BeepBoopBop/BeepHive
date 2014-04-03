#include "environmentobject.h"

EnvironmentObject::EnvironmentObject(int x, int y, int widthIn, int heightIn)
{
  xCoordinate = x;
  yCoordinate = y;
  width = widthIn;
  height = heightIn;
}


void EnvironmentObject::updateDrawPosition(QGraphicsScene* newScene){
  scene = newScene;
  body = scene->addRect(xCoordinate, yCoordinate, width, height, QColor(0, 0, 0), Qt::NoBrush);
}
