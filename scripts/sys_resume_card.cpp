#include "sys_resume_card.h"

sys_resume_card::sys_resume_card(Json::Value json):GUIButton(json) {

	for (auto const& propertieName : json["properties"].getMemberNames()) {
		try {
			properties[propertieName] = new Propertie(json["properties"][propertieName]);
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(sys_resume_card): Except in propertie: " << propertieName << std::endl;
		}
	}

	wingL = (sys_resume_float_wing*)getElement(properties["wingL"],"sys_resume_float_wing");
	wingR = (sys_resume_float_wing*)getElement(properties["wingR"],"sys_resume_float_wing");


	Propertie * propertie;

	propertie = properties["active_component"];
	if (propertie) {
		if (propertie->linkType == "Component") {
			if (propertie->linkId != "") {
				Component* component = getComponent(propertie->linkId);
				if (component) {
					if (component->scriptType == "SpriteComponent") active_component = (SpriteComponent*)component;
					else std::cout << "***ERROR(sys_resume_card)[active_component]: Component type not supported: " << scriptType << std::endl;
				} else std::cout << "***ERROR(sys_resume_card)[active_component]: Component not found: " << propertie->linkId << std::endl;
			} else std::cout << "***WARNING(sys_resume_card): linkId in propertie active_component is empty" << std::endl;
		} else std::cout << "***ERROR(sys_resume_card): Unknown type active_component: " << propertie->linkType << std::endl;
	} else std::cout << "***WARNING(sys_resume_card): Propertie not found: active_component" << std::endl;

	propertie = properties["inactive_component"];
	if (propertie) {
		if (propertie->linkType == "Component") {
			if (propertie->linkId != "") {
				Component* component = getComponent(propertie->linkId);
				if (component) {
					if (component->scriptType == "SpriteComponent") inactive_component = (SpriteComponent*)component;
					else std::cout << "***ERROR(sys_resume_card)[inactive_component]: Component type not supported: " << scriptType << std::endl;
				} else std::cout << "***ERROR(sys_resume_card)[inactive_component]: Component not found: " << propertie->linkId << std::endl;
			} else std::cout << "***WARNING(sys_resume_card): linkId in propertie inactive_component is empty" << std::endl;
		} else std::cout << "***ERROR(sys_resume_card): Unknown type inactive_component: " << propertie->linkType << std::endl;
	}

	propertie = properties["floating_component"];
	if (propertie) {
		if (propertie->linkType == "Component") {
			if (propertie->linkId != "") {
				Component* component = getComponent(propertie->linkId);
				if (component) {
					if (component->scriptType == "SpriteComponent") floating_component = (SpriteComponent*)component;
					else std::cout << "***ERROR(sys_resume_card)[floating_component]: Component type not supported: " << scriptType << std::endl;
				} else std::cout << "***ERROR(sys_resume_card)[floating_component]: Component not found: " << propertie->linkId << std::endl;
			} else std::cout << "***WARNING(sys_resume_card): linkId in propertie floating_component is empty" << std::endl;
		} else std::cout << "***ERROR(sys_resume_card): Unknown type floating_component: " << propertie->linkType << std::endl;
	}

	propertie = properties["debug_filelabel"];
	if (propertie) {
		if (propertie->linkType == "Component") {
			if (propertie->linkId != "") {
				Component * component = getComponent(propertie->linkId);
				if (component) {
					if (component->scriptType == "LabelComponent") debug_filelabel = (LabelComponent*)component;
					else std::cout << "***ERROR(sys_resume_card)[debug_filelabel]: Component type not supported: " << scriptType << std::endl;
				} else std::cout << "***ERROR(sys_resume_card)[debug_filelabel]: Component not found: " << propertie->linkId << std::endl;
			} else std::cout << "***WARNING(sys_resume_card): linkId in propertie debug_filelabel is empty" << std::endl;
		} else std::cout << "***ERROR(sys_resume_card): Unknown type debug_filelabel: " << propertie->linkType << std::endl;
	}

	propertie = properties["screen"];
	if (propertie) {
		if (propertie->linkType == "Component") {
			if (propertie->linkId != "") {
				Component* component = getComponent(propertie->linkId);
				if (component) {
					if (component->scriptType == "TextureComponent") screen = (TextureComponent*)component;
					else std::cout << "***ERROR(sys_resume_card)[screen]: Component type not supported: " << scriptType << std::endl;
				} else std::cout << "***ERROR(sys_resume_card)[screen]: Component not found: " << propertie->linkId << std::endl;
			} else std::cout << "***WARNING(sys_resume_card): linkId in propertie screen is empty" << std::endl;
		} else std::cout << "***ERROR(sys_resume_card): Unknown type screen: " << propertie->linkType << std::endl;
	} else std::cout << "***WARNING(sys_resume_card): Propertie not found: screen" << std::endl;
}


void sys_resume_card::start(WorldNode * parent) {
	GUIButton::start(parent);

	if (active_component) active_component->disable();
	if (inactive_component) inactive_component->enable();
	if (floating_component) floating_component->disable();

	if (!REED_DEBUG && debug_filelabel) debug_filelabel->disable();

	dummytexture = screen->getTexture();
	is_floating = false;
	is_need_warning = false;

	screen->setColor(0, 0, 0, 1);
}