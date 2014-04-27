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



class CustomBeepFactories : public BasicFactories<CustomBeepFactory>, 
                            public Singleton<CustomBeepFactories> {};



class World;

class CustomBeepCommand : public Command
{
  public:
    CustomBeepCommand(FactoryParams params);
    virtual void run(World* world);

    virtual std::string  save();
    virtual void load(std::string JSON);
  private:
    std::string type;
    std::string base;
};

DEFINE_FACTORY(CustomBeepCommand, Command);



class CustomBeepFeatureCommand : public Command
{
  public:
    CustomBeepFeatureCommand(FactoryParams params);
    virtual void run(World* world);

    virtual std::string  save();
    virtual void load(std::string JSON);
  private:
    std::string beep_type;
    std::string component_type;
    std::string concrete_component;
    std::string name;
    FactoryParams params;
};

DEFINE_FACTORY(CustomBeepFeatureCommand, Command);
#endif /* CUSTOMBEEPFACTORY_H */
