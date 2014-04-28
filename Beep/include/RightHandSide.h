#ifndef RIGHT_HAND_SIDE_H
#define RIGHT_HAND_SIDE_H

#include <vector>

#include "Dealii.h"
#include "BeepHive.h"
#include "EnvObject.h"

typedef std::vector<EnvObject*> ObjectArray;

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
    virtual void addObject(EnvObject* object);

  private:
    ObjectArray sources;

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

    for(int i = 0; i < sources.size(); i++){
      int xmin = sources[i]->getX();
      int xmax = xmin+(sources[i]->getWidth());
      int ymin = sources[i]->getY();
      int ymax = ymin+(sources[i]->getHeight());

      if( p[0] > xmin && p[0] < xmax && p[1] > ymin && p[1] > ymax )
        return sources[i]->getTemp();

    }
    
    return 0;
    
  }
  
  template<int dim>
  void RightHandSide<dim>::addObject(EnvObject* object)
  {
    if( object->isSource() ){
      sources.push_back(object);
      DEBUG("Adding Source to RHS");
    }
  }
#endif
