/*
 * RapidXmlWrapper.h
 *
 *  Created on: 7 sep. 2018
 *      Author: lucio
 */

#ifndef HEADERS_RAPIDXMLWRAPPER_H_
#define HEADERS_RAPIDXMLWRAPPER_H_

#pragma once
#include <string>
#include <map>
#include <vector>
#include "rapidxml.hpp"

using namespace std;

class RapidXmlWrapper {
public:
    RapidXmlWrapper(){}
public:
    static rapidxml::xml_node<>* getNodeByName(const string& nodeName, rapidxml::xml_node<>* parentNode);
    static rapidxml::xml_node<>* getNodeByNameAndAttribute(const string& nodeName, const string& attrName, const string& attribValue, rapidxml::xml_node<>* node);
    static string getAttributeValue(const std::string& attributeName, rapidxml::xml_node<>* node);
    static map<string, vector<string>> getParamMapsFromNode(rapidxml::xml_node<>* node);
};

#endif /* HEADERS_RAPIDXMLWRAPPER_H_ */
