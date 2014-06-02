#ifndef SINGLETON_H
#define SINGLETON_H 

/*!
 * An abstract singleton class
 *
 * Private constructors and such prevent accidental copying and force the
 * singletons to be singletons
 */
template<class T>
class Singleton
{
  public:
    static T& getInstance()
    {
      static T instance;
      return instance;
    }

  protected:
    Singleton<T>() {}

  private:
    Singleton<T>(const Singleton<T>& copy) {}
    Singleton<T>& operator=(const Singleton<T>& copy) {}
};

#endif /* SINGLETON_H */
