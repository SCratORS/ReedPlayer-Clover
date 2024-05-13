#pragma once

#include "../../ScriptComponent.h"
#include "../../GUIManager.h"

#include "gui_button.h"

#define GUI_COMMAND_FOCUS "COMMAND_FOCUS"
#define GUI_COMMAND_UNFOCUS "COMMAND_UNFOCUS"
#define GUI_COMMAND_PRESS "COMMAND_PRESS"
#define GUI_COMMAND_DRAG "COMMAND_DRAG"
#define GUI_COMMAND_RELEASE "COMMAND_RELEASE"
#define GUI_COMMAND_CLICK "COMMAND_CLICK"
#define GUI_COMMAND_LEFT "COMMAND_LEFT"
#define GUI_COMMAND_RIGHT "COMMAND_RIGHT"
#define GUI_COMMAND_UP "COMMAND_UP"
#define GUI_COMMAND_DOWN "COMMAND_DOWN"
#define GUI_COMMAND_KEYPRESS "COMMAND_KEYPRESS"

#define GUI_NEIGHBOUR_SELECTIVITY 0.5

class gui: public ScriptComponent
{
public:
	int gameDevice = 0;
	/* Unknown type vars */
	int * pressedCommandTarget = NULL;
	int * focusedElement = NULL;
	/*-------------------*/
	std::string clickMode = "release";
	std::string buttonMode = "push";
	int dragThresholdX = 4;
	int dragThresholdY = 4;
	bool hasAutomaticNavigation = false;
	bool roundedUnits = false;

	bool disabled = false;

	float REPEAT_DELAY = 0.0;
	float REPEAT_RATE = 0.0;

	GUIManager * manager = NULL;
	CameraComponent * camera = NULL;

	std::map<GUIButton* , bool> buttonTable = {};
	
	std::map<std::string, bool> DEBUG_LEVEL = 
	{
		{"hit_test", false},
		{"actions", false},
		{"runtime", false},
		{"commands", false},
		{"inputs", false},
		{"callbacks", false},
		{"states", false},
		{"sounds", false},
		{"dragging", false},
		{"scroll_layout", false},
		{"neighbors", false},
		{"hit_test_ll", false},
		{"animations", false},
		{"info", false},
		{"focus", false},
		{"input_repeat", false}
	};
	gui(Json::Value);
	void start(GUIManager *);
	void debugPrint(std::string, std::string level = "");
	void error(std::string);
	void reset();
	void setInputCamera(CameraComponent *);
	void registerButton(GUIButton * );
};