#include "Model.h"

Model::Model()
{
  time = 0; 
}



double Model::getTime()
{ 
  return time; 
}



void Model::setTime(double new_time)
{ 
  time = new_time;
}
