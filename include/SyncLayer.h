#ifndef SYNCMODEL_H
#define SYNCMODEL_H 

#include "DiscreteTimeLayer.h"
#include "Event.h"

/*!
 * The sync layer implements syncronization with the GUI process
 *
 * This is a special layer that users are not able to instantiate. The synclayer
 * is automatically created by the world class if BeepHive was started with a
 * GUI. There is no reason for the existence of multiple SyncLayers, so the user
 * is explicitly prevented from instantiating more.
 *
 */
class SyncLayer : public DiscreteTimeLayer
{
  friend class World;
  public:
    virtual void update(const Event* event);

  private:
    SyncLayer();
    SyncLayer(double event_frequency);
    SyncLayer(const SyncLayer& copy);
    SyncLayer& operator=(const SyncLayer& copy);
};

#endif /* SYNCMODEL_H */
