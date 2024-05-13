#include "sys_resume_floating_card.h"
#include <iostream>
#include <ostream>


sys_resume_floating_card::sys_resume_floating_card(Json::Value json):sys_resume_card(json) {

}

void sys_resume_floating_card::start(WorldNode * parent)
{
	std::cout << "***TO-DO(sys_resume_card): function start() need modifed" << std::endl;
	sys_resume_card::start(parent);
	refresh();
	is_floating = true;
}


void sys_resume_floating_card::refresh() {
	std::cout << "***TO-DO(sys_resume_floating_card): function refresh() don't created" << std::endl;
}