#include <string>

#include "CustomBeepFactory.h"



CustomBeepFactory::CustomBeepFactory(std::string type_name, std::string base_factory,
    FactoryParams params)
: CustomFactory<Beep>(type_name, base_factory, params)
{
  CustomBeepFactories& custom_beep_factories
    = CustomBeepFactories::getInstance();
  custom_beep_factories.addFactory(*this);
  std::cout << "Creating BeepFactory: " << type_name << std::endl;
  assert(CustomBeepFactories::getInstance()[type_name]);
  assert(Factories<Beep>::getInstance()[type_name]);
}



Beep* CustomBeepFactory::create()
{
  Beep* beep=this->factory.factory->create(this->factory.params);
  Sensor* sensor;
  Manipulator* manipulator;
  Controller* controller;

  {
    Map<FactoryAndParams<Sensor> >::iterator it;

    for(it=sensors.begin(); it!=sensors.end(); ++it){
      sensor=it->second.factory->create(it->second.params);
      beep->addSensor(it->first, sensor);
    }
  }

  {
    Map<FactoryAndParams<Manipulator> >::iterator it;
    for(it=manipulators.begin(); it!=manipulators.end(); ++it){
      manipulator=it->second.factory->create(it->second.params);
      beep->addManipulator(it->first, manipulator);
    }
  }

  controller = this->controller.factory->create(this->controller.params);
  beep->setController(controller);


  return beep;
}



Beep* CustomBeepFactory::create(FactoryParams& params)
{
  this->factory.params=params;
  return this->create();
}



void CustomBeepFactory::addSensor(std::string instance_name, std::string base_type,
    FactoryParams params)
{
  Factories<Sensor>& factories=Factories<Sensor>::getInstance();
  sensors[instance_name]=FactoryAndParams<Sensor>(factories[base_type], params);
}



void CustomBeepFactory::addManipulator(std::string instance_name, std::string base_type,
    FactoryParams params)
{
  Factories<Manipulator>& factories=Factories<Manipulator>::getInstance();
  manipulators[instance_name]=
    FactoryAndParams<Manipulator>(factories[base_type], params);
}



void CustomBeepFactory::setController(std::string base_type,
    FactoryParams params)
{
  Factories<Controller>& factories=Factories<Controller>::getInstance();
  controller=FactoryAndParams<Controller>(factories[base_type], params);
}




  CustomBeepCommand::CustomBeepCommand(FactoryParams params)
: concrete_type(params[0]), base(params[1])
{
  assert(params.size()>=2);
  this->concrete_type=params[0];
  this->base=params[1];

  /*
     for(int i=2; i<params.size(); ++i){
     this->params.push_back(params[i]);
     }
     */
}



void CustomBeepCommand::run(World* world)
{
  CustomBeepFactory* factory = new CustomBeepFactory(concrete_type, base);
}



void  CustomBeepCommand::saveHelper(ptree& tree)
{
  tree.put("concrete_type", this->concrete_type);
  tree.put("base", this->base);
  return;
}



void CustomBeepCommand::load(std::string JSON)
{
  if(JSON.size() > 0){
    ptree tree = StringToPTree(JSON);
    concrete_type = tree.get<std::string>("concrete_type");
    base = tree.get<std::string>("base");
  }
}



Command* CustomBeepCommandFactory::create()
{
  FactoryParams params = {"",""};
  return create(params);
}



Command* CustomBeepCommandFactory::create(FactoryParams& params)
{
  return new CustomBeepCommand(params);
}



ADD_TO_FACTORIES(CustomBeepCommand, Command);



static std::string valOrBlank(size_t i, FactoryParams& params)
{
  if(params.size() > i){
    return params[i];
  }else{
    return "";
  }
}



CustomBeepFeatureCommand::CustomBeepFeatureCommand(FactoryParams params)
{
  int i=0;
  component_type=valOrBlank(i++,params);
  name=valOrBlank(i++,params);
  concrete_component=valOrBlank(i++,params);
  beep_type=valOrBlank(i++,params);

  for(; i<params.size(); ++i){
    std::cout << "PARAM: " << params[i] << std::endl;
    this->params.push_back(params[i]);
  }
}



void CustomBeepFeatureCommand::run(World* world)
{
  CustomBeepFactories& factories = CustomBeepFactories::getInstance();
  if(component_type == "Sensor"){
    factories[beep_type]->addSensor(name, concrete_component, params);
  }else if(component_type == "Manipulator"){
    factories[beep_type]->addManipulator(name, concrete_component, params);
  }else if(component_type == "Controller"){
    factories[beep_type]->setController(concrete_component);
  }
}



void  CustomBeepFeatureCommand::saveHelper(ptree& tree)
{
  tree.put("beep_type", this->beep_type);
  tree.put("component_type", this->component_type);
  tree.put("concrete_component", this->concrete_component);
  tree.put("name", this->name);

  for(int i = 0; i<this->params.size(); i++)
  {
    std::string array = "params.";
    array.append(std::to_string(i));
    tree.put(array, this->params[i]);
  }

  return;
}



void CustomBeepFeatureCommand::load(std::string JSON)
{
  if(JSON.size() > 0){
    ptree tree = StringToPTree(JSON);
    component_type = tree.get<std::string>("component_type");
    name = tree.get<std::string>("name");
    concrete_component = tree.get<std::string>("concrete_component");
    beep_type = tree.get<std::string>("beep_type");

    if(tree.find("params") != tree.not_found()){
      BOOST_FOREACH(ptree::value_type &v, tree.get_child("params")){
        this->params.push_back(v.second.data());
      }
    }
  }
}



Command* CustomBeepFeatureCommandFactory::create()
{
  FactoryParams params;
  return create(params);
}



Command* CustomBeepFeatureCommandFactory::create(FactoryParams& params)
{
  return new CustomBeepFeatureCommand(params);
}

ADD_TO_FACTORIES(CustomBeepFeatureCommand, Command);
