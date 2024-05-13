#pragma once

#include "gui_container.h"

class sys_homemenu:public gui_container
{
public:
	sys_homemenu(Json::Value);
	void start(WorldNode *);
};