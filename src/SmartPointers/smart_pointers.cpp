#include <iostream>
#include <memory>
#include <numeric>
#include <chrono>

/**
* OSX:
* Compile as: g++ -std=c++1y smart_pointers.cpp -o smart_pointers
*
*/
class A {
private:
int value;
public:
A() : value(0)
{
};
A(int i) : value(i)
{
};
~A()
{
};
};

void test()
{
	// Regular pointer
	A *a = new A();
	delete a;
	// Same:
	std::shared_ptr<A> b = std::make_shared<A>();
	auto c = std::make_shared<A>();
	// Same:
	std::shared_ptr<A> d = std::make_shared<A>();
	auto e = std::make_shared<A>();
}

int main_smart_pointers()
{
	std::cout << "Main started." << std::endl;
  auto start = std::chrono::system_clock::now();
	test();
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> diff = end-start;
	std::cout << "Main ended: " << diff.count() << " ticks." << std::endl;
	return 0;
}
