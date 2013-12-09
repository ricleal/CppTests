/*
 * doThis.cpp
 *
 *  Created on: Mar 5, 2013
 *      Author: leal
 */

#include <iostream>

struct ExecutorType {
	enum Type {
		mpi, thread, serial
	};
};

namespace Wrong {

class Mpi {
	ExecutorType::Type type;
public:
	Mpi() :
			type(ExecutorType::Type::mpi) {
	}
	virtual ~Mpi() {
	}
	;

	void exec() {
		std::cout << "Execution MPI : " << type << std::endl;
	}
};

class Thread {
	ExecutorType::Type type;
public:
	Thread() :
			type(ExecutorType::Type::thread) {
	}
	virtual ~Thread() {
	}
	;

	void exec() {
		std::cout << "Execution Thread : " << type << std::endl;
	}
};

class Serial {
	ExecutorType::Type type;
public:
	Serial() :
			type(ExecutorType::Type::serial) {
	}
	virtual ~Serial() {
	}
	;

	void exec() {
		std::cout << "Execution Serial : " << type << std::endl;
	}
};

void wrongExecutor(ExecutorType::Type type) {

	if (type == ExecutorType::Type::mpi) {
		Mpi m;
		m.exec();
	} else if (type == ExecutorType::Type::thread) {
		Thread t;
		t.exec();
	} else if (type == ExecutorType::Type::serial) {
		Serial s;
		s.exec();
	} else
		std::cout << "Wrong executor type" << std::endl;
}
}

////////////////////////////////////////

namespace Right {
class Executor {
protected:
	ExecutorType::Type type;
public:

	virtual void exec();
	virtual ~Executor();
	ExecutorType::Type getType() const {
		return type;
	}
	;
};

class Mpi: public Executor {
public:
	Mpi() {
		type = ExecutorType::Type::mpi;
	}
	virtual ~Mpi() {
	}
	;

	void exec() {
		std::cout << "Execution MPI : " << type << std::endl;
	}
};

class Thread: public Executor {
public:
	Thread() {
		type = ExecutorType::Type::thread;
	}
	virtual ~Thread() {
	}
	;
	void exec() {
		std::cout << "Execution Thread : " << type << std::endl;
	}
};

class Serial: public Executor {
public:
	Serial() {
		type = ExecutorType::Type::serial;
	}
	virtual ~Serial() {
	}
	;
	void exec() {
		std::cout << "Execution Serial : " << type << std::endl;
	}
};

void rightExecutor(Executor& e) {
	e.exec();
}

}

