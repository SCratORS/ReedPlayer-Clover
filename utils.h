#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include <string>
#include <map>
#include <json/json.h>
#include <fstream>
#include <iostream>

struct Point
{
	float x;
	float y;
};

struct Init
{
	std::string exportTime;
	std::string buildName;
	int engineFormat;
	std::string defaultScene;
	int worldUnitsPerMeter;
	Point gravity;
	std::string localizationRootPath;
	std::string localizationStringFilePath;
	std::map <std::string, std::string> localePathFormats;
};

namespace Utils {
    std::vector<std::string> explode(const std::string& str, const char& ch);
    Init* loadInit(std::string initFilePath);
    void printInit(Init * init);
    void error(std::string text);
    void print(std::string text);
    Point getScreenSize(int *);
    Json::Value LoadJson(std::string path);
}

#endif