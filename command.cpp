#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
#include <map>
#include <cctype>
#include <limits.h>

/**
 *
 * Command design pattern.
 * Based on: http://www.dreamincode.net/forums/topic/38412-the-command-pattern-c/
 */

// Base interface for the Command
class Converter {
public:
	virtual std::string convert(int) = 0;
	virtual ~Converter() {
	}
};

// Commands to call
class HexConverter: public Converter {
public:
	std::string convert(int i) {
		std::stringstream ss;
		ss << std::hex << i;
		return ss.str();
	}
};

class OctConverter: public Converter {
public:
	std::string convert(int i) {
		std::stringstream ss;
		ss << std::oct << i;
		return ss.str();
	}
};

class BinConverter: public Converter {
public:
	std::string convert(int i) {
		std::bitset<sizeof(i) * CHAR_BIT> bits(i);
		std::stringstream ss;
		ss << bits;
		return ss.str();
	}
};



class ConverterDictionary {
public:
	ConverterDictionary() {
		dict.insert(std::make_pair('B', new BinConverter));
		dict.insert(std::make_pair('O', new OctConverter));
		dict.insert(std::make_pair('H', new HexConverter));
	}

	Converter* lookup(char x) {
		std::map<char, Converter*>::const_iterator iter = dict.find(toupper(x));
		if (iter != dict.end())
			return iter->second;
		else
			return NULL;
	}
	~ConverterDictionary() {
		while (dict.begin() != dict.end()) {
			delete dict.begin()->second;
			dict.erase(dict.begin());
		}
	}
private:
	std::map<char, Converter*> dict;

};

int main_command() {
	//using namespace std;

	ConverterDictionary dict;
	int num = 10;

	Converter* con = dict.lookup('H');
	std::cout << num << " -> " << con->convert(num) << std::endl;

	con = dict.lookup('B');
	std::cout << num << " -> " << con->convert(num) << std::endl;

	con = dict.lookup('O');
	std::cout << num << " -> " << con->convert(num) << std::endl;

}
