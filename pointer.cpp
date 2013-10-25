#include <iostream>
#include <vector>
#include <cstddef>

using namespace std;

/**
 *
 * Compile as C++11
 *
 *
 * Just a test with C pointers and copy values to vector
 *
 *
 */

//0 3 6
//1 4 7
//2 5 8
int main_pointer(void) {

	const int m = 5;
	const int n = 10;
	int *p = new int[n * m]; // Allocate n ints and save ptr in a.
	//int *p = new int(n * m * sizeof(int)); // Allocate n ints and save ptr in a.


	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int pos = j + i * n;
			p[pos] = pos + 1; // Initialize all elements to zero.
			cout << pos << "\t";
		}
		cout << endl;
	}

	cout << "0 -> " << *p << endl;
	cout << "1 -> " << *(p + 1) << endl;
	cout << "9 -> " << *(p + 9) << endl;

	vector<int> v(p, (p + n * m));
//	vector<int> v;
//
//	for (int i = 0; i < m; i++) {
//		for (int j = 0; j < n; j++) {
//			int pos = j + i * n;
//			cout << p[pos] << "\t";
//			int tmp = p[pos];
//			v.push_back(tmp);
//			//v[pos]=tmp;
//		}
//		cout << endl;
//	}

	//delete p;

	for (auto i : v)
		cout << i << " ";
	cout << endl;

	return 0;
}
