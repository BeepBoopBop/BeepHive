#include <sstream>
#include "Layer.h"

Layer::Layer()
{
  time = 0; 
}



Layer::Layer(double event_frequency)
{
  time = 0;
}



Layer::~Layer() {}


double Layer::getTime() const
{
  return time; 
}



void Layer::setTime(double new_time)
{ 
  time = new_time;
}



//! this is just here to make the compiler happy
double Layer::timeSinceLastUpdate()
{
  return -1;
}



//! this is just here to make the compiler happy
double Layer::getValue(double x, double y)
{
  return -1;
}



void Layer::update(const Event* event, World* world)
{
  this->setTime(event->getTime());
  //-- std::cout << "Layer updating! Time is now: " << event->getTime() << std::endl;
}



LayerCommand::LayerCommand(FactoryParams params)
{
  if(params.size() >= 3){
    int i=0;
    name=params[i++];
    concrete_type=params[i++];
    std::stringstream stream(params[i++]);
    stream >> frequency;
  }
}


void LayerCommand::run(World* world)
{
  if(world != NULL){
    double val;
    std::stringstream stream(frequency);
    stream >> val;

    Layer* layer = Factories<Layer>::getInstance()[concrete_type]->create();
    world->addLayer(name, layer, val);
  }
}



void  LayerCommand::saveHelper(ptree& tree)
{
  tree.put("frequency", this->frequency);
  tree.put("name", this->name);
  tree.put("concrete_type", this->concrete_type);
  return;
}



void LayerCommand::load(std::string JSON)
{
  if(JSON.size() > 0){
    ptree tree = StringToPTree(JSON);
    frequency = tree.get<std::string>("frequency");
    name = tree.get<std::string>("name");
    concrete_type = tree.get<std::string>("concrete_type");
  }
}




Command* LayerCommandFactory::create()
{
  FactoryParams temp;
  return this->create(temp);
}



Command* LayerCommandFactory::create(FactoryParams& params)
{
  return new LayerCommand(params);
}



ADD_TO_FACTORIES(LayerCommand, Command);
