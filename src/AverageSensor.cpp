

//class to sense the variable of specific cells of the light layer

#include "BeepHive.h"
#include "Sensor.h"
#include "Serializeable.h"
#include "AverageSensor.h"
#include "World.h"

    //create the sensor with a layer as well as an xyz location
    AverageSensor::AverageSensor(Layer* beep_layer, std::string state) : Sensor(beep_layer)
    {
      this->state=state;
    }

    //read the layer at the given x, y, z
    void AverageSensor::readLayer(const World* world)
    {
      //return environment->getCellValue(x_loc, y_loc, z_loc);
      World::BeepIterator it = world->beepBegin();
      float total=0;
      int count=0;
      for(it=world->beepBegin(); it!=world->beepEnd(); ++it,++count){
        total+=(*it)->getState(this->state);
      }
      total/=count;
      reading=total;
    }

