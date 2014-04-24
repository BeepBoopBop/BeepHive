#ifndef HEATLAYER_H
#define HEATLAYER_H 

#include "DiscreteTimeLayer.h"
#include "HeatEquation.h"

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
    double getValue( int x, int y );

  private:
    
    //! The equation that the layer updates
    HeatEquation<2> discretization;
    //! Used to tell whether the equation has been initialized or not.
    bool initialized;
};

#endif /* HEATLAYER_H */
