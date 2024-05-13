#pragma once
#include <memory>
#include <cstddef>
#include <map>
#include <string>

#include <json/json.h>
#include <fstream>
#include <iostream>

struct resource
{
	std::string type;
	std::string path;
	std::string groupId;
};

class ResourcesCollect
{
public:
	ResourcesCollect(std::string resourcesFilePath);
	~ResourcesCollect();
	resource * getParam(std::string id);

private:
	std::map <std::string, resource> param;
};