#include "Robot.h"

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
  red = 0;
  blue = 0;
  green = 0;
}

Robot::Robot(int x, int y){
  xCoordinate = x;
  yCoordinate = y;
  red = 0;
  blue = 0;
  green = 0;
}

void Robot::setPosition(int x, int y)
{
  xCoordinate = x;
  yCoordinate = y;
}

void Robot::updateDrawPosition(int x, int y, QGraphicsScene *newScene){
  xCoordinate = x;
  yCoordinate = y;
  scene = newScene;
  body = scene->addEllipse(xCoordinate, yCoordinate, 10, 10, QColor(red, green, blue), Qt::NoBrush);
}

void Robot::updateDrawPosition(QGraphicsScene * newScene){
  scene = newScene;
  body = scene->addEllipse(xCoordinate, yCoordinate, 10, 10, QColor(red, green, blue), Qt::NoBrush);
}

//moves robot in a random direction, used for demonstration purposes
void Robot::randUpdateDrawPosition(QGraphicsScene *newScene){
  xCoordinate += randInt(-1, 1);
  yCoordinate += randInt(-1,1);
  scene = newScene;
  body = scene->addEllipse(xCoordinate, yCoordinate, 10, 10, QColor(red, green, blue), Qt::NoBrush);
}

std::string Robot::obtainUpdateString(){
  std::stringstream ss;//create a stringstream
  ss << xCoordinate << " " << yCoordinate;//add number to the stream
  return ss.str();//return a string with the contents of the stream
}

//Return manhatten distance from the robot to a certain point
double Robot::distanceFromPoint(int x, int y){
  return abs(xCoordinate - x) + abs(yCoordinate - y);
}

//Color setting methods
void Robot::resetColor(){
  red = 0;
  blue = 0;
  green = 0;
}

void Robot::highlightGreen(){
  red = 0;
  blue = 0;
  green = 255;
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
