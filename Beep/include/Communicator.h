#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H 

#include <queue>

#include "Command.h"
#include "Singleton.h"

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

/*!
 * The communicators class is used for generalized sending and receiving to and
 * from anonymous sources.
 *
 * Currently Communicators is used for both communication between the backend
 * and the gui and file IO. All data goes to each individual communicator so the
 * code does not have to know where data is going. For instance, running the GUI
 * with the backend or instead writing commands to a file is just a difference
 * of which instances of Communicator are being used.
 */
class Communicators : public Singleton<Communicators>
{
  public:
    Communicators();
    void run();
    void addCommunicator(std::string name, Communicator* communicator);
    SerialObject popObject();
    std::string getInput();
    void addToOutput(std::string object);
    void addToInput(std::string object);
    void constructStack();
    bool isEmpty();
    std::string getStringOutput();
  private:
    static void reset(ptree& tree);
    Map<Communicator*> communicators;
    ptree output_tree;
    ptree input_tree;
    std::string input;
    std::queue<SerialObject> input_queue;
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
