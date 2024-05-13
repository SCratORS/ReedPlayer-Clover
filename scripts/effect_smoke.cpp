#include "effect_smoke.h"

effect_smoke::effect_smoke(Json::Value json):WorldNode(json) {
	for (auto const& propertieName : json["properties"].getMemberNames()) {
		try {
			properties[propertieName] = new Propertie(json["properties"][propertieName]);
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(sys_resume_card): Except in propertie: " << propertieName << std::endl;
		}
	}

	Propertie * propertie;

	propertie = properties["L"];
	if (propertie) {
		if (propertie->linkType == "Component") {
			if (propertie->linkId != "") {
				Component* component = getComponent(propertie->linkId);
				if (component) {
					if (component->scriptType == "AnimatedSpriteComponent") L = (AnimatedSpriteComponent*)component;
					else std::cout << "***ERROR(effect_smoke)[L]: Component type not supported: " << scriptType << std::endl;
				} else std::cout << "***ERROR(effect_smoke)[L]: Component not found: " << propertie->linkId << std::endl;
			} else std::cout << "***WARNING(effect_smoke): linkId in propertie L is empty" << std::endl;
		} else std::cout << "***ERROR(effect_smoke): Unknown type L: " << propertie->linkType << std::endl;
	} else std::cout << "***ERROR(effect_smoke): Propertie not found: L" << std::endl;

	propertie = properties["S"];
	if (propertie) {
		if (propertie->linkType == "Component") {
			if (propertie->linkId != "") {
				Component* component = getComponent(propertie->linkId);
				if (component) {
					if (component->scriptType == "AnimatedSpriteComponent") S = (AnimatedSpriteComponent*)component;
					else std::cout << "***ERROR(effect_smoke)[S]: Component type not supported: " << scriptType << std::endl;
				} else std::cout << "***ERROR(effect_smoke)[S]: Component not found: " << propertie->linkId << std::endl;
			} else std::cout << "***WARNING(effect_smoke): linkId in propertie S is empty" << std::endl;
		} else std::cout << "***ERROR(effect_smoke): Unknown type S: " << propertie->linkType << std::endl;
	} else std::cout << "***ERROR(effect_smoke): Propertie not found: S" << std::endl;
	
}

void effect_smoke::start(WorldNode * parent)
{
	L->disable();
	S->disable();
}

void effect_smoke::run()
{
	runL();
}

void effect_smoke::runL()
{
	L->enable();
	L->restart();
}

void effect_smoke::runM()
{
	runL();
}

void effect_smoke::runS()
{
	S->enable();
	S->restart();
}