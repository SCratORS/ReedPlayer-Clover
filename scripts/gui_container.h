#pragma once

#include "gui/gui_element.h"
#include "../WorldNode.h"
#include "gui/gui_layout.h"


class gui_container:public GUIElement
{
private:
	WorldNode * elements = NULL;
public:
	std::string neighborDirection = "";
	std::vector<WorldNode *> elementArray = {};
	std::string layoutType = "";
	std::string elementType = "";

	bool setListener = false;
	WorldNode * current = NULL;
	WorldNode * focus = NULL;
	GUILayout * layout;
	int HGap = 0;
	int VGap = 0;
	bool autoGap = false;
	bool autoPosition = false;
	int repeatedTimes = 0;

	gui_container(Json::Value);
	void buildElements(WorldNode *);
	void start(WorldNode *);
};