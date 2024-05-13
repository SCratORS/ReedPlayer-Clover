#include "sys_home_floating_cards.h"

sys_home_floating_cards::sys_home_floating_cards(Json::Value json):WorldNode(json) {

	for (auto const& propertieName : json["properties"].getMemberNames()) {
		try {
			properties[propertieName] = new Propertie(json["properties"][propertieName]);
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(sys_home_floating_cards): Except in propertie: " << propertieName << std::endl;
		}
	}

	cardL = (sys_resume_floating_card*)getElement(properties["cardL"],"sys_resume_floating_card");
	cardM = (sys_resume_floating_card*)getElement(properties["cardM"],"sys_resume_floating_card");
	cardS = (sys_resume_floating_card*)getElement(properties["cardS"],"sys_resume_floating_card");
	operation = getElement(properties["operation"],"WorldNode");
	smoke = (effect_smoke*)getElement(properties["smoke"],"effect_smoke");

	Propertie * propertie;

	propertie = properties["fuwafuwa"];
	if (propertie) {
		if (propertie->linkType == "Component") {
			if (propertie->linkId != "") {
				Component * component = getComponent(propertie->linkId);
				if (component) {
					if (component->scriptType == "fuwafuwa") _fuwafuwa = (fuwafuwa*)component;
					else std::cout << "***ERROR(sys_home_floating_cards)[fuwafuwa]: Component type not supported: " << scriptType << std::endl;
				} else std::cout << "***ERROR(sys_home_floating_cards)[fuwafuwa]: Component not found: " << propertie->linkId << std::endl;
			} else std::cout << "***WARNING(sys_home_floating_cards): linkId in propertie fuwafuwa is empty" << std::endl;
		} else std::cout << "***ERROR(sys_home_floating_cards): Unknown type fuwafuwa: " << propertie->linkType << std::endl;
	} else std::cout << "***ERROR:(sys_home_floating_cards) Not found propertie: fuwafuwa" << std::endl;

	propertie = properties["floatingEraseSound"];
	if (propertie) {
		if (propertie->linkType == "Component") {
			if (propertie->linkId != "") {
				Component* component = getComponent(propertie->linkId);
				if (component) {
					if (component->scriptType == "snd_component") floatingEraseSound = (snd_component*)component;
					else std::cout << "***ERROR(sys_home_floating_cards)[floatingEraseSound]: Component type not supported: " << scriptType << std::endl;
				} else std::cout << "***ERROR(sys_home_floating_cards)[floatingEraseSound]: Component not found: " << propertie->linkId << std::endl;
			} else std::cout << "***WARNING(sys_home_floating_cards): linkId in propertie floatingEraseSound is empty" << std::endl;
		} else std::cout << "***ERROR(sys_home_floating_cards): Unknown type floatingEraseSound: " << propertie->linkType << std::endl;
	} else std::cout << "***WARNING(sys_home_floating_cards): Propertie not found: floatingEraseSound" << std::endl;
}

void sys_home_floating_cards::start(WorldNode * parent)
{
	Point p;
	p = getLocalPosition();orgX = p.x; orgY = p.y;
	p = cardL->getLocalPosition();Lx = p.x; Ly = p.y;
	p = cardM->getLocalPosition();Mx = p.x; My = p.y;
	p = cardS->getLocalPosition();Sx = p.x; Sy = p.y;

	cardL->disable();
	cardM->enable();
	cardS->disable();

	cardSize="M";

	if (operation) operation->disable();

	if (_fuwafuwa) {
		_fuwafuwa->addWing(cardL->wingL);
		_fuwafuwa->addWing(cardL->wingR);
		_fuwafuwa->addWing(cardM->wingL);
		_fuwafuwa->addWing(cardM->wingR);
		_fuwafuwa->addWing(cardS->wingL);
		_fuwafuwa->addWing(cardS->wingR);
		_fuwafuwa->setType("homemenu");
	}
	is_moving = false;
}
