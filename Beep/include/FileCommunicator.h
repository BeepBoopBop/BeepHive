#ifndef FILECOMMUNICATOR_H
#define FILECOMMUNICATOR_H 

#include <string>
#include <fstream>

#include "Communicator.h"
#include "Command.h"
#include "Factory.h"

class World;

class InFileCommunicator : public Communicator
{
  public:
    InFileCommunicator(std::string file_name);
    std::string run(std::string& message);
  private:
    std::ifstream file;
};

DEFINE_FACTORY(InFileCommunicator, Communicator);



/*!
 * Use this command to instruct another process to save data to a file
 */
class OutFileCommunicator : public Communicator
{
  public:
    OutFileCommunicator(std::string file_name);
    std::string run(std::string& message);
  private:
    std::ofstream file;
};

DEFINE_FACTORY(OutFileCommunicator, Communicator);

#endif /* FILECOMMUNICATOR_H */
