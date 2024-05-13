#include "sys_boot.h"

#include "platform.h"
#include "system.h"
#include "dbg_menu_final.h"
#include "gui/gui.h"
#include "app/clover_pad.h"
#include "app/clover_task.h"

#include "../ResourcesCollect.h"
#include "../Pad.h"
#include "../application.h"

extern std::string __RESORCES_DIR__;
extern gui * GUI;
extern pad * Pad;
extern cloverPadUI * CloverPadUI;
extern cloverTask * CloverTask;
extern System * _system;
extern dbgMenu * DbgMenu;
extern int TITLE_RETURN_CODE;

extern ResourcesCollect * resourcesCollect;
extern application * Application;

sys_boot::sys_boot(Json::Value json):WorldNode(json) {
	for (auto const& propertieName : json["properties"].getMemberNames()) {
		try {
			properties[propertieName] = new Propertie(json["properties"][propertieName]);
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(sys_boot): Except in propertie: " << propertieName << std::endl;
		}
	}

	Propertie * propertie;
	resource * res;

	propertie = properties["defaultScene"];
	if (propertie) {
		if (propertie->linkType == "Resource") {	
			if (propertie->linkId != "") {
				res = resourcesCollect->getParam(propertie->linkId);
				if (res) defaultScene = new Scene(__RESORCES_DIR__ + res->path);
				else std::cout << "***ERROR(sys_boot): Not found defaultScene resource: " << res->path << std::endl;
			} else std::cout << "***WARNING(sys_boot): linkId in propertie defaultScene is empty" << std::endl;
		} else std::cout << "***ERROR(sys_boot): Unknown type defaultScene: " << propertie->linkType << std::endl;
	} else std::cout << "***ERROR:(sys_boot) Not found propertie: defaultScene" << std::endl;

	propertie = properties["bootSound"];
	if (propertie) {
		if (propertie->linkType == "Component") {
			if (propertie->linkId != "") {
				Component* component = getComponent(propertie->linkId);
				if (component) {
					if (component->scriptType == "SoundComponent") bootSound = (SoundComponent*)component;
					else std::cout << "***ERROR(sys_boot)[bootSound]: Component type not supported: " << scriptType << std::endl;
				} else std::cout << "***ERROR(sys_boot)[bootSound]: Component not found: " << propertie->linkId << std::endl;
			} else std::cout << "***WARNING(sys_boot): linkId in propertie bootSound is empty" << std::endl;
		} else std::cout << "***ERROR(sys_boot): Unknown type bootSound: " << propertie->linkType << std::endl;
	} else std::cout << "***WARNING(sys_boot): Propertie not found: bootSound" << std::endl;

	propertie = properties["camera"];
	if (propertie) {
		if (propertie->linkType == "Component") {
			if (propertie->linkId != "") {
				Component* component = getComponent(propertie->linkId);
				if (component) {
					if (component->scriptType == "CameraComponent") camera = (CameraComponent*)component;
					else std::cout << "***ERROR(sys_boot)[camera]: Component type not supported: " << scriptType << std::endl;
				} else std::cout << "***ERROR(sys_boot)[camera]: Component not found: " << propertie->linkId << std::endl;
			} else std::cout << "***WARNING(sys_boot): linkId in propertie camera is empty" << std::endl;
		} else std::cout << "***ERROR(sys_boot): Unknown type camera: " << propertie->linkType << std::endl;
	} else std::cout << "***WARNING(sys_boot): Propertie not found: camera" << std::endl;

	bootTime = 0;
	/*
	slot0 = 1
	slot1 = 0
	slot2 = 10
	*/

	GUI->gameDevice = HOST_PLATFORM_IS_WINDOWS?GAME_DEVICE:GAME_DEVICE_1;
}

void sys_boot::exitFunction(){
	_system->exitEvent = true;
	_system->fadeOut(Application->exit);
}

void sys_boot::start() {
	std::cout << "TITLE_RETURN_CODE = " << TITLE_RETURN_CODE << std::endl;
	camera->disable();
	Pad->Init();
	CloverPadUI->EnableUserInput(false, "boot");
	CloverTask->Init();

	if (bootSound) {
		bootSound->play();
	}

	_system->load_settings();

	bootTime = 1;
	DbgMenu->entry("sys_boot", this);
	
	GUI->disabled = true;
	fonts = {};

	std::cout << "***TO-DO(sys_boot): crash in start if setExitHandler" << std::endl;
	//Application->setExitHandler(exitFunction);

	dialogclosed = true;

}



void sys_boot::render(const Eigen::Affine3f& parent_transform)
{	
	if (!(visible&&enabled)) return;
	Eigen::Affine3f trans = parent_transform * transform;
	WorldNode::render(trans);
	if (defaultScene) defaultScene->render(trans);
}

void sys_boot::update(int deltaTime)
{
	if (!enabled) return;
	WorldNode::update(deltaTime);
	if (defaultScene) defaultScene->update(deltaTime);
}