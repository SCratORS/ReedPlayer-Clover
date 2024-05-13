#include "gui_element.h"
#include <iostream>
#include <ostream>


GUIElement::GUIElement(Json::Value json): WorldNode(json) {
	isGUIElement = true;
}

void GUIElement::start(WorldNode * parent)
{
	std::cout << "***TO-DO(GUIElement): function start() need modifed" << std::endl;
	currentState = "none";
}