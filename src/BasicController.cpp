#include "Controller.h"
#include "BasicController.h"
#include "Beep.h"
#include "Manipulator.h"

void BasicController::run(Beep* beep)
{
  Manipulator* omega_velocity=beep->getManipulator("OmegaVelocity");
  std::vector<double> inputs;
  inputs.push_back(0.5);
  inputs.push_back(1);
  omega_velocity->setInputs(inputs);
}
