/**
 *  Trying to figure out how to return huge objects when they are created
 *  inside a function or changed inside a function (i.e. avoiding copy constructors).
 *
 *  Code and output should be easy to understand.
 */

#include <iostream>

using namespace std;

class InnerDummy {

public:
	InnerDummy(){
		cout << "\t -> InnerDummy Default Constructor" << endl;
	}
	virtual ~InnerDummy() {
			cout << "\t -> InnerDummy desctructor" << endl;
		}

	InnerDummy(const InnerDummy& other) {
		cout << "\t -> InnerDummy Copy Constructor" << endl;
	}
	// Two existing objects!
	InnerDummy& operator=(const InnerDummy& other) {
		cout << "\t -> InnerDummy Copy Assignment Operator" << endl;
		return *this;
	}
	//C++11
	InnerDummy(InnerDummy&& other) {
		cout << "\t -> InnerDummy C++11 Move Constructor" << endl;
	}
	//C++11
	InnerDummy& operator=(InnerDummy&& other) {
		cout << "\t -> InnerDummy C++11 Move Operator" << endl;
		return *this;
	}

};


class Dummy {

public:
	Dummy() :
			x(0) {
		cout << "\t -> Default Constructor" << endl;
	}
	virtual ~Dummy() {
			cout << "\t -> desctructor" << endl;
		}
	Dummy(int i) :
			x(i) {
		cout << "\t -> Parameter Constructor" << endl;
	}
	Dummy(const Dummy& other) :
			x(other.x) {
		cout << "\t -> Copy Constructor" << endl;
	}
	// Two existing objects!
	Dummy& operator=(const Dummy& other) {
		x = other.x;
		cout << "\t -> Copy Assignment Operator" << endl;
		return *this;
	}
	//C++11
	Dummy(Dummy&& other) {
		x = std::move(other.x);
		cout << "\t -> C++11 Move Constructor" << endl;
	}
	//C++11
	Dummy& operator=(Dummy&& other) {
		x = std::move(other.x);
		cout << "\t -> C++11 Move Operator" << endl;
		return *this;
	}

	void setX(int x) {
		this->x = x;
	}

	void setInnerDummy(InnerDummy d){
		this->innerDummy = d;
	}

	InnerDummy getInnerDummyValue()  const {
		return this->innerDummy;
	}

	InnerDummy &getInnerDummyRef() {
		return this->innerDummy;
	}

	friend ostream& operator<<(ostream &out, const Dummy &m);

private:
	int x;
	InnerDummy innerDummy;
};

ostream& operator<<(ostream &out, const Dummy &m) {
	out << "\t   -> Dummy.x=" << m.x << endl;
	return out;
}


Dummy fRetClassValue() {
	return Dummy();
}

Dummy fRetClassValue(int x) {
	Dummy d = Dummy(x);
	return d;
}

// Cant't return references to local variables
//Dummy& fRetClassRef() {
//	return Dummy();
//}
//
//Dummy& fRetClassRef(int x) {
//	Dummy d = Dummy(x);
//	return d;
//}

/**
 * This will return a reference for the class passed by param
 * No copy constructors involved
 */
Dummy& fRetClassRef(Dummy &d) {
	return d;
}

Dummy& fRetClassRef(Dummy &d, int x) {
	d.setX(x);
	return d;
}

/**
 * This will return a copy for the class passed by param
 * Copy constructors involved!
 */
Dummy fRetClassValue(Dummy &d) {
	return d;
}

Dummy fRetClassValue(Dummy &d, int x) {
	d.setX(x);
	return d;
}

Dummy& f3(Dummy &m) {
    m.setX(21);
    return m;
}


int main_return_opt(void) {
	cout << "1........................." <<endl;
	Dummy d1 = fRetClassValue();
	cout << d1;
	Dummy d2 = fRetClassValue(2);
	cout << d2;

	cout << "1_2......................... (Need const to work!)" <<endl;
	const Dummy &d1_2 = fRetClassValue();
	cout << d1_2;
	const Dummy &d2_2 = fRetClassValue(22);
	cout << d2_2;

	cout << "2........................." <<endl;
	Dummy d3 = fRetClassRef(d1);
	cout << d3;
	Dummy d4 = fRetClassRef(d1,4);
	cout << d4;

	cout << "2_2........................." <<endl;
	Dummy &d3_2 = fRetClassRef(d1);
	cout << d3_2;
	Dummy &d4_2 = fRetClassRef(d1,42);
	cout << d4_2;

	cout << "3........................." <<endl;
	Dummy &d5 = fRetClassRef(d1);
	cout << d5;
	Dummy &d6 = fRetClassRef(d1,6);
	cout << "d1" << d1;
	cout << "d6" << d6;
	d6.setX(123);
	cout << "d1" << d1;
	cout << "d6" << d6;

	cout << "4........................." <<endl;
	const Dummy &d7 = fRetClassValue(d1);
	cout << d7;
	const Dummy &d8 = fRetClassValue(d1,7);
	cout << "d1" << d1;
	cout << "d8" << d8;
	d6.setX(1234);
	cout << "d1" << d1;
	cout << "d8" << d8;

	cout << "5........................." <<endl;
	Dummy d9(1);
	InnerDummy id1;
	d9.setInnerDummy(id1);
	cout << " --- copy const:" << endl;
	const InnerDummy id2 = d9.getInnerDummyValue();
	cout << " --- copy const:" << endl;
	const InnerDummy &id3 = d9.getInnerDummyValue();
	cout << " --- No copy const:" << endl;
	const InnerDummy &id4 = d9.getInnerDummyRef();


	cout << "END ........................." <<endl;

	return 0;
}
