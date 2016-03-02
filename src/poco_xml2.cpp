/*
 * poco_xml.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: rhf
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/NodeList.h>
#include <Poco/DOM/NodeFilter.h>
#include <Poco/DOM/NodeIterator.h>
#include <Poco/DOM/Node.h>
#include <Poco/DOM/Text.h>
#include <Poco/AutoPtr.h>
#include <Poco/SAX/InputSource.h>
#include <Poco/DOM/NamedNodeMap.h>
#include <Poco/DOM/CDATASection.h>

#include <boost/algorithm/string.hpp>


std::vector<std::map<std::string, std::string> > contents;

int main_xml_poco2(int argc, char*argv[]) {

	std::string fileName =
			"/SNS/VULCAN/IPTS-16013/0/80834/preNeXus/VULCAN_80834_cvinfo.xml";

	std::ifstream in(fileName);
	Poco::XML::InputSource src(in);
	Poco::XML::DOMParser parser;
	Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parse(&src);

	//"Poco::XML::NodeFilter::SHOW_ALL" filter applied, all node types(Element, Text, CDataSection, etc)
	//Poco::XML::NodeIterator it(pDoc, Poco::XML::NodeFilter::SHOW_ALL);
	//Poco::XML::NodeIterator it(pDoc, Poco::XML::NodeFilter::SHOW_CDATA_SECTION);
	Poco::XML::NodeIterator it(pDoc,
			Poco::XML::NodeFilter::SHOW_CDATA_SECTION
					| Poco::XML::NodeFilter::SHOW_ELEMENT);
	Poco::XML::Node* pNode = it.nextNode();

	while (pNode) {

		if (pNode->nodeType() == pNode->ELEMENT_NODE) {
			std::cout << pNode->nodeName() << std::endl;
		}
		else if (pNode->nodeType() == pNode->CDATA_SECTION_NODE) {
			std::string value = pNode->nodeValue();
			boost::algorithm::trim(value);
			std::cout << "\t\t" <<  value << std::endl;
		}
		// Show attributes
		if (pNode->hasAttributes()) {
			Poco::XML::NamedNodeMap* attributes = pNode->attributes();
			for (unsigned int i = 0; i < attributes->length(); i++) {
				Poco::XML::Node* attribute = attributes->item(i);
				std::cout << "\t" << attribute->nodeName() << " : "
						<< attribute->nodeValue() << std::endl;
			}
		}
		pNode = it.nextNode();
	}
	return 0;
}

