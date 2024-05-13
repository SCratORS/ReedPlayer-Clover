#pragma once

#include "../application.h"
#include "../WorldNode.h"

class System
{
private:
	
public:
	bool exitEvent = false;
	WorldNode * save_callback_object;
	std::vector<WorldNode * > hud = {};
	System();
	bool is_hvc();
	bool is_nes();
	void fadeOut(void(application::*)());
	void load_settings();
};