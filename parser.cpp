/*
 * parser.cpp
 *
 *  Created on: 9 Nov 2013
 *      Author: leal
 */
#include <iostream>
#include <fstream>

#include <vector>
#include <string>
#include <map>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/erase.hpp>

class ILLParser {
public:
	ILLParser(const std::string &filename) {
		fin.open(filename);
	}
	virtual ~ILLParser() {
		if (fin != NULL) {
			fin.close();
		}
	}

	/**
	 * Main function
	 */
	void startParsing() {
		std::string line;
		while (std::getline(fin, line)) {
			if (line.find(
					"RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR")
					!= std::string::npos) {
				parseFieldR();
			} else if (line.find(
					"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA")
					!= std::string::npos) {
				parseFieldA();
			} else if (line.find(
					"IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII")
					!= std::string::npos) {
				parseFieldNumeric(header, intWith);
			} else if (line.find(
					"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")
					!= std::string::npos) {
				parseFieldNumeric(header, floatWith);
			} else if (line.find(
					"SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS")
					!= std::string::npos) {
				startParseSpectra();
			}
		}
	}

	/**
	 * Parse fields of type R
	 */
	void parseFieldR() {
		std::string line;
		std::getline(fin, line);
		std::vector<std::string> parsedLineFields = splitLineInFixedWithFields(
				line, intWith);
		header["NRUN"] = parsedLineFields[0];
		header["NTEXT"] = parsedLineFields[1];
		header["NVERS"] = parsedLineFields[2];
	}

	void parseFieldA() {
		std::string line;
		std::getline(fin, line);
		std::vector<std::string> parsedLineFields = splitLineInFixedWithFields(
				line, intWith);
		// I'm not using this for now
		//int numberOfCharsToRead = evaluate<int>(parsedLineFields[0]);
		int numberOfLinesToRead = evaluate<int>(parsedLineFields[1]);
		std::string key;
		std::string value("");
		std::getline(fin, key);
		for (int i = 0; i < numberOfLinesToRead; i++) {
			std::getline(fin, line);
			value += line;
		}
		header[key] = value;
	}

	/**
	 * Parses a field of numeric type and puts the result in a map
	 */
	void parseFieldNumeric(std::map<std::string, std::string> &header,
			int fieldWith) {
		std::string line;
		std::getline(fin, line);
		int nNumericFields = -1, nTextLines = -1;
		sscanf(line.c_str(), "%d %d", &nNumericFields, &nTextLines);

		std::vector<std::string> keys(nNumericFields);
		std::vector<std::string> values(nNumericFields);
		int index = 0;
		for (int i = 0; i < nTextLines; i++) {
			std::getline(fin, line);
			std::vector<std::string> s = splitLineInFixedWithFields(line,
					fieldWith);
			for (auto it = s.begin(); it != s.end(); ++it) {
				keys[index] = *it;
				index += 1;
			}
		}
		// parse numeric fields
		int pos = 0;
		index = 0;
		while (pos < nNumericFields) {
			std::getline(fin, line);
			std::vector<std::string> s = splitLineInFixedWithFields(line,
					fieldWith);
			pos += s.size();
			for (auto it = s.begin(); it != s.end(); ++it) {
				values[index] = *it;
				index += 1;
			}
		}

		std::vector<std::string>::const_iterator iKeys;
		std::vector<std::string>::const_iterator iValues;
		for (iKeys = keys.begin(), iValues = values.begin();
				iKeys < keys.end() && iValues < values.end();
				++iKeys, ++iValues) {
			if (*iValues != "" && *iKeys != "") {
				header[*iKeys] = *iValues;
			}
		}

	}

	/**
	 * Parses the spectrum
	 */
	std::vector<int> parseFieldISpec(int fieldWith = intWith) {
		std::string line;
		std::getline(fin, line);
		int nSpectra;
		sscanf(line.c_str(), "%d", &nSpectra);
		std::vector<int> spectrumValues(nSpectra);

		int nSpectraRead = 0, index = 0;
		while (nSpectraRead < nSpectra) {
			std::getline(fin, line);
			std::vector<std::string> s = splitLineInFixedWithFields(line,
					fieldWith);
			nSpectraRead += s.size();
			for (auto it = s.begin(); it != s.end(); ++it) {
// THIS TAKES 2 SEC. With sscanf a few ms...
//				try {
//					boost::algorithm::erase_all(*it, " ");
//					spectrumValues[index] = boost::lexical_cast<int>(*it);
//
//				} catch (const boost::bad_lexical_cast& e) {
//					std::cerr << "ERROR lexical cast to int: " << e.what()
//							<< '\n';
//					spectrumValues[index] = 0;
//				}
				sscanf(it->c_str(),"%d",&spectrumValues[index]);

				index += 1;
			}
		}
		return spectrumValues;
	}

	void showHeader() {
		for (auto it = header.begin(); it != header.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "List of spec headers: " << spectraHeaders.size() << '\n';
		std::vector<std::map<std::string, std::string> >::const_iterator s;
		for (s = spectraHeaders.begin(); s != spectraHeaders.end(); ++s) {
			std::map<std::string, std::string>::const_iterator it;
			for (it = s->begin(); it != s->end(); ++it)
				std::cout << it->first << " => " << it->second << '\n';
		}

		std::vector<std::vector<int> >::const_iterator l;
		for (l = spectraList.begin(); l != spectraList.end(); ++l) {
			std::cout << " => " << l->size() << '\n';

		}

	}

	void startParseSpectra() {
		std::string line;
		std::getline(fin, line);
//		int spectraNumber, spectraRemaing, spectraTotal;
//		sscanf(line.c_str(), "%d %d %d", &spectraNumber, &spectraRemaing,
//				&spectraTotal);
		while (std::getline(fin, line)) {
			if (line.find(
					"IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII")
					!= std::string::npos) {
				spectraList.push_back(parseFieldISpec());

			} else if (line.find(
					"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")
					!= std::string::npos) {
				spectraHeaders.push_back(std::map<std::string, std::string>());
				parseFieldNumeric(spectraHeaders.back(), floatWith);
//
//				for (auto it = spectraHeaders[pos].begin(); it != spectraHeaders[pos].end(); ++it)
//								std::cout << it->first << " * => " << it->second << '\n';

			} else if (line.find(
					"SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS")
					!= std::string::npos) {
				std::getline(fin, line);
//				sscanf(line.c_str(), "%d %d %d", &spectraNumber,
//						&spectraRemaing, &spectraTotal);
////				std::cout << line << std::endl;
//				std::cout << spectraNumber << " ; " << spectraRemaing << " ; "
//						<< spectraTotal << std::endl;

			}

		}

	}

	void doNothing() {

	}

//		void parseNumericSection(int fieldWith) {
//			std::string line;
//			std::getline(fin, line);
//			int nNumericFields = -1, nTextLines = -1;
//			sscanf(line.c_str(), "%d %d", &nNumericFields, &nTextLines);
//
//			if (nTextLines > -1) {
//				// parse text lines first
//				// concatenate them in header
//				std::string header;
//				for (int i; i < nTextLines; i++) {
//					std::getline(fin, line);
//					header += line;
//				}
//				// parse numeric fields
//				int pos = 0;
//				std::vector<std::string> out;
//				while (pos < nNumericFields) {
//					std::getline(fin, line);
//					out = parseFixedSizeField<T>(line, fieldWith);
//					pos += out.size();
//				}
//
//				//std::cout << out[0] << std::endl;
//			} else {
//				// We are on a spectrum!
//			}
//		}

	template<typename T> std::vector<T> parseFixedSizeField(
			const std::string &s, int fieldWidth) {
		std::vector<T> outVec;
		size_t pos = 0;
		while (pos + fieldWidth <= s.length()) {
			std::string subs = s.substr(pos, fieldWidth);
			boost::algorithm::erase_all(subs, " ");
			//std::cout << subs << std::endl;
			try {
				T value = boost::lexical_cast<T>(subs);
				outVec.push_back(value);
			} catch (boost::bad_lexical_cast &) {
				outVec.push_back(0);
			}
			pos += fieldWidth;
		}
		return outVec;
	}

	/**
	 * Splits a line in fixed length fields.
	 */
	std::vector<std::string> splitLineInFixedWithFields(const std::string &s,
			int fieldWidth, int lineWitdh = 80) {
		size_t outVecSize = lineWitdh / fieldWidth;
		std::vector<std::string> outVec(outVecSize);
		size_t pos = 0, posInVec = 0;
		while (pos + fieldWidth <= s.length()) {
			std::string subs = s.substr(pos, fieldWidth);
			if (subs.find_first_not_of(' ') != std::string::npos) {
				// not empty substring
				outVec[posInVec] = subs;
				posInVec += 1;
			} else {
				// delete not necessary entries
				outVec.erase(outVec.begin() + posInVec);
			}
			pos += fieldWidth;
		}
		return outVec;
	}

	template<typename T>
	T evaluate(std::string field) {
		boost::algorithm::erase_all(field, " ");
		//std::cout << subs << std::endl;
		T value;
		try {
			value = boost::lexical_cast<T>(field);
		} catch (boost::bad_lexical_cast &e) {
			throw e;
		}
		return value;
	}

private:
// each line being padded out to exactly 80 characters of text.
//static const int lineWith = 80;
	static const int intWith = 8;
	static const int floatWith = 16;

	std::ifstream fin;

	std::map<std::string, std::string> header;
	std::vector<std::map<std::string, std::string> > spectraHeaders;
	std::vector<std::vector<int> > spectraList;

};

int main() {

	ILLParser p("/net/serdon/illdata/data/d2b/exp_5-21-1076/rawdata/123944");
	p.startParsing();
	p.showHeader();
//	std::vector<std::string> s =
//			p.splitLineInFixedWithFields(
//					"  0.50700000E+05                                                                ",
//					16);
//	for (auto i : s)
//		std::cout << " -> '" << i << "'" << std::endl;

	std::cout << "Done!" << std::endl;
	return 0;
}
