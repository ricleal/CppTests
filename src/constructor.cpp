#include <iostream>
#include <vector>
#include <cstddef>

using namespace std;

class MyClass {
	int x;
public:
	MyClass() :
			x(0) {
		cout << "Default Constructor" << endl;
	}
	MyClass(int i) :
			x(i) {
		cout << "Parameter Constructor" << endl;
	}
	MyClass(const MyClass& other) :
			x(other.x) {
		cout << "Copy constructor" << endl;
	}
	// Two existing objects!
	MyClass& operator=(const MyClass& other) {
		x = other.x;
		cout << "Assignment operator" << endl;
		return *this;
	}
};

int main_constructor(void) {
	MyClass m1(1);
	MyClass m2 = m1; //copy
	MyClass m3(m1); //copy
	MyClass m4;
	m4 = m1; //Assignment

	return 0;
}
