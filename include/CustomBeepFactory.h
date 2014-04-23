#ifndef CUSTOMBEEPFACTORY_H
#define CUSTOMBEEPFACTORY_H 

#include <string>

#include "Beep.h"
#include "Factory.h"
#include "Command.h"

class CustomBeepFactory : public CustomFactory<Beep>
{
  public:
    CustomBeepFactory(std::string type_name, std::string base_factory,
                      FactoryParams params=FactoryParams());

    Beep* create();
    Beep* create(FactoryParams& params);

    void addSensor(std::string instance_name, std::string base_type,
                   FactoryParams params=FactoryParams());
    void addManipulator(std::string instance_name, std::string base_type,
                        FactoryParams params=FactoryParams());
    void setController(std::string base_type,
                       FactoryParams params=FactoryParams());

  private:
    //Names of factories used to make the Beep
    Map<FactoryAndParams<Sensor> > sensors;
    Map<FactoryAndParams<Manipulator> > manipulators;
    FactoryAndParams<Controller> controller;
};



class World;

class CustomBeepCommand : public Command
{
  public:
    CustomBeepCommand(FactoryParams params);
    virtual void run(World* world);
  private:
    std::string type;
    std::string base;
};



DEFINE_FACTORY(CustomBeepCommand, Command);

#endif /* CUSTOMBEEPFACTORY_H */
