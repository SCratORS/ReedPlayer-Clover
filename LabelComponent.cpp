#include "LabelComponent.h"
#include <iostream>

LabelComponent::LabelComponent(Json::Value node):Component(node) {
	for (auto const& paramName : node.getMemberNames()) {
		try {
			if (paramName != "scriptType" && paramName != "type" && paramName != "enabled" && paramName != "id") {
				if (paramName == "alignment") alignment = node[paramName].asString();
				else if (paramName == "blendMode") blendMode = node[paramName].asInt();		
				else if (paramName == "color") color = Eigen::Vector4f(node[paramName][0].asFloat(),node[paramName][1].asFloat(), node[paramName][2].asFloat(),node[paramName][3].asFloat());
				else if (paramName == "fontResource") fontResource = node[paramName].asString();
				else if (paramName == "gradientcolorbottom") gradientcolorbottom = Eigen::Vector4f(node[paramName][0].asFloat(),node[paramName][1].asFloat(), node[paramName][2].asFloat(),node[paramName][3].asFloat());
				else if (paramName == "gradientcolortop") gradientcolortop = Eigen::Vector4f(node[paramName][0].asFloat(),node[paramName][1].asFloat(), node[paramName][2].asFloat(),node[paramName][3].asFloat());
				else if (paramName == "has_shadow") has_shadow = node[paramName].asBool();
				else if (paramName == "horizontalAnchor") horizontalAnchor = node[paramName].asString();
				else if (paramName == "layer") layer = node[paramName].asInt();
				else if (paramName == "magFilterMode") magFilterMode = node[paramName].asInt();
				else if (paramName == "minFilterMode") minFilterMode = node[paramName].asInt();
				else if (paramName == "monospaced") monospaced = node[paramName].asBool();
				else if (paramName == "shadowcolor") shadowcolor = Eigen::Vector4f(node[paramName][0].asFloat(),node[paramName][1].asFloat(), node[paramName][2].asFloat(),node[paramName][3].asFloat());
				else if (paramName == "shadowoffsetx") shadowoffsetx = node[paramName].asInt();
				else if (paramName == "shadowoffsety") shadowoffsety = node[paramName].asInt();
				else if (paramName == "text") text = node[paramName].asString();
				else if (paramName == "verticalAnchor") verticalAnchor = node[paramName].asString();
				else if (paramName == "viewDepth") viewDepth = node[paramName].asInt();
				else if (paramName == "visible") visible = node[paramName].asBool();
				else if (paramName == "wordWrap") wordWrap = node[paramName].asBool();
				else if (paramName == "wrapWidth") wrapWidth = node[paramName].asInt();
				else if (paramName == "properties") for (auto const& propertieName : node[paramName].getMemberNames()) {
					if (propertieName == "colorName") colorName = node[paramName][propertieName].asString();
					else if (propertieName == "fontName") fontName = node[paramName][propertieName].asString();
					else if (propertieName == "textScale") textScale = node[paramName][propertieName].asFloat();
					else if (propertieName == "lineHeightOffset") lineHeightOffset = node[paramName][propertieName].asInt();
					else if (propertieName == "characterSpacingOffset") characterSpacingOffset = node[paramName][propertieName].asInt();
					else {
						Component::Propertie prop;
						prop.linkType = node[paramName][propertieName]["linkType"].asString();
						prop.linkId = node[paramName][propertieName]["linkId"].asString();
						properties.insert(make_pair(propertieName, prop));
					}
				}
				else std::cout << "***WARNING(LabelComponent): Unknown param: " << paramName << std::endl;
			}
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(LabelComponent)" << id << " : Except in propertie: " << paramName << std::endl;
		}
	}
}