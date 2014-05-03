#ifndef HEATLAYER_H
#define HEATLAYER_H 

#include "DiscreteTimeLayer.h"
#include "HeatEquation.h"
#include "Factory.h"
#include "EnvObject.h"
#include <vector>
#include "DataPoint.h"

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

    virtual void write();

  private:
    
    bool initialized;
   
    //! The equation that the layer updates
    std::vector<DataPoint*> values;
    HeatEquation<2> discretization;
    void setup(World* world);
    void getOutput();

};

DEFINE_FACTORY(HeatLayer,Layer);

#endif /* HEATLAYER_H */
