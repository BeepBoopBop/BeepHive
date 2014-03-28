#include "BeepHive.h"
#include "BeepModel.h"

BeepModel::BeepModel() : DiscreteTimeModel() {}



BeepModel::BeepModel(double event_frequency) : DiscreteTimeModel(event_frequency) {}



BeepModel::~BeepModel() {}



void BeepModel::update(const Event* event)
{
  DiscreteTimeModel::update(event);
  DEBUG("Updating BeepModel");
}
