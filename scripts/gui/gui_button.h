#pragma once

#include "gui_element.h"

class GUIButton: public GUIElement
{
private:
	class states: public GUIElement::states
	{
		class pressed 
		{
			
		};
	};
	
public:
	/* Unknown type vars */
	int * pressedVisual = NULL;
	int * clickedAnimation = NULL;
	int * pressedAnimation = NULL;
	int * releasedAnimation = NULL;
	int * pressedSound = NULL;
	int * enteredSound = NULL;
	int * clickedSound = NULL;
	int * exitedSound = NULL;
	int * releasedSound = NULL;
	/*-------------------*/

	GUIButton(Json::Value);
	void start(WorldNode *);
};