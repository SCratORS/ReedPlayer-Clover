#include "Component.h"
#include <iostream>

Component::Component(Json::Value node) {
	try {
		id = node["id"].asString();
		type = node["type"].asString();
		enabled = node["enabled"].asBool();
		scriptType = node["scriptType"].asString();
	} catch (const std::exception& ex) {
		std::cout << "***ERROR(Component): Except in propertie: " << id << std::endl;
	}
}

Component::~Component() {

}

Component::Propertie * Component::getPropByName(std::string propName) {
	std::map <std::string, Propertie>::iterator i = properties.find(propName);
	return (i == properties.end())?NULL:&i->second;
}