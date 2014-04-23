#ifndef COMMAND_H
#define COMMAND_H 

#include <vector>
#include <string>

#include "Factory.h"
//#include "World.h"

class World;

class Command
{
  public:
    virtual void run(World* world) = 0;
};



class CreateCommand : public Command
{
  public:
    CreateCommand(FactoryParams params);
    virtual void run(World* world) = 0;
  protected:
    FactoryParams params;
    std::string type;
};



class BeepCommand : public CreateCommand
{
  public:
    BeepCommand(FactoryParams params);
    virtual void run(World* world);
};

DEFINE_FACTORY(BeepCommand, Command);

#endif /* COMMAND_H */
