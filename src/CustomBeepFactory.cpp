#include <string>

#include "CustomBeepFactory.h"



CustomBeepFactory::CustomBeepFactory(std::string type_name, std::string base_factory,
                                     FactoryParams params)
  : CustomFactory<Beep>(type_name, base_factory, params) {}



Beep* CustomBeepFactory::create()
{
  Beep* beep=this->factory.factory->create(this->factory.params);
  Sensor* sensor;
  Manipulator* manipulator;
  Controller* controller;

  {
    Map<FactoryAndParams<Sensor> >::iterator it;

    for(it=sensors.begin(); it!=sensors.end(); ++it){
      sensor=it->second.factory->create(it->second.params);
      beep->addSensor(it->first, sensor);
    }
  }

  {
    Map<FactoryAndParams<Manipulator> >::iterator it;
    for(it=manipulators.begin(); it!=manipulators.end(); ++it){
      manipulator=it->second.factory->create(it->second.params);
      beep->addManipulator(it->first, manipulator);
    }
  }

  controller = this->controller.factory->create(this->controller.params);
  beep->setController(controller);


  return beep;
}



Beep* CustomBeepFactory::create(FactoryParams& params)
{
  return this->create();
}



void CustomBeepFactory::addSensor(std::string instance_name, std::string base_type,
    FactoryParams params)
{
  Factories<Sensor>& factories=Factories<Sensor>::getInstance();
  sensors[instance_name]=FactoryAndParams<Sensor>(factories[base_type], params);
}



void CustomBeepFactory::addManipulator(std::string instance_name, std::string base_type,
  FactoryParams params)
{
  Factories<Manipulator>& factories=Factories<Manipulator>::getInstance();
  manipulators[instance_name]=
    FactoryAndParams<Manipulator>(factories[base_type], params);
}



void CustomBeepFactory::setController(std::string base_type,
  FactoryParams params)
{
  Factories<Controller>& factories=Factories<Controller>::getInstance();
  controller=FactoryAndParams<Controller>(factories[base_type], params);
}
