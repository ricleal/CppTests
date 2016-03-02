/*
 * main.cpp
 *
 *  Created on: Dec 9, 2013
 *      Author: leal
 */
#include <iostream>

int main_array_initialisation();
int main_return_opt();
int main_unzip(int argc, char** argv);
int main_parser();
int main_sscanfTest();
int main_test_tree(int argc, char **argv);
int main_map_performance(int argc, char **argv);
int main_xml_poco(int argc, char*argv[]);
int main_non_oop(int argc, char* argv[]);
int main_oop(int argc, char* argv[]);
int main_xml_poco2(int argc, char*argv[]);

int main(int argc, char** argv) {
	std::cout << "Starting..." << std::endl;

	main_xml_poco2(argc,argv);

	std::cout << "Done!" << std::endl;
	return 0;
}


