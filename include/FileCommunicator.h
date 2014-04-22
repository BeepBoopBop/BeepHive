#ifndef FILECOMMUNICATOR_H
#define FILECOMMUNICATOR_H 

#include <string>
#include <fstream>

#include "Communicator.h"

class FileCommunicator : public Communicator
{
  public:
    FileCommunicator(std::string file_name);
    std::string run(std::string message);
  private:
    std::ofstream file;
};
#endif /* FILECOMMUNICATOR_H */
