#include "AnimatedSpriteComponent.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(Json::Value node):Component(node) {
	for (auto const& paramName : node.getMemberNames()) {
		try {
			if (paramName != "scriptType" && paramName != "type" && paramName != "enabled" && paramName != "id") {
				if (paramName == "blendMode") blendMode = node[paramName].asInt();
				else if (paramName == "hFlip") hFlip = node[paramName].asBool();
				else if (paramName == "layer") layer = node[paramName].asInt();				
				else if (paramName == "magFilterMode") magFilterMode = node[paramName].asInt();
				else if (paramName == "minFilterMode") minFilterMode = node[paramName].asInt();
				else if (paramName == "vFlip") vFlip = node[paramName].asBool();
				else if (paramName == "viewDepth") viewDepth = node[paramName].asInt();
				else if (paramName == "visible") visible = node[paramName].asBool();
				else if (paramName == "animation") animation = node[paramName].asString();
				else if (paramName == "looped") looped = node[paramName].asBool();
				else if (paramName == "color") color = Eigen::Vector4f(node[paramName][0].asFloat(),node[paramName][1].asFloat(),
										node[paramName][2].asFloat(),node[paramName][3].asFloat());
				else if (paramName == "properties") for (auto const& propertieName : node[paramName].getMemberNames()) {
					Component::Propertie prop;
					prop.linkType = node[paramName][propertieName]["linkType"].asString();
					prop.linkId = node[paramName][propertieName]["linkId"].asString();
					properties.insert(make_pair(propertieName, prop));
				}
				else std::cout << "***WARNING(AnimatedSpriteComponent): Unknown param: " << paramName << std::endl;
			}
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(AnimatedSpriteComponent): Except in propertie: " << paramName << std::endl;
		}
	}
}


void AnimatedSpriteComponent::restart() {
	std::cout << "***TO-DO(AnimatedSpriteComponent): function restart() don't created" << std::endl;
}