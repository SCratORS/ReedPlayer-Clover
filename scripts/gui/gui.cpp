#include "gui.h"

#include <iostream>
#include <ostream>

gui::gui(Json::Value json): ScriptComponent(json) {

}

void gui::start(GUIManager * manager) {
	if (this->manager) error(std::string("Trying to start GUI manager, but one already exists ('") + manager->worldNode->getName() + std::string("')"));
	
	this->manager = manager;

	if (manager->hasAutomaticNavigation) hasAutomaticNavigation = manager->hasAutomaticNavigation;
	if (manager->dragThresholdX) dragThresholdX = manager->dragThresholdX;
	if (manager->dragThresholdY) dragThresholdY = manager->dragThresholdY;
	if (manager->roundedUnits) roundedUnits = manager->roundedUnits;
	if (manager->repeatDelay) REPEAT_DELAY = manager->repeatDelay;
	if (manager->repeatRate) REPEAT_RATE = manager->repeatRate;

	reset();
	setInputCamera(manager->inputCamera);
}


void gui::debugPrint(std::string text, std::string level){
	if (level=="" || DEBUG_LEVEL[level])
		std::cout << "<GUI> " << text << std::endl;

}

void gui::error(std::string text){
	std::cout << "<GUI> <ERROR> " << text << std::endl;
}

void gui::reset() {
	pressedCommandTarget = NULL;
	focusedElement = NULL;
	buttonTable = {};
}

void gui::setInputCamera(CameraComponent * camera) {
	std::cout << "***TO-DO(GUI): function setInputCamera() don't created" << std::endl;
	this->camera = camera;
	//Point p = getScreenSize(camera->getTargetScreen());
}

void gui::registerButton(GUIButton * button) {
	buttonTable[button] = true;
}

