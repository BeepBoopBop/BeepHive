#include "BeepHive.h"
#include "Communicator.h"
#include "DataPoint.h"
#include "Dealii.h"
#include "Event.h"
#include "HeatLayer.h"
#include "World.h"

HeatLayer::HeatLayer() : initialized(false), DiscreteTimeLayer(){}

HeatLayer::HeatLayer(double event_frequency) : initialized(false), DiscreteTimeLayer(event_frequency){}

HeatLayer::~HeatLayer() {}

void HeatLayer::setup(World* world)
{
  
  DEBUG_OUT("Setting up HeatEquation");
  //will get list of objects from world and add them to RHS
  World::ObjectIterator it;

  for(it = world->objectBegin(); it != world->objectEnd(); ++it){
    discretization.addSource(*it);
  }
  
  //setup listener points to evaluate the model at for graphical info

  for(double i = 0; i <= 1024; i +=16){
    for( double j = 0; j <= 1024; j+=16){
      DataPoint* newPoint = new DataPoint( i, j );
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
  DEBUG_OUT("Updating HeatLayer");
  this->discretization.run();

}

double HeatLayer::getValue( double x, double y )
{

  return this->discretization.getValue( x, y );

}
  
void HeatLayer::getOutput()
{

  DEBUG_OUT("Getting heatlayer output");

  for( int i = 0; i < values.size(); i++ ){
    double newVal = this->getValue( values[i]->getX(), values[i]->getY() );
    values[i]->setValue(newVal);
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

void HeatLayer::write(){
  
  this->getOutput();

  Communicators& communicators = Communicators::getInstance();

  DEBUG_OUT("Got output");
  for( int i = 0; i < values.size(); i++ ){
    std::string newMessage = values[i]->save();
    communicators.addToOutput(newMessage);
    //std::cout << newMessage << " ";
  }

  std::cout << std::endl;

}

ADD_TO_FACTORIES(HeatLayer, Layer);
