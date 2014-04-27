#ifndef OMEGAVELOCITYMANIPULATOR_H
#define OMEGAVELOCITYMANIPULATOR_H 

#include "BeepHive.h"
#include "Manipulator.h"

/*!
 * This class is a basic nonholonomic manipulator.
 * Inputs are the Rotational and Linear velocity of the robot
 */
class OmegaVelocityManipulator : public Manipulator {
  public:
    OmegaVelocityManipulator();
    void updateState(Beep* beep, World* world);
    unsigned getInputSize() const;
    std::string  save();
    void load(std::string JSON);
};



DEFINE_FACTORY(OmegaVelocityManipulator,Manipulator);

#endif /* OMEGAVELOCITYMANIPULATOR_H */
