#pragma once
#include <memory>
#include <cstddef>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <json/json.h>

class SpriteSheetCollect
{
public:
	SpriteSheetCollect(){};
	~SpriteSheetCollect(){};
	bool LoadResources(std::string path, std::string id);
	std::string getTextureId(std::string id);
	Json::Value getParam(std::string id);

private:
	std::map <std::string, Json::Value> json;
	std::map <std::string, std::string> textures;
};