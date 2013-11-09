/*
 * parser.cpp
 *
 *  Created on: 9 Nov 2013
 *      Author: leal
 */
#include <iostream>
#include <vector>
#include <boost/lexical_cast.hpp>

#include <boost/algorithm/string/erase.hpp>
#include <string>

class Parser {
public:
	Parser() {
	}
	virtual ~Parser() {
	}

	/**
	 * Hope compiler supports the NRVO and does not return a copy of the std::vector<T> outVec;
	 */
	template<typename T> std::vector<T> parseFixedSizeField(
			const std::string &s, int fieldWidth) {
		std::vector<T> outVec;
		size_t pos = 0;
		while (pos + fieldWidth <= s.length()) {
			std::string subs = s.substr(pos, fieldWidth);
			boost::algorithm::erase_all(subs, " ");
			//std::cout << subs << std::endl;
			try {
				T value = boost::lexical_cast<T>(subs);
				outVec.push_back(value);
			} catch (boost::bad_lexical_cast &) {
				outVec.push_back(0);
			}
			pos += fieldWidth;
		}
		return outVec;
	}
};

int main() {
	Parser p;
	std::vector<int> v = p.parseFixedSizeField<int>(" 123  23  12 111", 4);
	for (auto i = v.begin(); i != v.end(); ++i)
		std::cout << *i << ", ";
	std::cout << std::endl;

	std::vector<float> v2 = p.parseFixedSizeField<float>(
			" 123.000  23.1e2  12.122 111.e23", 8);
	for (auto i = v2.begin(); i != v2.end(); ++i)
		std::cout << *i << ", ";
	std::cout << std::endl;

	return 0;
}
