#pragma once

#include "../WorldNode.h"

class sys_resume_float_wing:public WorldNode
{
public:
	sys_resume_float_wing(Json::Value);
	void start(WorldNode *);
};