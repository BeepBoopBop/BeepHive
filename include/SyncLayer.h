#ifndef SYNCMODEL_H
#define SYNCMODEL_H 

#include "DiscreteTimeLayer.h"
#include "Event.h"

/*!
 * The sync model implements syncronization with the GUI process
 */
class SyncLayer : public DiscreteTimeLayer
{
  public:
    SyncLayer();
    SyncLayer(double event_frequency);

    virtual void update(const Event* event);
};

#endif /* SYNCMODEL_H */
