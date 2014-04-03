#ifndef MANIPULATOR_H
#define MANIPULATOR_H 

#include <vector>

#include "Layer.h"
#include "Beep.h"
#include "World.h"

class Beep;
class Layer;
class World;

class Manipulator 
{
  public:
    Manipulator(){}
    //virtual ~Manipulator() = 0;

    //! Set manipulator inputs
    void setInputs(const std::vector<double>& in);
    //! The size of the input vector that this class takes
    virtual int getInputSize() const = 0;
    //! Update the environment based on input state
    virtual void updateState(Beep* beep, World* world) = 0;


  protected:
    std::vector<double> inputs;

};




#endif /* MANIPULATOR_H */
