#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H 

#include "BeepHive.h"
#include "Singleton.h"
#include "Serializable.h"
#include "Command.h"
#include <stack>


typedef struct so
{
  std::string type;
  std::string JSON;
} SerialObject;

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
    //SerialObject popObject();
    std::string getInput();
    void addToOutput(std::string object);
    void addToInput(std::string object);
    void setOutput(std::string output);
    void constructStack();
    bool isEmpty();
    std::string getStringOutput();
  private:
    Map<Communicator*> communicators;
    std::string output;
    ptree outputTree;
    ptree inputTree;
    std::string input;
    std::stack<SerialObject> inputStack;
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
