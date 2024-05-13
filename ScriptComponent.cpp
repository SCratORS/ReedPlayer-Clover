#include "ScriptComponent.h"

ScriptComponent::ScriptComponent(Json::Value node):Component(node) {
	for (auto const& paramName : node.getMemberNames()) {
		try {
			if (paramName != "scriptType" && paramName != "type" && paramName != "enabled" && paramName != "id") {
				if (paramName == "properties") for (auto const& propertieName : node[paramName].getMemberNames()) {
					if (propertieName == "looped") looped = node[paramName][propertieName].asBool();
					else if (propertieName == "autoplay") autoplay = node[paramName][propertieName].asBool();
					else if (propertieName == "isRight") isRight = node[paramName][propertieName].asBool();
					else {
						Component::Propertie prop;
						prop.linkType = node[paramName][propertieName]["linkType"].asString();
						prop.linkId = node[paramName][propertieName]["linkId"].asString();
						properties.insert(make_pair(propertieName, prop));
					}
				}
				else std::cout << "***WARNING(ScriptComponent): Unknown param: " << paramName << std::endl;
			}
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(ScriptComponent): Except in propertie: " << paramName << std::endl;
		}
	}

}