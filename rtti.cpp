/*
 * rtti.cpp
 *
 *  Created on: Oct 9, 2012
 *      Author: leal
 */

#include <iostream>
#include <memory>

class Interface {
public:
	virtual void GenericOp() = 0; // pure virtual function
};

class SpecificClass1: public Interface {
public:
	SpecificClass1() {
	}
	;
	virtual void GenericOp() {
		std::cout << "GenericOp 1" << std::endl;
	}
	;
	virtual void SpecificOp() {
		std::cout << "SpecificOp 1" << std::endl;
	}
	;
	virtual ~SpecificClass1() {
		std::cout << "Bye Bye... " << typeid(this).name() << std::endl;
	}
	;
};

class SpecificClass2: public Interface {
public:
	SpecificClass2() {
	}
	;
	virtual void GenericOp() {
		std::cout << "GenericOp 2" << std::endl;
	}
	;
	virtual void SpecificOp() {
		std::cout << "SpecificOp 2" << std::endl;
	}
	;
	virtual ~SpecificClass2() {
		std::cout << "Bye Bye... " << typeid(this).name() << std::endl;
	}
	;
};

int main_rtti(void) {

	//**********************************************************
	Interface *i = new SpecificClass1();
	i->GenericOp();

	// This gives an error:
	//i->SpecificOp();
	// alternative
	SpecificClass1* new_i = dynamic_cast<SpecificClass1*>(i);
	new_i->SpecificOp();
	delete new_i;

	std::cout << "**********************************************************" << std::endl;
	//**********************************************************
	// RTTI
	Interface* ptr_interface;
	ptr_interface = new SpecificClass1();

	SpecificClass1* ptr_specific = dynamic_cast<SpecificClass1*>(ptr_interface);
	if (ptr_specific) {
		// our suspicions are confirmed -- it really was a SpecificClass
		std::cout << "This is a SpecificClass!" << std::endl;
		ptr_specific->SpecificOp();
	} else {
		// our suspicions were incorrect -- it is definitely not a SpecificClass.
		// The ptr_interface points to an instance of some other child class of the base InterfaceClass.
		std::cout << "This is NOT a SpecificClass!" << std::endl;

	};
	ptr_interface->GenericOp();
	//delete ptr_interface; // doesn't delete anything
	delete ptr_specific;

	std::cout << "**********************************************************" << std::endl;
	//**********************************************************
	// RTTI 2
	Interface* ptr_interface2;

	SpecificClass1* ptr_specific2 = dynamic_cast<SpecificClass1*>(ptr_interface2);
	if (ptr_specific2) {
		// our suspicions are confirmed -- it really was a SpecificClass
		std::cout << "This is a SpecificClass!" << std::endl;
		ptr_specific2->SpecificOp();
	} else {
		// our suspicions were incorrect -- it is definitely not a SpecificClass.
		// The ptr_interface points to an instance of some other child class of the base InterfaceClass.
		std::cout << "This is NOT a SpecificClass!" << std::endl;

	};

	//**********************************************************
	// same 1st example but with smart_pointers

	std::shared_ptr<Interface> shr_p;
	shr_p = std::make_shared<SpecificClass1>(); // same as new
	shr_p->GenericOp();

	// This gives an error:
	// shr_p->SpecificOp();
	// alternative
	// This make sense but doesn't work!!!
	//std::shared_ptr<SpecificClass1> new_shr_p = dynamic_cast<std::shared_ptr<SpecificClass1>>(shr_p);
	std::shared_ptr<SpecificClass1> new_shr_p = std::dynamic_pointer_cast<SpecificClass1>(shr_p);
	new_shr_p->SpecificOp();

	std::cout << "**********************************************************" << std::endl;
	return 0;


}

