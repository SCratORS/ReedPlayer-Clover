#pragma once

#include <string>

#include "../../WorldNode.h"

class GUILayout
{
public:
	bool refreshSuspended = false;
	GUILayout();
	void initialize(int, int);
	void pushBackElement(WorldNode * );
	void resume(bool);
	void suspend();
	void refresh(); //Похоже она тут 
};