#include "simple_factory.h"

#include <cassert>
#include <iostream>


struct Base {
  virtual ~Base() {}
  virtual int answer() const = 0;
};

struct A : Base {
  virtual int answer() const { return 42; }
};


int main_simpleFactory() {
  kniht::SimpleFactory<Base> f;
  f.define<A>("A");

  assert(f.create("A")->answer() == 42);

  try {
    f.define<A>("A");
    std::cerr << "error: define(\"A\") did not throw\n";
    assert(false);
  }
  catch (std::invalid_argument&) {
	  std::cout << "Got the exception" << std::endl;
  }

  return 0;
}
