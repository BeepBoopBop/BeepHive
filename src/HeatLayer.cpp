#include "BeepHive.h"
#include "HeatLayer.h"
#include "Dealii.h"

HeatLayer::HeatLayer() : DiscreteTimeLayer(){}



HeatLayer::HeatLayer(double event_frequency) : DiscreteTimeLayer(event_frequency){}



HeatLayer::~HeatLayer() {}



void HeatLayer::update(const Event* event, World* world){

  this->discretization.run();

}

double HeatLayer::getValue( double x, double y ){

  return this->discretization.getValue( x, y );

}
  



