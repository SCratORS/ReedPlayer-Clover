#include "AnimatorComponent.h"
#include <iostream>

AnimatorComponent::AnimatorComponent(Json::Value node):Component(node) {
	for (auto const& paramName : node.getMemberNames()) {
		try {
			if (paramName != "scriptType" && paramName != "type" && paramName != "enabled" && paramName != "id") {
				if (paramName == "looped") looped = node[paramName].asBool();
				else if (paramName == "animation") animation = node[paramName].asString();
				else if (paramName == "listener") listener = node[paramName].asString();				
				else if (paramName == "speed") speed = node[paramName].asInt();	
				else if (paramName == "time") listener = node[paramName].asInt();	
				else if (paramName == "properties") for (auto const& propertieName : node[paramName].getMemberNames()) {
					Component::Propertie prop;
					prop.linkType = node[paramName][propertieName]["linkType"].asString();
					prop.linkId = node[paramName][propertieName]["linkId"].asString();
					properties.insert(make_pair(propertieName, prop));
				}
				else std::cout << "***WARNING(AnimatorComponent): Unknown param: " << paramName << std::endl;
			}
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(AnimatorComponent): Except in propertie: " << paramName << std::endl;
		}
	}
}