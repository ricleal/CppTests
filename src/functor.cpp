// transform algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::transform
#include <vector>       // std::vector
#include <functional>   // std::plus
#include <string>

int op_increase(int i) {
	return ++i;
}

template<typename V>
void print(std::string name, V vec) {
	std::cout << name << ": ";
	for (auto i : vec)
		std::cout << i << " ";
	std::cout << std::endl;
}

int main_functor() {
	std::vector<int> vector1;
	std::vector<int> vector2;

	// set some values:
	for (int i = 1; i < 6; i++)
		vector1.push_back(i * 10); // 10 20 30 40 50
	print("Vector1", vector1);

	vector2.resize(vector1.size()); // allocate space
	print("Vector2", vector2);

	//
	std::transform(vector1.begin(), vector1.end(), vector2.begin(),
			op_increase);

	std::cout << " * op_increase: vec2 = vec1 + 1" << std::endl;
	print("Vector1", vector1);
	print("Vector2", vector2);

	// std::plus adds together its two arguments:
	std::transform(vector1.begin(), vector1.end(), vector2.begin(),
			vector1.begin(), std::plus<int>());

	std::cout << " * plus: vec1 = vec1 + vec2" << std::endl;
	print("Vector1", vector1);
	print("Vector2", vector2);

	std::transform(vector2.begin(), vector2.end(), vector2.begin(),
			op_increase);

	std::cout << " * op_increase: vec2 = vec2 + 1" << std::endl;
	print("Vector1", vector1);
	print("Vector2", vector2);

	return 0;
}
