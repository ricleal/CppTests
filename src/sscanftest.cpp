#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>


int main_sscanfTest() {

	std::string s("123 3434 frfrf 121212 12");

	int v1 = -1, v2 = -1;

	std::stringstream sstm;
	sstm << "%" << 10 << "d %" << 10 << "d";
	std::string pattern = sstm.str();

	sscanf(s.c_str(), pattern.c_str(), &v1, &v2);

	std::cout << "s -> " << s << std::endl;
	std::cout << "v1 -> " << v1 << std::endl;
	std::cout << "v2 -> " << v2 << std::endl;

	return 0;
}
