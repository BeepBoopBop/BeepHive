#ifndef COMMAND_H
#define COMMAND_H 

#include <string>

#include "Factory.h"
#include "Serializable.h"

class World;

class Command: public Serializable
{
  public:
    //! Run command for when no world is present
    void run();
    virtual void run(World* world) = 0;
};



class CreateCommand : public Command
{
  public:
    CreateCommand(FactoryParams params);
    CreateCommand(){}

    //serialization
    virtual void  saveHelper(ptree& tree);
    virtual void load(std::string JSON);

  protected:
    FactoryParams params;
    std::string concrete_type;
};

#endif /* COMMAND_H */
