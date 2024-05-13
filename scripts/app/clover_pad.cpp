#include "clover_pad.h"
#include <iostream>
#include <ostream>

CloverPadBase::CloverPadBase()
{
	std::cout << "***TO-DO(clover_pad.cpp): class CloverPadBase not create" << std::endl;
}

void CloverPadBase::init()
{
	std::cout << "***TO-DO(clover_pad.cpp): function CloverPadBase->init() not create" << std::endl;
}



cloverPadUI::cloverPadUI()
{
	std::cout << "***TO-DO(clover_pad.cpp): class CloverPadUI not create" << std::endl;
}

void cloverPadUI::init()
{
	CloverPadBase::init();
	is_enable_user = true;
	disable_id_list = {};
	is_enable_auto = true;
	priority_input = "";
}

void cloverPadUI::EnableUserInput(bool enable, std::string scene)
{
	disable_id_list[scene] = !enable;
	auto next = std::next(disable_id_list.find(scene));
	is_enable_user = ! next->second;

	std::string text;
	int i = 0;
	for (int index{-1}; auto&el:disable_id_list) {
		index++;
		text += std::string("** enable input(") + scene + std::string("/") + 
			std::string(enable?"true":"false") + std::string("):") + std::to_string(index) + std::string(", ");
	}
	std::cout << text << std::endl;
}