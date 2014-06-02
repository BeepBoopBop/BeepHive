#ifndef LOADCOMMAND_H
#define LOADCOMMAND_H 

#include "Command.h"

/*!
 * Class for loading plugins
 *
 * The class is instantiated with the name of a shared library. When run it
 * loads all symbols in the library.
 * Libraries are expeceted to use the ADD_TO_FACTORIES to perform the remaining
 * work to load themselves
 */
class LoadCommand : public Command
{
  public:
    LoadCommand(std::string file_name);
    void run(World* world);

    //serialization
    void  saveHelper(ptree& tree);
    void load(std::string JSON);
    std::string type() { return "LoadCommand"; };
  private:
    std::string file_name;
};

DEFINE_FACTORY(LoadCommand, Command);

#endif /* LOADCOMMAND_H */
