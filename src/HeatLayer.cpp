#include "BeepHive.h"
#include "HeatLayer.h"

HeatLayer::HeatLayer() : DiscreteTimeLayer(), initialized(false){}



HeatLayer::HeatLayer(double event_frequency) : DiscreteTimeLayer(event_frequency), initialized(false) {}



HeatLayer::~HeatLayer() {}



void HeatLayer::update(const Event* event, World* world){

  if(!initialized){

    this->discretization.setup_system();
    initialized = true;

  }
  
  this->discretization.solve_time_step();

}

double HeatLayer::getValue( int x, int y, int z ){

  return this->discretization.getValue( x, y );

}
  



