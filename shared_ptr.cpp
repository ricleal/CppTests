#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

class myClass {
public:
	myClass(int);
	~myClass();
	int getI(){return i;}
private:
	int i;
};

// constructor
myClass::myClass(int x) :
		i(x) {
	std::cout << "*** Calling: " << BOOST_CURRENT_FUNCTION << std::endl;
	std::cout << "Contructor init: " << x << " --> " << this->i << std::endl;
}
myClass::~myClass(){
	std::cout << "*** Calling: " << BOOST_CURRENT_FUNCTION << std::endl;
	std::cout << "Bye... " << this->i<< std::endl;
}

int main_shared() {
	myClass my_class(10);

	// dynamic
	myClass* my_class_ptr = new myClass(20);
	delete my_class_ptr;

	// auto just compiles with flag: -std=c++0x
	auto p1 = boost::make_shared<myClass>(1);
	std::cout << "p1: " << p1->getI() << std::endl;

	auto p2 = boost::shared_ptr<myClass>(new myClass(2));
	std::cout << "p2: " << p2->getI() << std::endl;

	boost::shared_ptr<myClass> p3 = boost::make_shared<myClass>(3);
	std::cout << "p3: " << p3->getI() << std::endl;

	const int n = static_cast<int>(p3->getI());
	std::cout << "n: " << n << std::endl;


	return 0;
}
