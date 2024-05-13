#pragma once

#include <map>
#include <string>

#include "../WorldNode.h"


class dbgMenu
{
private:
	std::map<std::string, WorldNode *>entrys;
public:
	dbgMenu();
	void entry(std::string, WorldNode *);
};