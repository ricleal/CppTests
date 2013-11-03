#include <iostream>
#include <vector>
#include <cstddef>

using namespace std;

int main_pointer(void) {

	// m × n matrix / m-by-n matrix
	// m rows / n collumns
	const int m = 5;
	const int n = 10;

	// Both do the same:
	int *p = new int[n * m];
	//int *p = new int(n * m * sizeof(int));

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int pos = j + i * n;
			p[pos] = pos + 1;
			cout << p[pos] << "\t";
		}
		cout << endl;
	}

	cout << "p[0] -> " << *p << "\t=\t" << p[0] << endl;
	cout << "p[1] -> " << *(p + 1) << "\t=\t" << p[1] << endl;
	cout << "p[9] -> " << *(p + 9) << "\t=\t" << p[9] << endl;

	// Test pointers to pointers
	int **pp = &p; /* pointer to a pointer */
	int *entry = p;

	cout << "*p\t= " << *p << endl;
	cout << " p\t= " << p << endl;
	cout << "&p\t= " << &p << endl;
	cout << "**pp\t= " << **pp << endl;
	cout << "*pp\t= " << *pp << endl;
	cout << "pp\t= " << pp << endl;
	cout << "*entry\t= " << *entry << endl;
	cout << " entry\t= " << entry << endl;

	for (int i = 0; i < 3; i++) {
		cout << *(p+i) << " = " << *((*pp)+i) << " = " << *(entry+i) << " ; ";
	}
	cout << endl;
}

