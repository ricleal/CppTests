/*
 * clean_architecture.cpp
 *
 *  Created on: May 29, 2013
 *      Author: leal
 *
 * Flow:
 *
 */

#include <iostream>
#include <string>
#include <memory>
#include <fstream>

class IUseCaseOutputPort {
public:
	virtual void print(std::string message) = 0;
	virtual ~IUseCaseOutputPort() {
	}
	;
};

// 2 Presenters
class HtmlPresenter: public IUseCaseOutputPort {
public:
	void print(std::string message) {
		std::cout << "<p>" << message << "</p>" << std::endl;
	}
};

class TextPresenter: public IUseCaseOutputPort {
public:
	void print(std::string message) {
		std::cout << message << std::endl;
	}
};

//
class IUseCaseInputPort {
public:
	virtual std::string read() = 0;
	virtual ~IUseCaseInputPort() {
	}
	;
};

// specific UseCaseInteractor for reading text from the stdin
class UseCaseInteractorForInputFromStdIn: public IUseCaseInputPort {
public:
	std::string read() {
		std::string message;
		std::cout << "Please input some text!" << std::endl;
		std::getline(std::cin, message);
		return message;
	}
};

// specific UseCaseInteractor for reading text from a dummy file
class UseCaseInteractorForInputFromDummyFile: public IUseCaseInputPort {
public:
	std::string read() {
		const std::string filename = "/proc/meminfo";
		std::string message = readFile(filename);
		return message;
	}
private:
	std::string readFile(const std::string filename) {
		std::string line;
		std::string lines;
		std::ifstream myfile(filename);
		if (myfile.is_open()) {
			while (myfile.good()) {
				getline(myfile, line);
				lines += line + '\n';
			}
			myfile.close();
		} else {
			lines = "Unable to open file";
		}
		return lines;
	}
};

// Controller
class ControllerForReading {
public:
	std::string readFromStdIn() {
		input = std::make_shared<UseCaseInteractorForInputFromStdIn>();
		std::string out = "This text was read from the stdin:\n";
		out += input->read();
		return out;
	}
	std::string readFromFile() {
		input = std::make_shared<UseCaseInteractorForInputFromDummyFile>();
		std::string out = "This text was read from the a file:\n";
		out += input->read();
		return out;
	}
private:
	std::shared_ptr<IUseCaseInputPort> input;
};

// main represents the outer shell
int main_clean_architecture() {
	std::cout << "Main started!" << std::endl;

	ControllerForReading c;
	const std::string textFromStdin = c.readFromStdIn();
	const std::string textFromFile = c.readFromFile();

	auto output = std::make_shared<HtmlPresenter>();
	output->print(textFromStdin);
	output->print(textFromFile);

	auto output2 = std::make_shared<TextPresenter>();
	output2->print(textFromStdin);
	output2->print(textFromFile);

	std::cout << "Main ended!" << std::endl;
	return 0;
}
