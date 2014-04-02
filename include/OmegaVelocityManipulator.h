#ifndef OMEGAVELOCITYMANIPULATOR_H
#define OMEGAVELOCITYMANIPULATOR_H 

#include "BeepHive.h"
#include "Manipulator.h"

class OmegaVelocityManipulator : public Manipulator {
  void run();
  void updateState();
};

#endif /* OMEGAVELOCITYMANIPULATOR_H */
