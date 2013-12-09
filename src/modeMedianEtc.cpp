/*
 * modeMedianEtc.cpp
 *
 *  Created on: Jan 25, 2013
 *      Author: leal
 */

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>

using namespace std;

template<typename T> vector<T> mode(vector<T> &data);
template<typename T> float median(vector<T> &data);
template<typename T> double mean(vector<T> &data);

/**
 *
 * For random:
 *
 */

struct gen_rand {
	double range;
public:
	gen_rand(double r = 1.0) :
			range(r) {
	}
	double operator()() {
		return (rand() / (double) RAND_MAX) * range * 10;
	}
};

int main_mode(int argc, char *argv[]) {
	// Function declaration

//	const int num_items = 100;
//	std::vector<int> data(num_items);
//	std::generate_n(data.begin(), num_items, gen_rand());
//
//	sort(data.begin(), data.end());
//	cout << "Data Set: ";
//	unsigned int j;
//	for (j = 0; j < data.size(); j++) {
//		printf("%i ", data[j]);
//	}
//	cout << endl;
//
//	printf("Mean: %f Median: %f, Mode: ", mean(data), median(data));
//	vector<int> tmp = mode(data);
//	unsigned int i;
//
//	for (i = 0; i < tmp.size(); i++) {
//		printf("%i ", tmp[i]);
//	}
//	printf("\n");
//

	std::vector<int> data;
	data.push_back(254);
	data.push_back(254);
	vector<int> tmp = mode(data);
	std::cout << "Size: " << tmp.size() << std::endl;

	return 0;

}

template<typename T> vector<T> mode(vector<T> &data) {
	vector<T> tmp_vector;

	if (data.size() > 0) {
		sort(data.begin(), data.end());
		vector<int>::iterator i;
		i = data.begin();

		int highest_mode = 0;
		int highest_mode_count = 0;
		int current_mode = 0;
		int current_count = 0;

		// Iterate through the vector
		while (i != data.end()) {
			int tmp = *i;

			if (current_count == 0) {
				current_mode = tmp;
			}

			if (tmp == current_mode) {
				current_count++;
			} else if (tmp > current_mode) {

				// Check if the current mode is greater than the highest
				if (current_count > highest_mode_count) {
					// Make the current mode the highest
					highest_mode = current_mode;
					highest_mode_count = current_count;

					// Clear the vector
					tmp_vector.clear();

					// Add the highest value to the vector
					tmp_vector.push_back(highest_mode);

					// Set current to tmp
					current_mode = tmp;
					current_count = 1;
				}

				// In case multiple modes
				else if (current_count == highest_mode_count) {
					// Set the highest mode to current
					highest_mode = current_mode;
					highest_mode_count = current_count;

					// Add the current mode to the vector
					tmp_vector.push_back(current_mode);

					current_mode = tmp;
					current_count = 1;
				}

				else {
					// Set tmp to current
					current_mode = tmp;
					current_count = 1;
				}
			} else {
				// Shouldn't need to do anything if tmp < current_mode
			}

			i++;
		}
	}

	return tmp_vector;
}

template<typename T> float median(vector<T> &data) {
	if (data.size() > 0) {
		// Sort the data
		sort(data.begin(), data.end());

		// Handle the even cases
		if ((data.size() % 2) == 0) {
			// To get the median value sum the 2 medians and get the average
			float sum = 0;

			sum += data[data.size() / 2];
			sum += data[(data.size() / 2) - 1];

			return (sum / 2);
		}

		// Handle the odd cases
		else {
			return data[data.size() / 2];
		}
	}

	return 0;
}

template<typename T> double mean(vector<T> &data) {
	if (data.size() > 0) {
		vector<int>::iterator i;
		double sum = 0;

		// Iterate through all of the elements in the vector and sum them
		for (i = data.begin(); i != data.end(); i++) {
			sum += *i;
		}

		return sum / data.size();
	}

	return 0;
}

