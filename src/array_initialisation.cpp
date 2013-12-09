/*
 * array_initialisation.cpp
 *
 *  Created on: Apr 17, 2013
 *      Author: leal
 */

#include <iostream>
#include <vector>
#include <algorithm>    // std::generate
const int N = 10;

template <typename T>
class Increment {
private:
	T current;
	T step;
public:
	Increment(T start, T step) {
		current = start;
		this->step = step;
	}
	int operator()() {
		return current += step;
	}
};


int main_array_initialisation() {

	std::vector<int> vec(N);
	std::generate(vec.begin(), vec.end(), Increment<int>(10,2));

	for (auto i : vec) {
		std::cout << ' ' << i;
	}
	std::cout << std::endl;

//	std::generate(vec.begin(), vec.end(), UniqueNumberStart<10>);
//
//	for (auto i : vec) {
//		std::cout << ' ' << i;
//	}
//	std::cout << std::endl;

	return 0;

}

