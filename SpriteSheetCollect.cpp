#include "SpriteSheetCollect.h"

#include "Utils.h"

std::string SpriteSheetCollect::getTextureId(std::string id)
{
	return textures.find(id)->second;
}

Json::Value SpriteSheetCollect::getParam(std::string id)
{
	return json.find(id)->second;
}

bool SpriteSheetCollect::LoadResources(std::string path, std::string id)
{
	Json::Value jsonParam = Utils::LoadJson(path);

	if (jsonParam.isMember("texture")) {
		std::string id = jsonParam["texture"]["id"].asString();
		int width = jsonParam["texture"]["width"].asInt();
		int height = jsonParam["texture"]["height"].asInt();
		for (auto const& name : jsonParam["sprites"].getMemberNames()) {
			Json::Value sprite = jsonParam["sprites"][name];
			json.insert(make_pair(id+"."+name, sprite));
			textures.insert(make_pair(id+"."+name, id));
		}
	}
	return true;
}