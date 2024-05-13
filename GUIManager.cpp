#include "GUIManager.h"

#include <iostream>
#include <ostream>

GUIManager::GUIManager(WorldNode * node, ScriptComponent * component) {
	worldNode = node;

	Component::Propertie * propertie;
	propertie = component->getPropByName("inputCamera");
	if (propertie) {
		if (propertie->linkType == "Component") {
			if (propertie->linkId != "") {
				Component* component = node->getComponent(propertie->linkId);
				if (component) {
					if (component->scriptType == "CameraComponent") inputCamera = (CameraComponent*)component;
					else std::cout << "***ERROR(GUIManager)[inputCamera]: Component type not supported: " << component->scriptType << std::endl;
				} else std::cout << "***ERROR(GUIManager)[inputCamera]: Component not found: " << propertie->linkId << std::endl;
			} else std::cout << "***WARNING(GUIManager): linkId in propertie inputCamera is empty" << std::endl;
		} else std::cout << "***ERROR(GUIManager): Unknown type inputCamera: " << propertie->linkType << std::endl;
	} else std::cout << "***ERROR(GUIManager): Propertie not found: inputCamera" << std::endl;
}