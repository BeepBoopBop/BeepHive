#ifndef DISCRETETIMEMODEL_H
#define DISCRETETIMEMODEL_H 

#include "Model.h"

/*!
 * Base model for all discrete time-stepping models.
 * For the most part, this should be the only kind of model used.
 */
class DiscreteTimeModel : public Model
{
  public:
    DiscreteTimeModel();
    DiscreteTimeModel(double event_frequency);
    virtual ~DiscreteTimeModel();

    virtual Event getNextEvent();
    virtual void update(const Event* event);

    virtual double getEventFrequency();
    virtual void setEventFrequency(double event_frequency);

  protected:
    double event_frequency;
};

#endif /* DISCRETETIMEMODEL_H */
