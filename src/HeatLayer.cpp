#include "BeepHive.h"
#include "HeatLayer.h"

HeatLayer::HeatLayer() : DiscreteTimeLayer() {}



HeatLayer::HeatLayer(double event_frequency) : DiscreteTimeLayer(event_frequency) {}



HeatLayer::~HeatLayer() {}



void HeatLayer::update(const Event* event, World* world){

  if(!initialized){

    this->discretization.setup_system();
    initialized = true;

  }
  
  this->discretization.solve_time_step();

}
  



