/*
 * non_oop.cpp
 *
 *  Created on: Sep 4, 2015
 *      Author: ferrazlealrm@ornl.gov
 *
 *  Non OOP example of URL:
 *  scheme:[//domain[:port]][/]path
 */

#include <iostream>
#include <string>

std::string domain = "ornl.gov";
std::string http_port = "80";
std::string https_port = "443";
std::string ftp_port = "20";

std::string build_url(const std::string &scheme,
		const std::string &domain,
		const std::string &port) {
	return scheme + "://" + domain + ":" + port;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Use " + std::string(argv[0]) + " [http, https, ftp]"<<std::endl;
		exit(-1);
	}
	std::string scheme = argv[1];

	if (scheme == "http"){
		std::cout << build_url(scheme,domain,http_port) <<std::endl;
	}
	else if (scheme == "https"){
		std::cout << build_url(scheme,domain,https_port) <<std::endl;
	}
	else if (scheme == "ftp"){
		std::cout << build_url(scheme,domain,ftp_port) <<std::endl;
	}
	else {
		std::cerr << "Scheme not valid. Use of these: http, https, ftp"<<std::endl;
	}
	return 0;
}

