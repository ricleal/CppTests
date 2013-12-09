// constructing vectors
#include <iostream>
#include <vector>
#include <valarray>

// C++11
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliseconds;

const int SIZE = 10000000;

std::vector<double> fillVec1() {
	std::vector<double> v(SIZE);
	for (std::size_t i = 0; i < v.size(); i++)
		v[i] = i;
	return v;
}

std::vector<double> fillVec2(std::vector<double> &v) {
	for (std::size_t i = 0; i < v.size(); i++)
		v[i] = i;
	return v;
}

static Clock::time_point t0;

void tic() {
	t0 = Clock::now();
}
void toc() {
	Clock::time_point t1 = Clock::now();
	milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);

	std::cout.precision(2);
	std::cout << "Total time: " << std::fixed << ms.count() * 1e-3 << " seconds"
			<< std::endl;

}

int main_speedtestvector() {

	std::cout << "Main has started!" << std::endl;

	tic();
	std::vector<double> v1;
	v1 = fillVec1();
	toc();

	tic();
	std::vector<double> v2(SIZE);
	std::vector<double> v3 = fillVec2(v2);
	toc();

	std::cout << "Main has finished!" << std::endl;
	return 0;
}
