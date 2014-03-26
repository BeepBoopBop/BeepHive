#ifndef MANIPULATOR_H
#define MANIPULATOR_H 


class Manipulator 
{
  public:
    Manipulator(Layer* e){environment = e;}
    virtual ~Manipulator() = 0;

    //alter the environment layer that is pointed to, specific implementation decides how
    virtual void alterEnvironment(float delta) = 0;


  protected:
    //the layer that this manipulator can affect
    Layer* environment;

}




#endif /* MANIPULATOR_H */
