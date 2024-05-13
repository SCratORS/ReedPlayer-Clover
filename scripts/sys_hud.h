#pragma once

#include "../WorldNode.h"

class sys_hud:public WorldNode
{
private:
	std::vector<WorldNode *> elementList = {};
	int orgX = 0;
	int orgY = 0;
	int VGap = 0;
	int sizeX = 0;
	int sizeY = 0;
public:
	sys_hud(Json::Value);
	void start(WorldNode *);
	void refresh();
	Point getSize();
};