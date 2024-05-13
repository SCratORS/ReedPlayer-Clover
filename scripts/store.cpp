#include "store.h"
#include <iostream>
#include <ostream>

#include "system.h"

extern _Store::_debug_store * debug_store;
extern _Store::_store * store;
extern System * _system;

_Store::_Store(Json::Value json): ScriptComponent(json) {

	/*
	std::cout << "***TO-DO(Store): ScriptComponent not inner WorldNode Element. Problem.." << std::endl;
	Component::Propertie * propertie;
	
	propertie = getPropByName("callback_object");
	if (propertie) {
		if (propertie->linkType == "WorldNode") {
			if (propertie->linkId != "") {
				WorldNode * component = getElement(propertie->linkId);
				if (component) callback_object = component;
				else std::cout << "***ERROR(Store)[callback_object]: Component not found: " << propertie->linkId << std::endl;
			} else std::cout << "***WARNING(Store): linkId in propertie callback_object is empty" << std::endl;
		} else std::cout << "***ERROR(Store): Unknown type callback_object: " << propertie->linkType << std::endl;
	} else std::cout << "***WARNING(Store): Propertie callback_object not found" << std::endl;
	*/

	store = new _store();
	debug_store = new _debug_store();

}

void _Store::init() {
	ui_init();
	debug_init();
}

void _Store::ui_init() {
	store->setting = {};
	store->info = {};
}

void _Store::debug_init() {
	debug_store->version = SAVE_VERSION;
	debug_store->debug_version = DEBUGSAVE_VERSION;
}

void _Store::load() {
	std::cout << "***TO-DO(Store): function load() need modifed" << std::endl;
	if (!isBusy()) {
//		uv0();
//		uv1();
	} else std::cout << "Store is busy" << std::endl;
}

bool _Store::isBusy() {
	return uisaveIsBusy || debugsaveIsBusy;
}

void _Store::start(WorldNode * parent) {
	std::cout << "***TO-DO(Store): function start() need modifed" << std::endl;
	// Store.instance = slot0
	onSaveActionDone_Table = {};
	_system->save_callback_object = callback_object;

	/* this function -> need move to system!
	function system.save_callback_object.onSaveActionDone(slot0, slot1, slot2, slot3, slot4)
		Store.onSaveActionDone_Table[slot1](slot1, slot2, slot3, slot4)

		Store.onSaveActionDone_Table[slot1] = nil
	end
	*/
}