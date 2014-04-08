#ifndef FACTORY_H
#define FACTORY_H 

#include <string>
#include <vector>

#include "BeepHive.h"

template<class T>
class Factory
{
  public:
    //static virtual Factory<T>* getInstance() = 0;

    virtual std::string type() = 0;

    virtual T* create() = 0;
    virtual T* create(std::vector<std::string> params) = 0;
};



template<class T>
class Factories
{
  public:
    typedef typename Map<Factory<T>*>::iterator iterator;

    static Factories<T>& getInstance()
    {
      static Factories<T> instance;
      return instance;
    }



    Factory<T>* getFactory(std::string name)
    {
      return factories[name];
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

  private:
    Factories<T>() {};
    Map<Factory<T>*> factories;
};
    

#endif /* FACTORY_H */
