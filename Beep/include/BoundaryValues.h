#ifndef BOUNDARY_VAL_H
#define BOUNDARY_VAL_H

#include "Dealii.h"
#include "BeepHive.h"

/*!
 * This class defines the boundary values for the HeatEquation class
 * when called it will return the base environment temperature.
 *
 * Dimension independent and needs to be called as a template
 *
 * BoundaryValues<2> is the primarily used one for 2d
 */ 
using namespace dealii;

template<int dim>
  class BoundaryValues : public Function<dim>
  {
  public:
    virtual double value (const Point<dim>  &p,
			  const unsigned int component = 0) const;
  };

/*! 
 * Template function to return point value will always return the base 
 * environment value (currently 0 by default)
 */
  
  template<int dim>
  double BoundaryValues<dim>::value (const Point<dim> &/*p*/,
				     const unsigned int component) const
  {
    Assert(component == 0, ExcInternalError());
    return 50;
  }

#endif
