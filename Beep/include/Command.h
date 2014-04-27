#ifndef COMMAND_H
#define COMMAND_H 

#include <vector>
#include <string>
#include "Serializable.h"
#include "Factory.h"

class World;

class Command: public Serializable
{
  public:
    //! Run command for when no world is present
    void run();
    virtual void run(World* world) = 0;

    virtual std::string  save() = 0;
    virtual void load(std::string JSON) = 0;
};



class CreateCommand : public Command
{
  public:
    CreateCommand(FactoryParams params);
    CreateCommand(){}

    virtual void run(World* world) = 0;

    //serialization
    virtual std::string  save();
    virtual void load(std::string JSON);

  protected:
    FactoryParams params;
    std::string type;
};

#endif /* COMMAND_H */
