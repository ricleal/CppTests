/*
 * peakdet.cpp
 *
 *  Created on: Jan 23, 2013
 *      Author: leal
 */

#include <iostream>
#include <vector>
#include <string>
#include <limits>

std::vector<int> peakSearch(std::vector<int> v, int delta=10) {

	std::vector<int> maxPositions;
	std::vector<int> minPositions;

	int mn = std::numeric_limits<int>::max();
	int mx = std::numeric_limits<int>::min();
	int mnpos = -1, mxpos = -1;

	bool lookformax = true;

	for (unsigned int i = 0; i < v.size(); i++) {
		int thisV = v[i];
		if (thisV > mx) {
			mx = thisV;
			mxpos = i;
		}
		if (thisV < mn) {
			mn = thisV;
			mnpos = i;
		}

		if (lookformax) {
			if (thisV < mx - delta) {
				maxPositions.push_back(mxpos);
				mn = thisV;
				mnpos = i;
				lookformax = false;
			}
		} else {
			if (thisV > mn + delta) {
				minPositions.push_back(mnpos);
				mx = thisV;
				mxpos = i;
				lookformax = true;
			}
		}
	}

	return maxPositions;
}

int main_peakDetect() {
	std::vector<int> v = {0,1,2,1,0,0,0,0,0,0,0,2,0,0,0,0,0,1,0,2,0,0,1,0,0,0,0,1,0,1,3,1,1,0,0,0,1,0,0,0,2,2,0,0,0,0,0,1,1,0,0,1,1,3,0,0,1,0,1,1,1,0,0,0,0,1,0,0,0,2,0,0,1,0,1,1,0,0,1,0,0,1,1,0,0,1,1,3,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,1,1,0,0,1,0,1,0,0,0,0,0,0,0,0,3,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0,2,0,0,1,0,0,0,1,0,1,0,0,1,1,0,0,0,0,0,0,4,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,1,1,1,1,0,0,0,0,0,626,39315,84129,75125,35981,4709,103,61,33,16,8,10,2,5,2,1,3,1,2,0,0,2,1,0,1,1,1,0,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,0,1,0,1,2,2,3,1,1,1,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,1,2,1,0,0,2,2,1,0,0,0,1,0,0,0,1,1,0,1,0,0,1,1,0,0,0,1,0,1,1,1,0,0,1,0,1,0,0,0,1,0,1,1,0,0,0,1,0,0,0,2,0,0,0,0,0,2,0,1,0,0,1,1,0,0,0,1,1,1,0,0,0,0,1,0,0,2,0,626,39315,84129,75125,35981,4709,103,61,33,16,8,10,2,5,2,1,3,1,2,0,0,2,1,0,1,1,1,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,0,2,1,0,0,0,1,0,1,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,2,1,1,1,1,1,0,0,0,0,0,0,0,1,2,0,0,2,1,1,0,0,0,1,0,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,0,1,1,0,0,2,1,0,0,0,0,2,0,0,0,0,1,0,0,1,0,0,0,0,0,0,2,1,0,1,1,0,0,1,2,0,0,0,0,0};

	std::vector<int> peakPost = peakSearch(v);

	for (auto i: peakPost)
		std::cout << "Peaks : " << i << " -> " << (i>0?v[i]:std::numeric_limits<int>::min()) << std::endl;

	return 0;

}
