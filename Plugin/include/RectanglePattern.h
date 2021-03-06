#ifndef RECTANGLEPATTERN_H
#define RECTANGLEPATTERN_H 

#include "Factory.h"
#include "Pattern.h"

/*!
 * Generates a rectangular array of indices
 * add params in the form:
 * x coord y coord
 */
class RectanglePattern : public Pattern
{
  public:
    RectanglePattern(unsigned width, unsigned height, double distance);
    //! returns the number of elements in the pattern, -1 for infinite
    virtual long int size();

    //! returns the next element of the pattern
    virtual FactoryParams getNext();

    virtual bool isEmpty();

  private:
    long width;
    long height;
    double distance;

    long index;
};

DEFINE_FACTORY(RectanglePattern, Pattern);

#endif /* RECTANGLEPATTERN_H */
