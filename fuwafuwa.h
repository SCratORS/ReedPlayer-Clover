#pragma once

#include <json/json.h>
#include "ScriptComponent.h"

class fuwafuwa: public ScriptComponent
{
public:
	fuwafuwa(Json::Value);
	void addWing(WorldNode * wing);
};