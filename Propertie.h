#pragma once

#include <string>
#include <json/json.h>

class Propertie
{
public:
	Propertie(Json::Value);
	std::string linkType;
	std::string linkId;
};