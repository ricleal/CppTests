/**
 * unzip.cpp
 * A zcat replacement, for educational purpose.
 * Uses boost::iostream and zlib.
 *
 * Compile like this:
 *   g++ -o unzip unzip.cpp -lz -lboost_iostreams
 *
 * This code is published as public domain.
 */
#include <fstream>
#include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/shared_ptr.hpp>

class Parser {
public:
	virtual ~Parser() {
		std::cout << "Parser dead...\n";
	}

	Parser(std::string filename) {

		m_instream = openFile(filename);

	}

	void parse(){
		//Iterate lines
		std::string line;
		while (std::getline(*m_instream, line)) {
			std::cout << line << std::endl;
		}
	}
private:

	boost::shared_ptr<std::istream> m_instream;
	boost::shared_ptr<std::ifstream> m_file;
	boost::shared_ptr< boost::iostreams::filtering_streambuf<boost::iostreams::input> > m_inbuf;

	boost::shared_ptr<std::istream> openFile(const std::string &filename) {
		//Read from the first command line argument, assume it's gzipped
		boost::shared_ptr<std::ifstream> file( new std::ifstream(filename, std::ios_base::in | std::ios_base::binary) );
		m_file = file;
		boost::shared_ptr< boost::iostreams::filtering_streambuf<boost::iostreams::input> > inbuf(new boost::iostreams::filtering_streambuf<boost::iostreams::input>() );
		m_inbuf = inbuf;
		inbuf->push(boost::iostreams::gzip_decompressor());
		inbuf->push(*file);
		//Convert streambuf to istream
		boost::shared_ptr<std::istream> instream(new std::istream(inbuf.get()));

//		std::string line;
//		while (std::getline(*instream, line)) {
//			std::cout << line << std::endl;
//		}

		return instream;
	}

};

//int main_unzip(int argc, char** argv) {
//	if (argc < 2) {
//		std::cerr << "Usage: " << argv[0] << " <gzipped input file>"
//				<< std::endl;
//		return -1;
//	}
//	//Read from the first command line argument, assume it's gzipped
//
//	char *filepath = argv[1];
//
//	std::ifstream file(filepath, std::ios_base::in | std::ios_base::binary);
//	boost::iostreams::filtering_streambuf<boost::iostreams::input> inbuf;
//
//	if (boost::algorithm::ends_with(filepath, ".gz")
//			|| boost::algorithm::ends_with(filepath, ".GZ")) {
//		inbuf.push(boost::iostreams::gzip_decompressor());
//	}
//	inbuf.push(file);
//	//Convert streambuf to istream
//	std::istream instream(&inbuf);
//	//Iterate lines
//	std::string line;
//	while (std::getline(instream, line)) {
//		std::cout << line << std::endl;
//	}
//	//Cleanup
//	file.close();
//	return 0;
//}

int main_unzip(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <gzipped input file>"
				<< std::endl;
		return -1;
	}
	char *filepath = argv[1];
	Parser p(filepath);
	p.parse();

	return 0;
}
