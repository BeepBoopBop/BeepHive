#ifndef CENTRALCOMMUNICATOR_H
#define CENTRALCOMMUNICATOR_H 

#include <fstream>
#include <string>

#include "Communicator.h"

class CentralCommunicator : public Communicator
{
  public:
    CentralCommunicator() {}
    std::string run(std::string& message);
};

#endif /* CENTRALCOMMUNICATOR_H */
