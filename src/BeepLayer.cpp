#include "BeepHive.h"
#include "BeepLayer.h"

BeepLayer::BeepLayer() : DiscreteTimeLayer() {}



BeepLayer::BeepLayer(double event_frequency) : DiscreteTimeLayer(event_frequency) {}



BeepLayer::~BeepLayer() {}



void BeepLayer::update(const Event* event)
{
  DiscreteTimeLayer::update(event);
  DEBUG("Updating BeepLayer");
}
