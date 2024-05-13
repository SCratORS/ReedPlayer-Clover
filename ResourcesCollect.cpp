#include "ResourcesCollect.h"

#include "utils.h"
#include "TextureResourceCollect.h"
#include "FontResourceCollect.h"
#include "SpriteSheetCollect.h"

extern std::string __RESORCES_DIR__;
extern TextureResourceCollect  * textureResourceCollect;
extern SpriteSheetCollect  * spriteSheetCollect;
extern FontResourceCollect  * fontResourceCollect;

ResourcesCollect::~ResourcesCollect() {
	param = {};
}

ResourcesCollect::ResourcesCollect(std::string resourcesFilePath) {
	Json::Value dependencies = Utils::LoadJson(resourcesFilePath);

	for (Json::Value element : dependencies["resources"]) {
		resource item;
		bool valid = true;
		std::string id = element["id"].asString();
		item.type = element["type"].asString();
		item.path = element["path"].asString();
		item.groupId = element["groupId"].asString();
		if (element.isMember("dependencies")) {
			for (Json::Value dep : element["dependencies"]) {
				std::string idd = dep["id"].asString();
				if (param.find(idd) == param.end()) {
					valid = false; 
					std::cout << "***WARNING(ResourcesCollect): Element " << idd << " not defined for id " << id << std::endl;
					break;	
				}
			}
		}
		if (valid) {
			param.insert(make_pair(id, item));
			if (item.type == "TextureResource")
				if (!textureResourceCollect->LoadResources(__RESORCES_DIR__ + item.path, id))
					std::cout << "***WARNING(ResourcesCollect): Can't load TextureResource: " << __RESORCES_DIR__ << item.path << std::endl;
			if (item.type == "FontResource")
				if (!fontResourceCollect->LoadResources(__RESORCES_DIR__ + item.path, id))
					std::cout << "***WARNING(ResourcesCollect): Can't load FontResource: " << __RESORCES_DIR__ << item.path << std::endl;

			if (item.type == "SpriteSheet")
				if (!spriteSheetCollect->LoadResources(__RESORCES_DIR__ + item.path, id))
					std::cout << "***WARNING(ResourcesCollect): Can't load SpriteSheet: " << __RESORCES_DIR__ << item.path << std::endl;
		}
	}
}

resource * ResourcesCollect::getParam(std::string id) {
	std::map <std::string, resource>::iterator i = param.find(id);
	return (i == param.end())?NULL:&param.find(id)->second;
}