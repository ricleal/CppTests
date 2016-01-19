/*
 * oop.cpp
 *
 *  Created on: Sep 4, 2015
 *      Author: ferrazlealrm@ornl.gov
 *
 *  OOP example of URL:
 *  scheme:[//domain[:port]][/]path
 */

#include <iostream>
#include <string>
#include <map>
#include <initializer_list> //C++11?

// Abstract class: cannot be instantiated
class URL {
protected:
	std::string domain = "ornl.gov";
	std::string port;
	std::string scheme;
	std::string build_url(const std::string &scheme,
			const std::string &port) const {
		return scheme + "://" + domain + ":" + port;
	}
public:
	// Pure virtual function: i.e. must be overridden by a derived class
	virtual std::string build_url() const = 0;
	~URL() {};
};

class Http: public URL {
public:
	Http() {port = "80"; scheme = "http";}
	std::string build_url() const {
		return URL::build_url(scheme, port);
	}
};

class Https: public URL {
public:
	Https() {port = "443"; scheme = "https";}
	std::string build_url() const {
		return URL::build_url(scheme, port);
	}
};

class Ftp: public URL {
public:
	Ftp() {port = "20"; scheme = "ftp";}
	std::string build_url() const {
		return URL::build_url(scheme, port);
	}
};

/**
 * Let's imagine that I want to add a path to the URL: http://ornl.gov:80/<path>
 * I don't need to modify the code! Open/closed principle.
 * Just extend it, i.e., add new code.
 */

class HttpWithPath: public Http {
protected:
	std::string path;
public:
	HttpWithPath(std::string path) : Http(), path(path) {}
	std::string build_url() const {
		std::string default_url = URL::build_url(scheme, port);
		return default_url + "/" + path;
	}
};

/**
 * Sort of factory
 */
template <class T>
class Registry{
private:
	std::map<std::string, T*> choices;
public:
	void register_entry( std::initializer_list< std::pair<const std::string, T*> > list_of_pairs){
	    for( auto elem : list_of_pairs ){
	        std::cout << "Registering: " << elem.first << std::endl ;
	        choices.insert(list_of_pairs.begin(), list_of_pairs.end());
	    }
	}
	// Given a string, returns an object
	T* get(const std::string &name){
		return choices[name];
	}
};

/**
 * Main function
 */
std::string build_url(const URL &url) {
	return url.build_url();
}

int main_oop(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Use " + std::string(argv[0]) + " [http, https, ftp]"
				<< std::endl;
		exit(-1);
	}
	std::string scheme = argv[1];

	// UGLY!!!
	// In real world I would have here some sort of better Dependency Injection:
	Http http; Https https; Ftp ftp;
	Registry<URL> reg;
	reg.register_entry({std::make_pair("http", &http),
		std::make_pair("https", &https), std::make_pair("ftp", &ftp)});

	if (scheme == "http" or scheme == "https" or scheme == "ftp") {
		URL *url = reg.get(scheme);
		std::cout << "Built URL: " << build_url(*url) << std::endl;
	} else {
		std::cerr << "Scheme not valid. Use of these: http, https, ftp"
				<< std::endl;
	}
	return 0;
}
