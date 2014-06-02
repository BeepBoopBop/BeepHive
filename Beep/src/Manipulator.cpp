#include "BeepHive.h"
#include "Manipulator.h"

void Manipulator::setInputs(const std::vector<double>& in)
{
  assert(in.size() == this->getInputSize());
  inputs=in;
}
