#ifndef ENVIRONMENTOBJECT_H
#define ENVIRONMENTOBJECT_H

#include <gui_includes.h>

class EnvironmentObject
{

public:
  EnvironmentObject(int x, int y, int widthIn, int heightIn);
  void updateDrawPosition(QGraphicsScene* newScene);

private:
  int xCoordinate;
  int yCoordinate;
  int width;
  int height;
  QGraphicsRectItem* body;
  QGraphicsScene *scene;


};

#endif // ENVIRONMENTOBJECT_H
