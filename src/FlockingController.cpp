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
  inputs.push_back(linear/10);
  omega_velocity->setInputs(inputs);
}
