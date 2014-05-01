#include <string>

#include "FileCommunicator.h"
#include "BeepHive.h"

std::string generateName(std::string file_name, std::string extension)
{
  mpi::communicator comm;
  std::stringstream stream(file_name);
  stream << file_name << "_" << comm.rank() << extension;
}

InFileCommunicator::InFileCommunicator(std::string file_name) : file(file_name)
{
  std::cout << "OPENING " << file_name << " FOR READ" << std::endl;
}



/*!
 * Reads in data from file
 * \todo add time-stamping
 */
std::string InFileCommunicator::run(std::string& message)
{
  std::string data;
  std::getline(file,data,'\n');
  std::cout << "LOADING: " << data << std::endl;
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

ADD_TO_FACTORIES(InFileCommunicator,Communicator);



OutFileCommunicator::OutFileCommunicator(std::string file_name) : file(file_name)
{
  std::cout << "OPENING " << file_name << " FOR WRITE" << std::endl;
}



//! Sends data to output file
std::string OutFileCommunicator::run(std::string& message)
{
  std::cout << "WRITING: " << message << std::endl;
  file << message << '\n';
  file.flush();
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

ADD_TO_FACTORIES(OutFileCommunicator,Communicator);
