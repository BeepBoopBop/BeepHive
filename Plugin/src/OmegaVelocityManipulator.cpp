#include <boost/property_tree/ptree.hpp>
#include <math.h>

#include "Beep.h"
#include "BeepHive.h"
#include "Layer.h"
#include "OmegaVelocityManipulator.h"
#include "World.h"

OmegaVelocityManipulator::OmegaVelocityManipulator() {}

/*!
 * This method updates the state based on a radial and linear velocity
 *
 * The inputs to the state vector are:
 * radial velocity, linear velocity
 * omega is in the counterclockwise direction
 * velocity is in the local X direction
 */
void OmegaVelocityManipulator::updateState(Beep* beep, World* world)
{
  double delta_t = world->getLayer("BeepLayer")->timeSinceLastUpdate();
  double omega = inputs[0];
  double velocity = inputs[1];
  double theta = beep->getState("theta");
  double x = beep->getState("x");
  double y = beep->getState("y");


  //Calculate change in position in the local frame
  double delta_theta = omega * delta_t;
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

unsigned OmegaVelocityManipulator::getInputSize() const
{
  return 2;
}

//serialization
//std::string OmegaVelocityManipulator::save(){return "not implemented";}
//void OmegaVelocityManipulator::load(std::string JSON){}

Manipulator* OmegaVelocityManipulatorFactory::create()
{
  return new OmegaVelocityManipulator();
}

Manipulator* OmegaVelocityManipulatorFactory::create(FactoryParams& params)
{
  return this->create();
}

ADD_TO_FACTORIES(OmegaVelocityManipulator,Manipulator);
