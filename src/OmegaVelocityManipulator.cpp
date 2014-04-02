#include <math.h>

#include "BeepHive.h"
#include "OmegaVelocityManipulator.h"

/*!
 * This method updates the state based on a radial and linear velocity
 *
 * The inputs to the state vector are:
 * radial velocity, linear velocity
 * omega is in the counterclockwise direction
 * velocity is in the local X direction
 */
void OmegaVelocityManipulator::updateState()
{
  double delta_t = layer->timeSinceLastUpdate();
  double omega = inputs[0];
  double velocity = inputs[1];
  double theta = beep->getState("theta");
  double x = beep->getState("x");
  double y = beep->getState("y");


  //Calculate change in position in the local frame
  double delta_theta = theta * delta_t;
  double radius = velocity / omega;
  // alpha is the angle of the vector to the new position in the local reference
  // frame
  double alpha = delta_theta / 2;
  // r is the lenght of the vector to the new position
  double r = 2 * radius * sin(delta_theta / 2);

  double local_x = r * cos(alpha);
  double local_y = r * sin(alpha);

  //Transform to global frame
  double delta_x = (cos(theta) * local_x - sin(theta) * local_y);
  double delta_y = (sin(theta) * local_x + cos(theta) * local_y);
  beep->setState("x",x+delta_x);
  beep->setState("y",y+delta_y);
  beep->setState("theta",theta+delta_theta);
}
