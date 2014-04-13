#ifndef FACTORY_H
#define FACTORY_H 

#include <string>
#include <vector>
#include <iostream>

#include "BeepHive.h"



/*!
 * Macro for the definition of factories is intended to return pointers of
 * type base to objects of type "type"
 *
 * To create the name of the factory "Factory" is concatenated onto the name
 * "type." So a factory of type Beep would be "BeepFactory." The type() method
 * though will simply return "type" and this will be what is listed in the
 * multiton. Keep this in mind when defining the two required member functions:
 *
 * base* typeFactory::create();
 * base* typeFactory::create(FactoryParams& params);
 */
#define DEFINE_FACTORY(_type, base) \
/*! \
 * This type factory returns pointers to base. \
 * \
 * The type factory class and this class were automatically generated by a \
 * compiler macro \
 */ \
class _type##FactoryProxy; \
class _type##Factory : public Factory<base> \
{ \
  public: \
    friend class _type##FactoryProxy; \
    virtual std::string type() \
    { \
      return #_type; \
    } \
 \
    virtual base* create(); \
    virtual base* create(FactoryParams& params); \
  private: \
    _type##Factory() {}; \
}



/*!
 * This macro does the dirty work to add a concrete factory to the multiton
 * associated with the base class.
 *
 * Append a call to this macro at the end of the implementation of the factory
 */
#define ADD_TO_FACTORIES(type,base) \
/*! \
 * This class automatically generated to add a factory of type to the base \
 * multiton 
 * */\
class type##FactoryProxy \
{ \
  public: \
    type##FactoryProxy() \
    { \
      type##Factory* f= new type##Factory(); \
      Factories<base>::getInstance().addFactory(*f); \
    } \
}; \
type##FactoryProxy type##_factory_proxy



typedef std::vector<std::string> FactoryParams;



/*!
 * This is the template for all factories used within BeepHive.
 * 
 * Concrete Factories should inherit from the factory class templated with the
 * base class of the objects created by the factory.
 * All factories should be added to the corresponding multiton using the
 * ADD_FACTORY_TO_BASE_MULTITON macro.
 */
template<class T>
class Factory
{
  public:
    virtual std::string type() = 0;

    virtual T* create() = 0;
    virtual T* create(FactoryParams& params) = 0;
};



/*!
 * Struct to store factories with params
 *
 * This takes the place of using a pair to store factory pointers and parameters
 * together. This makes the syntax for storing these in a map MUCH simpler
 */
template<class T>
class FactoryAndParams
{
  public:
    FactoryAndParams<T>() : factory(0), params() {}
    FactoryAndParams<T>(Factory<T>* factory, FactoryParams params)
      : factory(factory), params(params) {}

    Factory<T>* factory;
    FactoryParams params;
};



/*!
 * This multiton is used to access all Factories in BeepHive.
 *
 * The ADD_FACTORY_TO_BASE_MULTITON macro is responsible for adding factories to
 * the appropriate multiton instance. Our plugin system is implemented by having
 * factories automatically inserted into the multiton using this method.
 */
template<class T>
class Factories
{
  public:
    typedef typename Map<Factory<T>*>::iterator iterator;



    ~Factories<T>()
    {
      iterator it;
      for(it=factories.begin(); it!=factories.end(); ++it){
        delete (*it).second;
      }
    }



    static Factories<T>& getInstance()
    {
      static Factories<T> instance;
      return instance;
    }



    /*!
     * \todo
     * Setup exceptions or some system to allow the user to recover from typos
     * in type names
     */
    Factory<T>* getFactory(std::string type)
    {
      iterator factory = factories.find(type);
      if(factory==factories.end()){
        std::cout << "ERROR: Factory " << type << "  not found, current factories:" << std::endl;
        iterator it;
        for(it=this->begin(); it!=this->end(); ++it){
          std::cout << it->first << std::endl;
        }
        abort();
      }
      return factory->second;
    }



    Factory<T>* operator[](std::string type)
    {
      return getFactory(type);
    }



    void addFactory(Factory<T>& factory)
    {
      factories[factory.type()] = &factory;
    }



    iterator begin()
    {
      return factories.begin();
    }



    iterator end()
    {
      return factories.end();
    }

  protected:
    Factories<T>() {};
    Map<Factory<T>*> factories;
};
    


/*!
 * Custom factories are intended to be used to create factories that combine
 * calls to other factories to create some object.
 *
 * The CustomFactory template class does not necessarily provide much for
 * creating such compositions of factories specifically but does have some
 * baseline features. Because these are intended to be user instantiated,
 * instead of being provided by some plugin the custom factories add themselves
 * to the multiton on instantiation. Also, the name of the factory is set on
 * instantiation unlike other factories which will typically have a predefined
 * name.
 */
template<class T>
class CustomFactory : public Factory<T>
{
  public:
    /*!
     * CustomFactory objects should ONLY be instantiated with new as they are
     * automatically added to the multiton which will delete its factories at
     * its end of life multiton will take responsibility for deleting th
     */
    CustomFactory<T>(std::string type_name, std::string base_factory,
        FactoryParams params=FactoryParams())
      : type_name(type_name)
    {
      Factories<T>& factories=Factories<T>::getInstance();
      Factory<T>* factory=factories[base_factory];
      this->factory=FactoryAndParams<T>(factory,params);
      factories.addFactory(*this);
    }



    std::string type()
    {
      return type_name;
    }

  protected:
    FactoryAndParams<T> factory;

  private:
    std::string type_name;
};


#endif /* FACTORY_H */
