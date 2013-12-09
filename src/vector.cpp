// my first program in C++

#include <iostream>
#include <vector>

void v1() {
	int n = 10;
	std::vector<std::vector<int> > v(n, std::vector<int>(n));

	int k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			v[i][j] = k;
			k++;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << v[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//dynamicly allocated
void v2() {
	int n = 10;
	std::vector<std::vector<int> > v;

	int k = 0;
	for (int i = 0; i < n; i++) {
		v.push_back(std::vector<int>());
		for (int j = 0; j < n; j++) {
			v[i].push_back(k);
			k++;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << v[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main_vector() {
	std::cout << "Main Started!" << std::endl;
	std::cout << "* v1" << std::endl;
	v1();
	std::cout << "* v2" << std::endl;
	v2();
	std::cout << "Main Ended!" << std::endl;
	return 0;
}
