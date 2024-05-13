#pragma once

#include <json/json.h>
#include "Component.h"

class AnimatorComponent: public Component
{
public:
	std::string animation;
	std::string listener;
	bool looped;
	int speed;
	int time;

	AnimatorComponent(Json::Value);
};