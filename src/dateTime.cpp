/*
 * SingletonHolder.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: leal
 */

#include <iostream>
#include <boost/date_time.hpp>
#include <string>

using namespace std;

/***
 *
 *
 */
std::string getDateTimeInIsoFormat(std::string dateToParse) {
	namespace bt = boost::posix_time;

	// parsing format
	const std::locale format = std::locale(std::locale::classic(),
			new bt::time_input_facet("%d-%b-%y %H:%M:%S"));

	bt::ptime pt;

	std::istringstream is(dateToParse);
	is.imbue(format);
	is >> pt;

	if (pt != bt::ptime()) {
		std::string s = bt::to_iso_extended_string(pt);
		return s;
	}
	return "";
}

int main_datetime() {

	std::string s = getDateTimeInIsoFormat("29-Jun-12 11:27:26");
	std::cout << "Time in ISO is " << s << '\n';
	return 0;

}
