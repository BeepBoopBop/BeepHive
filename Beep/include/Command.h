#ifndef COMMAND_H
#define COMMAND_H 

#include <vector>
#include <string>
#include "Serializeable.h"
#include "Factory.h"
//#include "World.h"

class World;

class Command 
{
  public:
    //! Run command for when no world is present
    void run();
    virtual void run(World* world) = 0;

};



class CreateCommand : public Command, public Serializeable
{
  public:
    CreateCommand(FactoryParams params);
    CreateCommand(){}

    virtual void run(World* world) = 0;

    //serialization
    std::string  save();
    void load(std::string JSON);

  protected:
    FactoryParams params;
    std::string type;
};

#endif /* COMMAND_H */
