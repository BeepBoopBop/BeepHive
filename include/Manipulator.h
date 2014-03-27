#ifndef MANIPULATOR_H
#define MANIPULATOR_H 


class Manipulator 
{
  public:
    Manipulator(Model* m){model = m;}
    virtual ~Manipulator() = 0;

    //alter the model layer that is pointed to, specific implementation decides how
    virtual void alterModel(float delta) = 0;


  protected:
    //the layer that this manipulator can affect
    Model* model;

}




#endif /* MANIPULATOR_H */
