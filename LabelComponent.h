#pragma once

#include <json/json.h>
#include <eigen3/Eigen/Dense>

#include "Component.h"

class LabelComponent: public Component
{
public:
	std::string alignment = "";
	int blendMode = 0;
    Eigen::Vector4f color = Eigen::Vector4f(1.0,1.0,1.0,1.0);
	std::string fontResource = "";
	Eigen::Vector4f gradientcolorbottom = Eigen::Vector4f(1.0,1.0,1.0,1.0);
	Eigen::Vector4f gradientcolortop = Eigen::Vector4f(1.0,1.0,1.0,1.0);;
	bool has_shadow = false;
	std::string horizontalAnchor = "";
	int layer = 0;
	int magFilterMode = 1;
	int minFilterMode = 1;
	bool monospaced = false;
	Eigen::Vector4f shadowcolor = Eigen::Vector4f(0.0,0.0,0.0,1.0);;
	int shadowoffsetx = 1;
	int shadowoffsety = 1;
	std::string text = "";
	std::string verticalAnchor = "";
	int viewDepth = 0;
	bool visible = false;
	bool wordWrap = false;
	int wrapWidth = 0;

	/*  properties */
	std::string colorName = "";
	std::string fontName = "";
	int lineHeightOffset = 0;
	int characterSpacingOffset = 0;
	float textScale = 1.0;

	LabelComponent(Json::Value);
};