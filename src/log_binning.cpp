#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>

/*
g++  main.cpp -o test -std=c++11 -stdlib=libc++ && ./test
*/

/**
Same as scipy:
# Example: Qmin = 0.1 ; Qmax=1; 10 bins
In [4]: np.logspace(np.log10(0.1), np.log10(1), 10, base=10)
Out[4]:
array([ 0.1       ,  0.12915497,  0.16681005,  0.21544347,  0.27825594,
        0.35938137,  0.46415888,  0.59948425,  0.77426368,  1.        ])
Same here returns:
0.1 0.129155 0.16681 0.215443 0.278256 0.359381 0.464159 0.599484 0.774264 1
*/
std::vector<double> logBinning(double min, double max, int num)
{
    std::vector<double> outBins(num);
    min = log10(min);
    max = log10(max);
    double binWidth = fabs((max - min) / (num - 1));
    for (int i = 0; i <= num; ++i)
    {
	outBins[i] = pow(10, min + i * binWidth);
    }
    return outBins;
}

int main()
{
    std::vector<double> v = logBinning(0.1, 1, 10);
    std::cout << "--- out:" << std::endl;
    for (auto i : v)
		std::cout << i << ' ';
    std::cout << '\n';

    return 0;
}
