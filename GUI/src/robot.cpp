#include "robot.h"

//used to generate random starting positions for the robots
int randInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

//Constructor
Robot::Robot()
{
  xCoordinate = randInt(0,400);
  yCoordinate = randInt(0,400);
  QBrush greenBrush(Qt::green);
  QPen outlinePen(Qt::black);
  outlinePen.setWidth(2);
}

void Robot::updateDrawPosition(int x, int y, QGraphicsScene *newScene){
    xCoordinate = x;
    yCoordinate = y;
    scene = newScene;
    body = scene->addEllipse(xCoordinate, yCoordinate, 10, 10, outlinePen, greenBrush);
}

void Robot::updateDrawPosition(QGraphicsScene * newScene){
    scene = newScene;
    body = scene->addEllipse(xCoordinate, yCoordinate, 10, 10, outlinePen, greenBrush);
}

//moves robot in a random direction, used for demonstration purposes
void Robot::randUpdateDrawPosition(QGraphicsScene *newScene){
    xCoordinate += randInt(-1, 1);
    yCoordinate += randInt(-1,1);
    scene = newScene;
    body = scene->addEllipse(xCoordinate, yCoordinate, 10, 10, outlinePen, greenBrush);
}


//Accessor Methods

QGraphicsEllipseItem *Robot::getBody(){
    return body;
}

void Robot::setBody(QGraphicsEllipseItem * abody){
    body = abody;
}

QGraphicsScene *Robot::getScene(){
    return scene;
}

void Robot::setScene(QGraphicsScene * ascene){
    scene = ascene;
}
