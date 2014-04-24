#ifndef HEATLAYER_H
#define HEATLAYER_H 

#include "DiscreteTimeLayer.h"
#include "HeatEquation.h"
#include "Factory.h"

/*!
 * This layer updates the heat equation for the simulation.
 */
class HeatLayer : public DiscreteTimeLayer
{

  friend class World;
  public:

    virtual ~HeatLayer();
    HeatLayer();
    HeatLayer(double event_frequency);
    virtual void update(const Event* event, World* world);
    double getValue( double x, double y );

  private:
    
    //! The equation that the layer updates
    HeatEquation<2> discretization;

};

DEFINE_FACTORY(HeatLayer,Layer);

#endif /* HEATLAYER_H */
