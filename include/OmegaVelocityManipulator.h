#ifndef OMEGAVELOCITYMANIPULATOR_H
#define OMEGAVELOCITYMANIPULATOR_H 

#include "BeepHive.h"
#include "Manipulator.h"

class OmegaVelocityManipulator : public Manipulator {
  public:
    OmegaVelocityManipulator();
    void updateState(Beep* beep, World* world);
    int getInputSize() const;
};

#endif /* OMEGAVELOCITYMANIPULATOR_H */
