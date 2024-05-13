#include "main.h"

#include "../ResourcesCollect.h"

extern std::string __RESORCES_DIR__;
extern ResourcesCollect * resourcesCollect;

Main::Main(Json::Value json):gui_container(json) {
	for (auto const& propertieName : json["properties"].getMemberNames()) {
		try {		
			if (propertieName == "setListener") continue;
			else if (propertieName == "autoGap") continue;
			else if (propertieName == "autoPosition") continue;
			else properties[propertieName] = new Propertie(json["properties"][propertieName]);
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(main): Except in propertie: " << propertieName << std::endl;
		}
	}
	startScene = (sys_homemenu*)getElement(properties["startScene"],"sys_homemenu");


	Propertie * propertie;
	resource * res;

	propertie = properties["bgScene"];
	if (propertie) {
		if (propertie->linkType == "Resource") {
			if (propertie->linkId != "") {	
				res = resourcesCollect->getParam(propertie->linkId);
				if (res) bgScene = new Scene(__RESORCES_DIR__ + res->path);
				else std::cout << "***ERROR(main): Not found bgScene resource: " << res->path << std::endl;
			} else std::cout << "***WARNING(main): linkId in propertie bgScene is empty" << std::endl;
		} else std::cout << "***ERROR(main): Unknown type bgScene: " << propertie->linkType << std::endl;
	} else std::cout << "***ERROR:(main) Not found propertie: bgScene" << std::endl;

	propertie = properties["bootBGM"];
	if (propertie) {
		if (propertie->linkType == "Component") {
			if (propertie->linkId != "") {
				Component * component = getComponent(propertie->linkId);
				if (component) {
					if (component->scriptType == "snd_component") bootBGM = (snd_component*)component;
					else std::cout << "***ERROR(main)[bootBGM]: Component type not supported: " << scriptType << std::endl;
				} else std::cout << "***ERROR(main)[bootBGM]: Component not found: " << propertie->linkId << std::endl;
			} else std::cout << "***WARNING(main): linkId in propertie bootBGM is empty" << std::endl;
		} else std::cout << "***ERROR(main): Unknown type bootBGM: " << propertie->linkType << std::endl;
	} else std::cout << "***WARNING(main): Propertie not found: bootBGM" << std::endl;

	propertie = properties["resMainBGM"];
	if (propertie) {
		if (propertie->linkType == "Resource") {
			if (propertie->linkId != "") {	
				resMainBGM = propertie->linkId;
			} else std::cout << "***WARNING(main): linkId in propertie resMainBGM is empty" << std::endl;
		} else std::cout << "***ERROR(main): Unknown type resMainBGM: " << propertie->linkType << std::endl;
	} else std::cout << "***ERROR:(main) Not found propertie: resMainBGM" << std::endl;

	propertie = properties["mainBGM"];
	if (propertie) {
		if (propertie->linkType == "Component") {
			if (propertie->linkId != "") {
				Component* component = getComponent(propertie->linkId);
				if (component) {
					if (component->scriptType == "snd_component") mainBGM = (snd_component*)component;
					else std::cout << "***ERROR(main)[mainBGM]: Component type not supported: " << scriptType << std::endl;
				} else std::cout << "***ERROR(main)[mainBGM]: Component not found: " << propertie->linkId << std::endl;
			} else std::cout << "***WARNING(main): linkId in propertie mainBGM is empty" << std::endl;
		} else std::cout << "***ERROR(main): Unknown type mainBGM: " << propertie->linkType << std::endl;
	} else std::cout << "***WARNING(main): Propertie not found: mainBGM" << std::endl;

}

void Main::start() {
	gui_container::start(this);

	bgmPhase = 0;
	
	std::cout << "***TO-DO(main): bootBGM is incorect code " << std::endl;
	bootBGM->play();
}

void Main::playMainBGM() {
	if (resMainBGM != "" ) mainBGM->play();
}

void Main::render(const Eigen::Affine3f& parent_transform)
{	
	if (!(visible&&enabled)) return;
	Eigen::Affine3f trans = parent_transform * transform;
	if (bgScene) bgScene->render(trans);
	WorldNode::render(trans);
}

void Main::update(int deltaTime) {
	if (!enabled) return;
	if (bgScene) bgScene->update(deltaTime);
	WorldNode::update(deltaTime);

	if (bgmPhase == 0) {
		if (resMainBGM!="") {
				bgmPhase = 1;
				mainBGM->setSoundResource(resMainBGM);
		}
	} else if (bgmPhase == 1) {
		if (!bootBGM->isPlaying()) {
			mainBGM->play();
			bootBGM->disable();
			bgmPhase = 2;
		}
	}
	
}