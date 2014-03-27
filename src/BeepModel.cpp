#include "BeepHive.h"
#include "BeepModel.h"

BeepModel::BeepModel() : DiscreteTimeModel() {}



BeepModel::BeepModel(double event_frequency) : DiscreteTimeModel(event_frequency) {}



BeepModel::~BeepModel() {}



void BeepModel::update(Event* event)
{
  DiscreteTimeModel::update(event);
}
