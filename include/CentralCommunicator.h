#ifndef CENTRALCOMMUNICATOR_H
#define CENTRALCOMMUNICATOR_H 
#include <string>
#include <fstream>

#include "Communicator.h"

class CentralCommunicator : public Communicator
{
  public:
    CentralCommunicator() {}
    std::string run(std::string& message);
};

#endif /* CENTRALCOMMUNICATOR_H */
