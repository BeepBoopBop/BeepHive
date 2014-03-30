#ifndef DISCRETETIMEMODEL_H
#define DISCRETETIMEMODEL_H 

#include "Layer.h"

/*!
 * Base model for all discrete time-stepping models.
 * For the most part, this should be the only kind of model used.
 */
class DiscreteTimeLayer : public Layer
{
  public:
    DiscreteTimeLayer();
    DiscreteTimeLayer(double event_frequency);
    virtual ~DiscreteTimeLayer();

    virtual Event getNextEvent();
    virtual void update(const Event* event);
    double timeSinceLastUpdate();

    virtual double getEventFrequency();
    virtual void setEventFrequency(double event_frequency);

  protected:
    double event_frequency;
};

#endif /* DISCRETETIMEMODEL_H */
