#ifndef simple_factory_h
#define simple_factory_h

// Copyright (c) 2009 Roger Pate. See LICENSE for details.

#include <map>
#include <memory>
#include <stdexcept>
#include <string>


namespace kniht {

template<class KeyT, class RTypeT, class CreatorT=RTypeT (*)()>
struct BasicFactory {
  typedef KeyT Key;
  typedef RTypeT RType;
  typedef CreatorT Creator;

  bool define(Key const& key, Creator v) {
    // Define key -> v relationship, return whether this is a new key.
    return _registry.insert(typename Registry::value_type(key, v)).second;
  }
  RType create(Key const& key) const {
    typename Registry::const_iterator i = _registry.find(key);
    if (i == _registry.end()) {
      throw std::invalid_argument(std::string(__PRETTY_FUNCTION__) + ": key not registered");
    }
    else {
      return RType(i->second());
    }
  }

private:
  typedef std::map<Key, Creator> Registry;
  Registry _registry;
};


template<class InterfaceT, class KeyT=std::string>
struct SimpleFactory {
  typedef InterfaceT Interface;
  typedef KeyT Key;
  typedef std::auto_ptr<Interface> RType;

  RType create(Key const& name) const {
    return _factory.create(name);
  }
  template<class Derived>
  void define(Key const& name) {
    bool new_key = _factory.define(name, &SimpleFactory::create_func<Derived>);
    if (not new_key) {
      throw std::invalid_argument(std::string(__PRETTY_FUNCTION__) + ": name already registered");
    }
  }

private:
  typedef RType (*Creator)();
  typedef BasicFactory<Key, RType, Creator> Factory;

  Factory _factory;

  template<class Actual>
  static RType create_func() {
    return RType(new Actual());
  }
};

} // kniht::

#endif
