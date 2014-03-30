#ifndef ROBOT_H
#define ROBOT_H

#include "gui_includes.h"


class Robot
{
public:
    Robot();
    void updateDrawPosition(int x, int y, QGraphicsScene * newScene);
    void updateDrawPosition(QGraphicsScene * newScene);
    void randUpdateDrawPosition(QGraphicsScene * newScene);

    //Accessor Methods
    QGraphicsEllipseItem *getBody();
    void setBody( QGraphicsEllipseItem*);
    QGraphicsScene *getScene();
    void setScene(QGraphicsScene *);

private:
    int xCoordinate;
    int yCoordinate;
    QGraphicsEllipseItem * body;
    QGraphicsScene *scene;

    QBrush greenBrush;
    QPen outlinePen;
};

#endif // ROBOT_H
