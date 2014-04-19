#include "HeatEquation.h"

HeatEquation::HeatEquation ():
fe(1),
dof_handler(triangulation),
time_step(1. / 500),
theta(0.5)
{}

HeatEquation::~HeatEquation (){}

