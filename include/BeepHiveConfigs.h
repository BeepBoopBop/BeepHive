#ifndef BEEPHIVECONFIGS_H
#define BEEPHIVECONFIGS_H 

#include "BeepHive.h"

/*!
 * Singleton configuration class for use by BeepHive
 *
 * Information contained here includes global information on processes,
 * information contained in startup parameters, and how to run simulations
 */
class BeepHiveConfigs
{
  public:
    static BeepHiveConfigs& getInstance();
    void parseArgs(const int argc, char** argv);
  private:
    BeepHiveConfigs();
    //! Do not implement
    BeepHiveConfigs(const BeepHiveConfigs& copy);
    //! Do not implement
    BeepHiveConfigs& operator=(const BeepHiveConfigs& copy);
};

#endif /* BEEPHIVECONFIGS_H */
