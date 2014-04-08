#include "math.h"

#include "Controller.h"
#include "FlockingController.h"
#include "Beep.h"
#include "Manipulator.h"

void FlockingController::run(Beep* beep)
{
  DEBUG("Running basic controller");
  Manipulator* omega_velocity=beep->getManipulator("OmegaVelocity");
  std::vector<double> inputs;

  double average_x=beep->getSensor("AverageX")->getReading();
  double average_y=beep->getSensor("AverageY")->getReading();
  double x=beep->getState("x");
  double y=beep->getState("y");
  double theta=beep->getState("theta");
  double delta_x=average_x-x;
  double delta_y=average_y-y;
  double linear=delta_x*cos(theta)+delta_y*sin(theta);
  inputs.push_back(0.1);
  inputs.push_back(linear/20);
  omega_velocity->setInputs(inputs);
}

FlockingControllerFactory::FlockingControllerFactory() {}

/*
Factory<Controller>* FlockingControllerFactory::getInstance()
{
  static FlockingControllerFactory instance;
  return &instance;
}
*/

std::string FlockingControllerFactory::type()
{
  return "FlockingController";
}

Controller* FlockingControllerFactory::create()
{
  return new FlockingController();
}

Controller* FlockingControllerFactory::create(std::vector<std::string> params)
{
  return new FlockingController();
}

FlockingControllerFactoryProxy::FlockingControllerFactoryProxy()
{
  static FlockingControllerFactory instance;
  Factories<Controller>::getInstance().addFactory(instance);
}
FlockingControllerFactoryProxy flocking_controller_factory_proxy;
