#ifndef BEEP_H
#define BEEP_H 

#include <iostream>

#include "Command.h"
#include "Factory.h"
#include "Manipulator.h"
#include "Sensor.h"
#include "Stateful.h"

class Controller;
class Manipulator;
class Sensor;
class World;

/*!
 * The Beep class is a template for robots in BeepHive
 * 
 * Custom beeps can be created by setting a controller and by adding
 * Sensors and Manipulators
 */
class Beep: public Stateful
{
  public:
    Beep();
    ~Beep();
    void readSensors(World* world);
    void runController();
    void runManipulators(World* world);

    void setController(Controller* controller);

    void addSensor(std::string sensor_name, Sensor* sensor);
    Sensor* getSensor(std::string sensor_name);

    void addManipulator(std::string manipulator_name, Manipulator* manipulator);
    Manipulator* getManipulator(std::string manipulator_name);

    virtual std::string type() { return "Beep"; }

  private:
    Controller* controller;
    Map<Sensor*> sensors;
    Map<Manipulator*> manipulators;
    Map<double> states;
};

DEFINE_FACTORY(Beep, Beep);



class BeepCommand : public CreateCommand
{
  public:
    BeepCommand() {}
    //! vector concrete type, param1,val1
    BeepCommand(FactoryParams params);
    virtual void run(World* world);
    std::string type() { return "BeepCommand"; }
};

DEFINE_FACTORY(BeepCommand, Command);

#endif /* BEEP_H */
