#ifndef STATEFUL_H
#define STATEFUL_H 

#include "BeepHive.h"
#include "Serializable.h"

#define SCOPE "::"

class Stateful //: public Serializable
{
  public:
    typedef Map<double>::const_iterator StateIterator;
    typedef Map<Stateful*>::const_iterator ChildIterator;
    //! Adds a new state variable to the state map, creating if necessary
    void setState(std::string state_name, double initial_state=0);
    //! Get the value of an existing state variable.
    double getState(std::string state_name);
    //! Add a child stateful
    void addChild(std::string stateful_name, Stateful* stateful);
    //! Get a child stateful
    Stateful* getChild(std::string stateful_name);

    //serialization
    //std::string  save();
    //void load(std::string JSON);


  private:
    Map<double>::iterator findState(std::string state_name);
  protected:
    Map<double> states;
    Map<Stateful*> children;
};

#endif /* STATEFUL_H */
