#ifndef INITIAL_VALUES_H
#define INITIAL_VALUES_H

#include "Dealii.h"

using namespace dealii;

template<int dim>
  class InitialValues : public Function<dim>
  {
  public:
    InitialValues ()
      :
      Function<dim>()
    {}

    virtual double value (const Point<dim> &p,
			  const unsigned int component = 0) const;

};

/*! 
 * Initial Value function used by HeatEquation
 * Defined by the list of sources
 */

  template<int dim>
  double InitialValues<dim>::value (const Point<dim> &p,
				    const unsigned int component) const
  {
    Assert (component == 0, ExcInternalError());
    Assert (dim == 2, ExcNotImplemented());

    const double time = this->get_time();
    
    return 50;
    
  }
  
#endif
