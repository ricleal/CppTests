/**
 * RVO: Return value optimization and NRVO: Named return value optimization
 *
 * Trying to get the last line of this to work...
 *
 * Still creates a new object when I assign m14 = fChangeClassRetRef(m14); :(
 *
 * I guess this is a problem with the compiler itself.
 *
 */

#include <iostream>

using namespace std;

class VOpt {
	int x;
public:
	VOpt() :
			x(0) {
		cout << "\t -> Default Constructor" << endl;
	}
	VOpt(int i) :
			x(i) {
		cout << "\t -> Parameter Constructor" << endl;
	}
	VOpt(const VOpt& other) :
			x(other.x) {
		cout << "\t -> Copy Constructor" << endl;
	}
	// Two existing objects!
	VOpt& operator=(const VOpt& other) {
		x = other.x;
		cout << "\t -> Copy Assignment Operator" << endl;
		return *this;
	}
	//C++11
	VOpt(VOpt&& other) {
		x = std::move(other.x);
		cout << "\t -> C++11 Move Constructor" << endl;
	}
	//C++11
	VOpt& operator=(VOpt&& other) {
		x = std::move(other.x);
		cout << "\t -> C++11 Move Operator" << endl;
		return *this;
	}

	void setX(int x) {
		this->x = x;
	}

	friend ostream& operator<<(ostream &out, const VOpt &m);
};

ostream& operator<<(ostream &out, const VOpt &m) {
	out << "\t -> VOpt.x=" << m.x << endl;
	return out;
}

// Dummy func to show C++11 move  constructor
VOpt fCpp11Move(VOpt m) {
	m.setX(1000);
	return m;
}

// create class and return
VOpt fNewClassParam(int x) {
	VOpt m(x);
	return m;
}

// return new class
VOpt fNewClass() {
	return VOpt(11);
}

// Change the value of the class, return ref!
VOpt& fChangeClassRetRef(VOpt &m) {
	m.setX(21);
	return m;
}

// Change the value of the class, return ref!
VOpt fChangeClassRetValue(VOpt &m) {
	m.setX(21);
	return m;
}

int main_rvo_nrvo(void) {
	cout << "VOpt m1(1);" <<endl;
	VOpt m1(1);

	cout << "VOpt m1_2 = VOpt(1);" <<endl;
	VOpt m1_2 = VOpt(1);

	cout << "VOpt m2 = m1;" <<endl;
	VOpt m2 = m1; //copy

	cout << "VOpt &m2_2 = m1;" <<endl;
	VOpt &m2_2 = m1; //No copy constructor involved!

	cout << "VOpt &&m2_3 = VOpt(1);" <<endl;
	//VOpt &&m2_3 = m1; //This is illegal
	VOpt &&m2_3 = VOpt(1);


	cout << "VOpt m3(m1);" <<endl;
	VOpt m3(m1); //copy
	cout << "VOpt m4" <<endl;
	VOpt m4;
	cout << "m4 = m1;" <<endl;
	m4 = m1; //Assignment

	cout << "VOpt m5(fCpp11Move(VOpt()));" <<endl;
	VOpt m5(fCpp11Move(VOpt())); //Move Contructor C++11

	cout << "VOpt m6;" <<endl;
	VOpt m6;
	cout << "m6 = VOpt();" <<endl;
	m6 = VOpt();

	cout << "-------- Optimisation 1 ---------" << endl;
	cout << "VOpt m7 = fNewClassParam(10);" <<endl;
	VOpt m7 = fNewClassParam(10);
	cout << "cout << m7;" <<endl;
	cout << m7;

	cout << "-------- Optimisation 2 ---------" << endl;
	cout << "VOpt m8 = fNewClass();" <<endl;
	VOpt m8 = fNewClass();
	cout << "cout << m8;" <<endl;
	cout << m8;

	cout << "-------- Optimisation 3 ---------" << endl;
	cout << "const VOpt &m9 = fNewClassParam(12);" <<endl;
	const VOpt &m9 = fNewClassParam(12);
	cout << "cout << m9;" <<endl;
	cout << m9;

	// Does not work! lvalue must be const!
	// fCpp11Move() returns a temporary object (i.e., rvalue) and only lvalues can be bound to references to non-const.
	cout << "-------- Optimisation 4 ---------" << endl;
	cout << "-- This doesn't work: " << endl;
	cout << "-- VOpt &m10 = fNewClass(); " << endl;
	cout << "-- This works: " << endl;
	cout << "const VOpt &m10 = fNewClass(); " << endl;
	const VOpt &m10 = fNewClass();

	cout << "-------- NO Optimisation 5 ---------" << endl;
	cout << "VOpt m11(15);" <<endl;
	VOpt m11(15);
	cout << "VOpt m12 = fChangeClassRetRef(m11);" <<endl;
	VOpt m12 = fChangeClassRetRef(m11); // :( Copy constructor

	cout << "m12 = fChangeClassRetRef(m12);" <<endl;
	m12 = fChangeClassRetRef(m12); // :( Copy Assignement Operator
	cout << "cout << m12;" <<endl;
	cout << m12;

	cout << "VOpt &m12_2 = fChangeClassRetRef(m11);" <<endl;
	VOpt &m12_2 = fChangeClassRetRef(m11); // :( Copy constructor

	cout << "-------- Optimisation 6 ---------" << endl;
	cout << "VOpt m13(15);" <<endl;
	VOpt m13(15);
	cout << "cout << m13;" <<endl;
	cout << m13;
	cout << "VOpt &m14 = fChangeClassRetRef(m13);" <<endl;
	VOpt &m14 = fChangeClassRetRef(m13); // if function return ref this is OK! NO COPY!
	cout << "cout << m13  << m14;" <<endl;
	cout << m13 << m14;
	cout << "m11.setX(10);" <<endl;
	m11.setX(10);
	cout << "m14 = fChangeClassRetRef(m11);" <<endl;
	m14 = fChangeClassRetRef(m11);
	cout << "cout << m14 << m11;" <<endl;
	cout << m14 << m11;

	cout << "m14 = fChangeClassRetValue(m11);" <<endl;
	m14 = fChangeClassRetValue(m14);

	cout << "VOpt m15 = fChangeClassRetValue(m14);" <<endl;
	VOpt m15 = fChangeClassRetValue(m14);
	cout << "cout << m14 << m15;" <<endl;
	cout << m14 << m15;
	cout << "m15.setX(1213);" <<endl;
	m15.setX(1213);
	cout << "cout << m14 << m15;" <<endl;
	cout << m14 << m15;

	cout << "const VOpt &m16 = fChangeClassRetValue(m14);" <<endl;
	const VOpt &m16 = fChangeClassRetValue(m14);
	cout << "cout << m14 << m16;" <<endl;
	cout << m14 << m16;
	cout << "m14.setX(1213);" <<endl;
	m14.setX(1213);
	cout << "cout << m14 << m16;" <<endl;
	cout << m14 << m16;

	return 0;
}
