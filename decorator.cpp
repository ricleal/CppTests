#include <iostream>

/*
 * http://www.codeproject.com/Articles/99469/Learn-Decorator-Design-Pattern-in-Easy-Steps
 */

class Kelvin {
public:
	virtual ~Kelvin() {
		std::cout << "Kelvin Dtor\n";
	}
	virtual void MisBehave() {
		std::cout << "Hi, I am Kelvin the Great!\n";
	}
};

class KelvinDecorator: public Kelvin {
public:

	virtual ~KelvinDecorator() {
		delete kelvinComponent;
	}

	KelvinDecorator(Kelvin *kelvinArgument) :
			kelvinComponent(kelvinArgument) {
	}

	virtual void MisBehave() {
		kelvinComponent->MisBehave();
	}

private:
	Kelvin *kelvinComponent;
	KelvinDecorator();
};


class SpacemanDecorator: public KelvinDecorator {
public:
	virtual ~SpacemanDecorator() {
		std::cout << "Spaceman Dtor\n";
	}

	SpacemanDecorator(Kelvin *kelvin) :
			KelvinDecorator(kelvin) {
	}

	virtual void MisBehave() {
		KelvinDecorator::MisBehave();

		//now add this decorator's additional functionality
		std::cout << "The fearless Spaceman Kpiff battles with the Zork!!!\n";
	}

private:
	SpacemanDecorator();
};

class DinoDecorator: public KelvinDecorator {
public:
	virtual ~DinoDecorator() {
		std::cout << "Dino Dtor\n";
	}

	DinoDecorator(Kelvin *kelvin) :
			KelvinDecorator(kelvin) {
	}

	virtual void MisBehave() {
		// call previous decorator
		KelvinDecorator::MisBehave();

		//now add this decorator's additional functionality
		std::cout
				<< "Kelvin the terrible T-Rex runs rampant in Jurassic park!\n";
	}

private:
	DinoDecorator();
};

class TracerBazookaDecorator: public KelvinDecorator {
public:
	virtual ~TracerBazookaDecorator() {
		//std::cout << "Tracer Dtor\n";
	}

	TracerBazookaDecorator(Kelvin *kelvin) :
			KelvinDecorator(kelvin) {
	}

	virtual void MisBehave() {
		// call previous decorator
		KelvinDecorator::MisBehave();

		//now add this decorator's additional functionality
		std::cout << "TracerBazooka: Here's looking at you kid.\n";
	}

private:
	TracerBazookaDecorator();
};

int main_decorator() {
	Kelvin *mainComponent = new Kelvin();

	KelvinDecorator *pAddedFunctionality = new SpacemanDecorator(
			new DinoDecorator(new TracerBazookaDecorator(mainComponent)));

	pAddedFunctionality->MisBehave();

	delete pAddedFunctionality;

	return 0;
}

