#pragma once

#include <json/json.h>
#include "Component.h"
#include "WorldNode.h"

class ScriptComponent: public Component
{
public:

	bool looped;
	bool autoplay;
	bool isRight;

	ScriptComponent(Json::Value);
};