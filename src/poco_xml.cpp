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

/**
 *
 */
std::map<std::string, std::string> get_metadata(
		Poco::AutoPtr<Poco::XML::Document> &pDoc) {
	std::map<std::string, std::string> metadata;

	Poco::XML::NodeIterator it(pDoc, Poco::XML::NodeFilter::SHOW_ELEMENT);
	Poco::XML::Node* pNode = it.nextNode();

	while (pNode) {
		if (pNode->childNodes()->length() == 1
				&& pNode->nodeName() != "Detector") {
			std::string key = pNode->parentNode()->nodeName() + "/"
					+ pNode->nodeName();
			std::string value = pNode->innerText();
			auto to_insert = std::pair<std::string, std::string>(key, value);
			metadata.insert(to_insert);
		}
		pNode = it.nextNode();
	}
	return metadata;
}

std::string get_text_from_tag(Poco::AutoPtr<Poco::XML::Document> &pDoc,
		const std::string &xpath) {
	Poco::XML::NodeIterator it(pDoc, Poco::XML::NodeFilter::SHOW_ELEMENT);
	Poco::XML::Node* pNode = it.nextNode();
	Poco::XML::Node* detectorNode = pNode->getNodeByPath(xpath);
	std::string value("");
	if (detectorNode)
		value = detectorNode->innerText();
	return value;

}

std::map<std::string, std::string> get_attributes_from_tag(
		Poco::AutoPtr<Poco::XML::Document> &pDoc, const std::string &xpath) {
	std::map<std::string, std::string> attributes_map;
	Poco::XML::NodeIterator it(pDoc, Poco::XML::NodeFilter::SHOW_ELEMENT);
	Poco::XML::Node* pNode = it.nextNode();
	Poco::XML::Node* detectorNode = pNode->getNodeByPath(xpath);
	std::string value("");
	if (detectorNode) {
		Poco::XML::NamedNodeMap* attributes = detectorNode->attributes();
		for (unsigned int i = 0; i < attributes->length(); i++) {
			Poco::XML::Node* attribute = attributes->item(i);
			std::string key = attribute->nodeName();
			std::string value = attribute->nodeValue();
			auto to_insert = std::pair<std::string, std::string>(key, value);
			attributes_map.insert(to_insert);
		}
	}
	return attributes_map;
}

int main_xml_poco(int argc, char*argv[]) {

	std::string fileName = "/home/rhf/git/PythonCode/src/Xml/data.xml";

	std::ifstream in(fileName);
	Poco::XML::InputSource src(in);

	Poco::XML::DOMParser parser;
	Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parse(&src);

	std::map<std::string, std::string> metadata = get_metadata(pDoc);
	for (auto it = metadata.begin(); it != metadata.end(); it++) {
		std::cout << it->first << " = " << it->second << std::endl;
	}

	std::string data = get_text_from_tag(pDoc, "//Data/Detector");
	std::cout << data << std::endl;

	std::cout << "** get_attributes_from_tag //Data/Detector" << std::endl;
	std::map<std::string, std::string> attributes = get_attributes_from_tag(
			pDoc, "//Data/Detector");
	for (auto it = attributes.begin(); it != attributes.end(); it++) {
		std::cout << it->first << " = " << it->second << std::endl;
	}

	std::cout << "** get_attributes_from_tag //Motor_Positions/selector_speed" << std::endl;
	attributes = get_attributes_from_tag(pDoc,"//Motor_Positions/selector_speed");
	for (auto it = attributes.begin(); it != attributes.end(); it++) {
		std::cout << it->first << " = " << it->second << std::endl;
	}
	std::cout << "** get_attributes_from_tag /" << std::endl;
	attributes = get_attributes_from_tag(pDoc,"/");
	for (auto it = attributes.begin(); it != attributes.end(); it++) {
		std::cout << it->first << " = " << it->second << std::endl;
	}

	return 0;
}

