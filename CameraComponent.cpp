#include "CameraComponent.h"
#include <iostream>

CameraComponent::CameraComponent(Json::Value node):Component(node) {
	for (auto const& paramName : node.getMemberNames()) {
		try {
			if (paramName != "scriptType" && paramName != "type" && paramName != "enabled" && paramName != "id") {
				if (paramName == "categoryMask") categoryMask = node[paramName].asUInt();
				else if (paramName == "clearScreen") clearScreen = node[paramName].asBool();		
				else if (paramName == "order") order = node[paramName].asInt();
				else if (paramName == "stereoscopicView") stereoscopicView = node[paramName].asInt();
				else if (paramName == "targetScreen") targetScreen = node[paramName].asInt();
				else if (paramName == "renderTarget") renderTarget = node[paramName].asString();
				else if (paramName == "clearColor") clearColor = Eigen::Vector4f(node[paramName][0].asFloat(),node[paramName][1].asFloat(),	node[paramName][2].asFloat(),node[paramName][3].asFloat());
				else if (paramName == "viewportRect") viewportRect = Eigen::Vector4i(node[paramName][0].asInt(),node[paramName][1].asInt(), node[paramName][2].asInt(),node[paramName][3].asInt());
				else if (paramName == "properties") for (auto const& propertieName : node[paramName].getMemberNames()) {
					Component::Propertie prop;
					prop.linkType = node[paramName][propertieName]["linkType"].asString();
					prop.linkId = node[paramName][propertieName]["linkId"].asString();
					properties.insert(make_pair(propertieName, prop));
				}
				else std::cout << "***WARNING(CameraComponent): Unknown param: " << paramName << std::endl;
			}
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(CameraComponent): Except in propertie: " << paramName << std::endl;
		}
	}
}