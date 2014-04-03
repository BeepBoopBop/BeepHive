#ifndef ROBOT_H
#define ROBOT_H

#include "gui_includes.h"


class Robot
{
public:
    Robot();
    Robot(int x, int y);

    //***********************************************************************
    //self contained updates (for demoing GUI)
    void updateDrawPosition(int x, int y, QGraphicsScene * newScene);
    void updateDrawPosition(QGraphicsScene * newScene);
    void randUpdateDrawPosition(QGraphicsScene * newScene);

    std::string obtainUpdateString();

    //***********************************************************************
    //MPI based update functions
    void mpiUpdateDrawPosition(std::string);

    //Obtain text update info
    std::string obtainMPISummaryString();

    //Accessor Methods
    QGraphicsEllipseItem *getBody();
    void setBody( QGraphicsEllipseItem*);
    QGraphicsScene *getScene();
    void setScene(QGraphicsScene *);
    double distanceFromPoint(int x, int y);
    void resetColor();
    void highlightGreen();

private:
    int xCoordinate;
    int yCoordinate;
    QGraphicsEllipseItem * body;
    QGraphicsScene *scene;

    //used to update debug window
    std::string rawUpdateString;


    //used to set the color of the agent
    int red;
    int green;
    int blue;
};

#endif // ROBOT_H
