#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H 

#include "BeepHive.h"
#include "Singleton.h"
#include "Serializable.h"
#include "Command.h"

/*!
 * The communicator abstract class defines a basic interface for all
 * communication
 *
 * This class is used for both input and output. This allows for some
 * communicators to serve dual purposes as input and output and allows for the
 * ordering constraints imposed by MPI
 */
class Communicator
{
  public:
    virtual std::string run(std::string& message) = 0;
};



class Communicators : public Singleton<Communicators>
{
  public:
    Communicators();
    void run();
    void addCommunicator(std::string name, Communicator* communicator);
    std::string getInput();
    void addToOutput(std::string object);
    void setOutput(std::string output);
    std::string getStringOutput();
  private:
    Map<Communicator*> communicators;
    std::string output;
    ptree outputTree;
    std::string input;
};

class CommunicatorCommand : public CreateCommand
{
  public:
    CommunicatorCommand(FactoryParams params);

    virtual void run(World* world);

    std::string type() { return "CommunicatorCommand"; }
};

DEFINE_FACTORY(CommunicatorCommand, Command);

#endif /* COMMUNICATOR_H */
