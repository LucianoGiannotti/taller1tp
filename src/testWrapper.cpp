/*
 * testWrapper.cpp
 *
 *  Created on: 7 sep. 2018
 *      Author: lucio
 */

#include "RapidXmlWrapper.h"
#include "rapidxml.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

int testWrapper(int argc, char **argv) {
	rapidxml::xml_document<> doc;
	ifstream theFile("/home/lucio/eclipse-workspace/Contraa/src/config.xml");

	stringstream buffer;
	buffer << theFile.rdbuf();
	theFile.close();
	string content(buffer.str());
	doc.parse<0>(&content[0]);
	cout << "Leyendo config.XML, nombre parentNode inicial: " <<  doc.first_node()->name() << endl;

	//Extraigo escenarios Map
	rapidxml::xml_node<>* escenarios_node = RapidXmlWrapper::getNodeByName("escenarios",doc.first_node());
	cout << "Extrayendo informacion de " << escenarios_node->name() << endl;
	rapidxml::xml_node<>* nivel1_node = RapidXmlWrapper::getNodeByName("nivel1",escenarios_node);

	cout << "Extrayendo informacion de " << nivel1_node->name() << endl;
	map<string, vector<string>> nivel1List = RapidXmlWrapper::getParamMapsFromNode(nivel1_node);
	//cout << nivel1_node->first_node() << endl;


	for (auto const& x : nivel1List) {

	    cout << x.first  // string (key)
	    		<< ": ";
	    for (auto const& x : x.second) {
	    	cout << x  << ", ";
	    }
	}
}
