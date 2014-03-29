#ifndef MANIPULATOR_H
#define MANIPULATOR_H 

#include <vector>

#include "Model.h"
#include "Beep.h"

class Beep;

class Manipulator 
{
  public:
    Manipulator(Beep* b, Model* m){beep = b; model = m;}
    //virtual ~Manipulator() = 0;

    //! Set manipulator inputs
    void setInputs(const std::vector<double>& in);
    //! The size of the input vector that this class takes
    virtual int getInputSize() const = 0;
    //! Update the environment based on input state
    virtual void update() = 0;


  protected:
    //!the layer that this manipulator can affect
    Model* model;
    Beep* beep;
    std::vector<double> inputs;

};




#endif /* MANIPULATOR_H */
