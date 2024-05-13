#pragma once

#include <json/json.h>
#include <string>
#include <eigen3/Eigen/Dense>
#include "Component.h"

class CameraComponent: public Component
{
public:
	unsigned int categoryMask = 0;
	Eigen::Vector4f clearColor = Eigen::Vector4f(1.0,1.0,1.0,1.0);
	bool clearScreen = false;
	std::string renderTarget = "";	
	int order = 0;
	int targetScreen = 0;
	int stereoscopicView = 0;
	Eigen::Vector4i viewportRect = Eigen::Vector4i(0,0,1,1);

	CameraComponent(Json::Value);
};