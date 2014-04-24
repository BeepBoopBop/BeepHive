#ifndef RIGHT_HAND_SIDE_H
#define RIGHT_HAND_SIDE_H
#include "Dealii.h"
#include "BeepHive.h"

using namespace dealii;

/*! 
 * Function class to handle the sources of HeatEquation
 * Returns 0 everywhere except where the sources are defined
 */

  template<int dim>
  class RightHandSide : public Function<dim>
  {
  public:
    RightHandSide ()
      :
      Function<dim>()
    {}

    virtual double value (const Point<dim> &p,
			  const unsigned int component = 0) const;

  };

/*! 
 * Value function used by HeatEquation
 * Defined by the list of sources
 */

  template<int dim>
  double RightHandSide<dim>::value (const Point<dim> &p,
				    const unsigned int component) const
  {
    Assert (component == 0, ExcInternalError());
    Assert (dim == 2, ExcNotImplemented());

    const double time = this->get_time();
    
  }
#endif
