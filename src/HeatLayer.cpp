#include "BeepHive.h"
#include "HeatLayer.h"
#include "Dealii.h"

HeatLayer::HeatLayer() : DiscreteTimeLayer(){}



HeatLayer::HeatLayer(double event_frequency) : DiscreteTimeLayer(event_frequency){}



HeatLayer::~HeatLayer() {}



void HeatLayer::update(const Event* event, World* world)
{

  this->discretization.run();

}

double HeatLayer::getValue( double x, double y )
{

  return this->discretization.getValue( x, y );

}
  



Layer* HeatLayerFactory::create()
{
  return new HeatLayer();
}



Layer* HeatLayerFactory::create(FactoryParams& params)
{
  double event_frequency = 0;
  if(params.size() > 0){
    std::stringstream stream(params[0]);
    stream >> event_frequency;
  }
  return new HeatLayer(event_frequency);
}

ADD_TO_FACTORIES(HeatLayer, Layer);
