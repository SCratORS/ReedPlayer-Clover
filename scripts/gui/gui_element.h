#pragma once

#include <string>
#include "../../WorldNode.h"

class GUIElement: public WorldNode
{
public:
	class states {

	};
	bool isGUIElement = false;
	bool hvc_only = false;
	bool nes_only = false;
	std::string currentState = "";
	GUIElement(Json::Value);
	void start(WorldNode *);
};