#ifndef MANIPULATOR_H
#define MANIPULATOR_H 

#include <vector>

#include "Layer.h"
#include "Beep.h"
#include "World.h"

class Beep;
class Layer;
class World;

/*!
 * Manipulators are anything that a robot has that can modify the world
 * or that changes the robots state.
 *
 * The controller is responsible for setting the inputs to the Manipulators.
 *
 * \warning
 * Controllers are the most likely component of a Beep to be dependent on
 * the order of execution. For this reason, conditionals should be avoided
 * in all controller code and all called code. If conditionals are necessary
 * good practice would be to output a warning whenever the main path has not
 * been followed such as if the manipulator failed to pick up an object because
 * another Beep did on the same time-step.
 */
class Manipulator 
{
  public:
    Manipulator(){}
    //virtual ~Manipulator() = 0;

    //! Set manipulator inputs
    void setInputs(const std::vector<double>& in);
    //! The size of the input vector that this class takes
    virtual unsigned getInputSize() const = 0;
    //! Update the environment based on input state
    virtual void updateState(Beep* beep, World* world) = 0;


  protected:
    std::vector<double> inputs;
};




#endif /* MANIPULATOR_H */
