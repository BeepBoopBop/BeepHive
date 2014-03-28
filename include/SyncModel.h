#ifndef SYNCMODEL_H
#define SYNCMODEL_H 

#include "DiscreteTimeModel.h"
#include "Event.h"

/*!
 * The sync model implements syncronization with the GUI process
 */
class SyncModel : public DiscreteTimeModel
{
  public:
    SyncModel();
    SyncModel(double event_frequency);

    virtual void update(const Event* event);
};

#endif /* SYNCMODEL_H */
