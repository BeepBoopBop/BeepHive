#ifndef BEEPHIVECONFIGS_H
#define BEEPHIVECONFIGS_H 

#include "BeepHive.h"
#include "Singleton.h"

/*!
 * Singleton configuration class for use by BeepHive
 *
 * Information contained here includes global information on processes,
 * information contained in startup parameters, and how to run simulations
 *
 * \todo implement parsing of args
 */
class BeepHiveConfigs: public Singleton<BeepHiveConfigs>
{
  public:
    BeepHiveConfigs();
    void parseArgs(const int argc, char** argv);
    
    void setTimeLimit(double time_limit);
    double getTimeLimit();
    bool guiEnabled();
  private:
    //! Do not implement
    BeepHiveConfigs(const BeepHiveConfigs& copy);
    //! Do not implement
    BeepHiveConfigs& operator=(const BeepHiveConfigs& copy);

    /*!
     * Maximim allowed simulation time, negative and zero values interpreted as
     * no limit
     */
    double time_limit;
    bool gui_enabled;
};

#endif /* BEEPHIVECONFIGS_H */
