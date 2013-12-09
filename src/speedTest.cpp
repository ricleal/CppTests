// constructing vectors
#include <iostream>
#include <vector>
#include <valarray>

// C++11
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds milliseconds;

int main_speed() {

	std::cout << "Main has started!" << std::endl;

	Clock::time_point t0 = Clock::now();

	int nSpectra = 12 * 32 * 256;
	int nBinsTotal = nSpectra * 512;

	std::vector<double> total; //(nBinsTotal);

	for (int i = 0; i < nBinsTotal; i++) {
		double res = 500 * 500 + i;
		total.push_back(res);
	}

	Clock::time_point t1 = Clock::now();
	milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);

	//std::cout << ms.count() << "ms\n";
	std::cout.precision(2);
	std::cout << "Total time: " << std::fixed << ms.count() * 1e-3 << " seconds"<< std::endl;


	// 2
	t0 = Clock::now();
	std::valarray<double> total2 (nBinsTotal);
	for (int i=0; i<nBinsTotal; i++)
		total2 = i;

	std::valarray<double> total3 (nBinsTotal,500 * 500);

	total2 = total2 + total3;

	t1 = Clock::now();
	ms = std::chrono::duration_cast<milliseconds>(t1 - t0);

	//std::cout << ms.count() << "ms\n";
	std::cout.precision(2);
	std::cout << "Total time: " << std::fixed << ms.count() * 1e-3 << " seconds"<< std::endl;











	std::cout << "Main has finished!" << std::endl;
	return 0;
}
