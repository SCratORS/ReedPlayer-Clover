#include "gui_button.h"
#include <iostream>
#include <ostream>

#include "gui.h"

extern gui * GUI;

GUIButton::GUIButton(Json::Value json): GUIElement(json) {

}

void GUIButton::start(WorldNode * parent) {
	if (GUI->DEBUG_LEVEL["runtime"]) GUI->debugPrint(std::string("[") + this->getName() + std::string("]\tGUIButton:start()"));
	std::cout << "***TO-DO(GUIButton): inner functions not created" << std::endl;

	/*
	setupClickableArea();
	disableVisual(pressedVisual);
	setupAnimator(clickedAnimation);
	setupAnimator(pressedAnimation);
	setupAnimator(releasedAnimation);
	initializeElementSound(pressedSound);
	initializeElementSound(enteredSound);
	initializeElementSound(clickedSound);
	initializeElementSound(exitedSound);
	initializeElementSound(releasedSound);
	*/

	GUIElement::start(parent);	

	GUI->registerButton((GUIButton*)parent);
}