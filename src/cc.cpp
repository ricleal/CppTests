#include <iostream>

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
        cout << "Copy Constructor" << endl;
    }
    // Two existing objects!
    MyClass& operator=(const MyClass& other) {
        x = other.x;
        cout << "Assignment Operator" << endl;
        return *this;
    }
    //C++11
    MyClass(MyClass&& other) {
    	x = std::move(other.x);
        cout << "Move Constructor" << endl;
    }
    //C++11
    MyClass& operator=(MyClass&& other) {
        x = std::move(other.x);
        cout << "Move Operator" << endl;
        return *this;
    }
};

// Dummy func to show C++11 move  constructor
MyClass fDoNothing(MyClass m) {
    return m;
}

int main_cc(int argc, char* argv[])  {
    cout << "argc = " << argc << endl; 
    for(int i = 0; i < argc; i++) 
        cout << "argv[" << i << "] = " << argv[i] << endl; 

    MyClass m1(1);
    MyClass m2 = m1; //copy
    MyClass m3(m1); //copy
    MyClass m4;
    m4 = m1; //Assignment

    cout << "* Move Contructor C++11" << endl;
    MyClass m5(fDoNothing(MyClass()));
    cout << "* Move Operator C++11" << endl;
    MyClass m6;
    m6 = MyClass();

    return 0;
}
