#pragma once

#include <json/json.h>
#include "Component.h"
#include <eigen3/Eigen/Dense>

class AnimatedSpriteComponent: public Component
{
public:
	std::string animation = "";
	int blendMode = 0;
	Eigen::Vector4f color = Eigen::Vector4f(1.0,1.0,1.0,1.0);
	bool hFlip = false;
	int layer = 0;
	bool looped = false;
	int magFilterMode = 1;
	int minFilterMode = 1;
	bool vFlip = false;
	int viewDepth = 0;
	bool visible = false;

	AnimatedSpriteComponent(Json::Value);
	void restart();
};