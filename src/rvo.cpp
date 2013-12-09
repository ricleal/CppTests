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
        cout << "Copy Assignment Operator" << endl;
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

    void setX(int x){
        this->x=x;
    }

    friend ostream& operator<< (ostream &out, const MyClass &m);
};

ostream& operator<< (ostream &out, const MyClass &m)
{
    out << "MyClass x=" << m.x << endl;
    return out;
}

// Dummy func to show C++11 move  constructor
MyClass f(MyClass m) {
    return m;
}

// create class and return
MyClass f1() {
    MyClass m(10);
    return m;
}

// return new class
MyClass f2() {
    return MyClass(11);
}

// Change the value of the class, return ref!
MyClass& f3(MyClass &m) {
    m.setX(21);
    return m;
}


int main_rvo(void) {
    MyClass m1(1);
    MyClass m2 = m1; //copy
    MyClass m3(m1); //copy
    MyClass m4;
    m4 = m1; //Assignment

    cout << "* Move Contructor C++11" << endl;
    MyClass m5(f(MyClass()));
    cout << "* Move Operator C++11" << endl;
    MyClass m6;
    m6 = MyClass();

    cout << "* Optimisation 1:" << endl;
    MyClass m7 = f1();
    cout << m7;
    cout << "* Optimisation 2:" << endl;
    MyClass m8 = f2();
    cout << m8;
    cout << "* Optimisation 3:" << endl;
    const MyClass &m9 = f1();
    cout << m9;
    // Does not work! lvalue must be const!
    // f() returns a temporary object (i.e., rvalue) and only lvalues can be bound to references to non-const.
    // cout << "Optimisation 4:" << endl;
    // MyClass &m10 = f2();
    // cout << m10;
    cout << "* NO Optimisation 5:" << endl;
    MyClass m11(15) ;
    cout << "  :( Copy constructor:" << endl;
    MyClass m12 = f3(m11);
    cout << "  :( Copy Assignement Operator:" << endl;
    m12 = f3(m12);

    cout << m12;
    cout << "* Optimisation 6:" << endl;
    MyClass m13(15) ;
    MyClass &m14 = f3(m11); // if function return ref this is OK! NO COPY!
    m14 = f3(m14);

    cout << m14;

    return 0;
}
