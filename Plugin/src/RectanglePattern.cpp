#include "RectanglePattern.h"
#include "Factory.h"

RectanglePattern::RectanglePattern(unsigned width, unsigned height,
                                   double distance)
  : width(width), height(height), distance(distance), index(0) {}

long int RectanglePattern::size()
{
  return width * height;
}

FactoryParams RectanglePattern::getNext()
{
  double val;
  std::stringstream stream;
  FactoryParams params;

  if(!isEmpty()){
    params.push_back("x");

    double x = index % width * distance;
    stream << x;
    params.push_back(stream.str());

    params.push_back("y");

    double y = index / width * distance;
    stream.str("");
    stream << y;
    params.push_back(stream.str());
    std::cout << "RECTANGLE: " << x << " " << y << " INDEX " << index << std::endl;

    ++index;
  }

  return params;
}

bool RectanglePattern::isEmpty()
{
  return !(index < width * height);
}

Pattern* RectanglePatternFactory::create()
{
  FactoryParams params;
  params.push_back("10 10 10");
  return this->create(params);
}

Pattern* RectanglePatternFactory::create(FactoryParams& params)
{
  unsigned width, height;
  double distance;
  assert(params.size() >= 1);
  std::stringstream stream(params[0]);
  stream >> width >> height >> distance;

  return new RectanglePattern(width, height, distance);
}

ADD_TO_FACTORIES(RectanglePattern, Pattern);
