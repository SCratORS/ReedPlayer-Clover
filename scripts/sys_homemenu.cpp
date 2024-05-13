#include "sys_homemenu.h"

sys_homemenu::sys_homemenu(Json::Value json):gui_container(json) {
	
}

void sys_homemenu::start(WorldNode * parent) {
	gui_container::start(parent);
}