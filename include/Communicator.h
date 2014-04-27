#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H 

#include "BeepHive.h"
#include "Singleton.h"
#include "Serializeable.h"

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



class Communicators : public Singleton<Communicators>, public Serializeable
{
  public:
    void run();
    void addCommunicator(std::string name, Communicator* communicator);
    std::string getInput();
    void addToOutput(std::string object);
    void setOutput(std::string output);
  private:
    Map<Communicator*> communicators;
    std::string output;
    std::string input;
};


#endif /* COMMUNICATOR_H */
