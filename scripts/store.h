#pragma once

#include "../ScriptComponent.h"

#define SAVE_VERSION 7
#define DEBUGSAVE_VERSION 1

class _Store:public ScriptComponent
{
private:
	std::string systemFileName = "system-save.json";
	std::string debugFileName = "debug-save.json";
	
	std::vector<std::function<void(int,bool,std::string,bool)>> onSaveActionDone_Table;

	bool uisaveIsBusy = false;
	bool debugsaveIsBusy = false;

	WorldNode * callback_object = NULL;
public:
	struct _store
	{
		std::vector<int> info;
		std::vector<int> setting;
	};
	struct _debug_store
	{
		int version;
		int debug_version;
	};

	_Store(Json::Value);
	void start(WorldNode *);
	void init();
	void load();
	void ui_init();
	void debug_init();
	bool isBusy();
};