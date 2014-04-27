#include <string>

#include "FileCommunicator.h"

FileCommunicator::FileCommunicator(std::string file_name) : file(file_name)
{ }



std::string FileCommunicator::run(std::string message)
{
  file << message;
  return std::string();
}
