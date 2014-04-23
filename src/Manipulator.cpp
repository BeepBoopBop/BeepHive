#include "Manipulator.h"
#include "BeepHive.h"


void Manipulator::setInputs(const std::vector<double>& in)
{
  assert(in.size() == this->getInputSize());
  inputs=in;
}
