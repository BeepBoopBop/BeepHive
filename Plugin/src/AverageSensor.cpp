#include <boost/property_tree/ptree.hpp>

#include "AverageSensor.h"
#include "Beep.h"
#include "BeepHive.h"
#include "Factory.h"
#include "Sensor.h"
#include "World.h"

using boost::property_tree::ptree;

//create the sensor with a layer as well as an xyz location
AverageSensor::AverageSensor(Layer* beep_layer, Beep* beep, std::string state) : Sensor(beep_layer, beep)
{
  this->state = state;
}

//read the layer at the given x, y, z
void AverageSensor::readLayer(const World* world)
{
  //return environment->getCellValue(x_loc, y_loc, z_loc);
  World::BeepIterator it = world->beepBegin();
  double total = 0;
  int count = 0;
  for(it=world->beepBegin(); it!=world->beepEnd(); ++it,++count){
    total += (*it)->getState(this->state);
  }
  total/=count;
  reading=total;
}

//std::string  AverageSensor::save(){return "not implemented";}
//void  AverageSensor::load(std::string JSON){}

Sensor* AverageSensorFactory::create()
{
  return new AverageSensor(NULL, NULL, "");
}

Sensor* AverageSensorFactory::create(FactoryParams& params)
{
  assert(params.size()>0);
  return new AverageSensor(NULL, NULL,params[0]);
}

ADD_TO_FACTORIES(AverageSensor,Sensor);
