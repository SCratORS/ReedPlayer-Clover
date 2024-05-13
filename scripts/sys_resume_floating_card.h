#pragma once

#include "sys_resume_card.h"

class sys_resume_floating_card:public sys_resume_card
{
public:
	sys_resume_floating_card(Json::Value);
	void refresh();
	void start(WorldNode *);
};