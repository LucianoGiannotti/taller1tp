/*
 * exampleRapidXML.cpp
 *
 *  Created on: 7 sep. 2018
 *      Author: lucio
 */

#include "RapidXmlWrapper.h"
#include <sstream>

/**
* Gets a node object from given node name and parent node.
*/
rapidxml::xml_node<>* RapidXmlWrapper::getNodeByName(const string& nodeName,
		rapidxml::xml_node<>* parentNode) {
    if(parentNode == NULL) {
        // parent node must not be null
        ostringstream errorBuilder;
        errorBuilder << " parentNode object should not be null: ";
        throw runtime_error(errorBuilder.str());
    }

   rapidxml::xml_node<>* node = parentNode->first_node();

   while(node != NULL) {
      if(node->name() == nodeName) {
         return node;
      }

      node = node->next_sibling();
   }
   return NULL;
}

/**
* Get node object from given node name, attribName, attribValue and parent node.
*/
rapidxml::xml_node<>* RapidXmlWrapper::getNodeByNameAndAttribute(const string& nodeName,
		const string& attrName, const string& attribValue, rapidxml::xml_node<>* parentNode) {
    if(parentNode == NULL) {
        // parent node must not be null
        ostringstream errorBuilder;
        errorBuilder << " parentNode object should not be null: ";
        throw runtime_error(errorBuilder.str());
    }

    rapidxml::xml_attribute<>* attr = parentNode->first_attribute(attrName.c_str());
    if( (attr != NULL) && (attr->value() == attribValue) && (parentNode->name() == nodeName)) {
        return parentNode;
    }

    rapidxml::xml_node<>* node = parentNode->first_node();

    while(node != NULL) {
        if(node->name() == nodeName) {
            // If attribute name and value empty then return node
            if(attrName.empty() || attribValue.empty()) {
                return node;
            }
            else {
                rapidxml::xml_attribute<>* attr = node->first_attribute(attrName.c_str());
                if( (attr != NULL) && (attr->value() == attribValue) ) {
                    return node;
                }
            }
        }
        node = node->next_sibling();
    }
    return NULL;
}

/**
* Get attribute value from given attribute name and given node object.
*/
string RapidXmlWrapper::getAttributeValue(const std::string& attributeName,
		rapidxml::xml_node<>* node) {
    string attributValue = "";

    if(node == NULL) {
        // throw This node must be initialized
        ostringstream errorBuilder;
        errorBuilder << "node object should not be null,for attribute name:"
        		+ string(attributeName);
        throw runtime_error(errorBuilder.str());
    }

    rapidxml::xml_attribute<>* attribute = node->first_attribute(attributeName.c_str());
    if(NULL == attribute) {
        ostringstream errorBuilder;
        errorBuilder << "Attribute not found, for attribute name:" + attributeName;
        throw runtime_error(errorBuilder.str());
    }
    attributValue = attribute->value();
    return attributValue;
}

/**
* Devuelve un diccionario con clave el nombre del nodo y valor un vector de atributos
* ex: <Employees>
        <Employee Name="John" Age="30"/>
        <Employee Name="Harry" Age="27"/>
        <Employee Name="Kate" Age="29"/>
*     </Employees>
*
*    Method will result the map of Employees with Name and age as key value pairs
*/
map<string, vector<string>> RapidXmlWrapper::getParamMapsFromNode(rapidxml::xml_node<>* node) {
   map<string, vector<string>> paramsMap;

   if(node == NULL) {
      // This node must be initialized
       ostringstream errorBuilder;
       errorBuilder << "node object should not be null";
       throw runtime_error(errorBuilder.str());
   }


   //Itero por nodos
   for(rapidxml::xml_node<>* currNode = node->first_node();
		   currNode != NULL; currNode = currNode->next_sibling()) {
      string nodeName = currNode->name();
      vector<string> atributos;

      //itero por atributos y saco los nombres
      for (rapidxml::xml_attribute<>* currAtribute = currNode->first_attribute();
    		  currAtribute != NULL; currAtribute = currAtribute->next_attribute()) {
    	  atributos.push_back(currAtribute->value());
      }
      paramsMap.insert(pair<string, vector<string>>(nodeName, atributos));
   }

   return paramsMap;
}


