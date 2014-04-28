#include "BeepHive.h"
#include "HeatLayer.h"
#include "Dealii.h"

HeatLayer::HeatLayer() : initialized(false), DiscreteTimeLayer(){}



HeatLayer::HeatLayer(double event_frequency) : initialized(false), DiscreteTimeLayer(event_frequency){}



HeatLayer::~HeatLayer() {}

void HeatLayer::setup(World* world)
{
  
  DEBUG("Setting up HeatEquation");
  //will get list of objects from world and add them to RHS
  World::ObjectIterator it;

  for(it = world->objectBegin(); it != world->objectEnd(); ++it){
    discretization.addSource(*it);
  }
  
  //setup listener points to evaluate the model at for graphical info

  for(double i = 0; i <= 1000; i +=5){
    for( double j = 0; j <= 1000; j+=5){
      DataPoint newPoint = new DataPoint( i, j );
      values.push_back(newPoint);
    }
  }

  initialized = true;
}

void HeatLayer::update(const Event* event, World* world)
{

  if(!initialized){
    this->setup(world);
  }
  
  DiscreteTimeLayer::update(event, world);
  DEBUG("Updating HeatLayer");
  this->discretization.run();

}

double HeatLayer::getValue( double x, double y )
{

  return this->discretization.getValue( x, y );

}
  
std::string HeatLayer::getOutput()
{

  for( int i = 0; i < values.size(); i++ ){
    double newVal = this->getValue( values[i].getX(), values[i].getY() );
    values[i].setValue(newVal);
  }

}

Layer* HeatLayerFactory::create()
{
  return new HeatLayer();
}



Layer* HeatLayerFactory::create(FactoryParams& params)
{
  double event_frequency = 0;
  if(params.size() > 0){
    std::stringstream stream(params[0]);
    stream >> event_frequency;
  }
  return new HeatLayer(event_frequency);
}



NOT_IMPLEMENTED(void HeatLayer::write())



ADD_TO_FACTORIES(HeatLayer, Layer);
