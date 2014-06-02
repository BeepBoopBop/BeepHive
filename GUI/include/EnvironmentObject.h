#ifndef ENVIRONMENTOBJECT_H
#define ENVIRONMENTOBJECT_H

#include "GuiIncludes.h"

class EnvironmentObject
{

  public:
    EnvironmentObject(int x, int y, int widthIn, int heightIn, bool source);
    void updateDrawPosition(QGraphicsScene* newScene);

  private:
    int xCoordinate;
    int yCoordinate;
    int width;
    int height;
    bool heatSource;
    QGraphicsRectItem* body;
    QGraphicsScene *scene;


};

#endif // ENVIRONMENTOBJECT_H
