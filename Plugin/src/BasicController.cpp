#include "BasicController.h"
#include "Beep.h"
#include "Controller.h"
#include "Manipulator.h"

void BasicController::run(Beep* beep)
{
  Manipulator* omega_velocity=beep->getManipulator("OmegaVelocityManipulator");
  std::vector<double> inputs;
  inputs.push_back(0.03); //radial velocity
  inputs.push_back(4);  //linear velocity
  omega_velocity->setInputs(inputs);
}

Controller* BasicControllerFactory::create()
{
  return new BasicController();
}

Controller* BasicControllerFactory::create(FactoryParams& params)
{
  return new BasicController();
}

ADD_TO_FACTORIES(BasicController, Controller);
