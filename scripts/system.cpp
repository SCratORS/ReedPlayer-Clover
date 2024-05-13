#include "system.h"
#include <iostream>
#include <ostream>

#include "store.h"

extern _Store * Store;
extern _Store::_store * store;

System::System(){

}

bool System::is_hvc()
{
	return true;
}

bool System::is_nes()
{
	return true;
}

void System::fadeOut(void(application::*exit)()){

}

void System::load_settings(){
	std::cout << "load_setting" << std::endl;
	Store->init();
	Store->load();
	if (!store->info.size()) store->info = {};
}
