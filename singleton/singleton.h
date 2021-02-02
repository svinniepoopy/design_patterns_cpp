#ifndef SINGLETON_H
#define SINGLETON_H

// creates a singleton of type T
template<typename T>
class singleton {
  private:
    singleton(const singleton&)=delete;
    singleton& operator=(const singleton)=delete;
  protected:
    singleton(){}
    virtual ~singleton(){}
  public:
    template<typename U>
    static T& get(const U& u) {
      static T instance{u};
      return instance;
    }

    static T& get() {
      static T instance;
      return instance;
    }
};

#endif // SINGLETON_H
