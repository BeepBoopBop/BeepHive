#include <string>

#include "FileCommunicator.h"
#include "BeepHive.h"

std::string generateName(std::string file_name, std::string extension)
{
  mpi::communicator comm;
  std::stringstream stream(file_name);
  stream << file_name << "_" << comm.rank() << extension;
}

InFileCommunicator::InFileCommunicator(std::string file_name)
{
  std::string name = generateName(file_name,".bh");
  file.open(name);
}



/*!
 * Reads in data from file
 * \todo add time-stamping
 */
std::string InFileCommunicator::run(std::string& message)
{
  std::string data;
  file >> data;
  return data;
}



Communicator* InFileCommunicatorFactory::create()
{
  return new InFileCommunicator("in");
}



Communicator* InFileCommunicatorFactory::create(FactoryParams& params)
{
  if(params.size() >= 1){
    return new InFileCommunicator(params[0]);
  }else{
    return create();
  }
}



OutFileCommunicator::OutFileCommunicator(std::string file_name) : file(file_name)
{
  std::string name = generateName(file_name,".bh");
  file.open(name);
}



//! Sends data to output file
std::string OutFileCommunicator::run(std::string& message)
{
  file << message;
  return std::string();
}




Communicator* OutFileCommunicatorFactory::create()
{
  return new OutFileCommunicator("in");
}



Communicator* OutFileCommunicatorFactory::create(FactoryParams& params)
{
  if(params.size() >= 1){
    return new OutFileCommunicator(params[0]);
  }else{
    return create();
  }
}
