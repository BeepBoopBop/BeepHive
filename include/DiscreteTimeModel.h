#ifndef DISCRETETIMEMODEL_H
#define DISCRETETIMEMODEL_H 

#include "Model.h"

/*
 * Base model for all discrete time-stepping models.
 * For the most part, this should be the only kind of model used.
 */
class DiscreteTimeModel : public Model {
  public:
    virtual Event getNextEvent();

  protected:
    double event_frequency;
};

#endif /* DISCRETETIMEMODEL_H */
