#ifndef SYNCLAYER_H
#define SYNCLAYER_H 

#include "DiscreteTimeLayer.h"

/*!
 * The sync layer implements syncronization with the GUI process
 *
 * This is a special layer that users are not able to instantiate. The synclayer
 * is automatically created by the world class if BeepHive was started with a
 * GUI. There is no reason for the existence of multiple SyncLayers, so the user
 * is explicitly prevented from instantiating more.
 */
class SyncLayer : public DiscreteTimeLayer
{
  friend class World;
  public:
    virtual void update(const Event* event, World* world);
    virtual void write() {};

  private:
    SyncLayer();
    SyncLayer(double event_frequency);
    SyncLayer(const SyncLayer& copy);
    SyncLayer& operator=(const SyncLayer& copy);
};

#endif /* SYNCLAYER_H */
