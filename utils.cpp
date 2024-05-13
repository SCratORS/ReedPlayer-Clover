#include "utils.h"

namespace Utils {
    std::vector<std::string> explode(const std::string& str, const char& ch) {
        std::string next;
        std::vector<std::string> result;
        for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
            if (*it == ch) {
                if (!next.empty()) {
                    result.push_back(next);
                    next.clear();
                }
            } else next += *it;
        }
        if (!next.empty()) result.push_back(next);
        return result;
    }
    
    Init* loadInit(std::string initFilePath) {
        Init* init = new Init;

        Json::Value initJson = LoadJson(initFilePath);

        init->exportTime = initJson["exportTime"].asString();
        init->buildName = initJson["buildName"].asString();
        init->engineFormat = initJson["engineFormat"].asInt();
        init->defaultScene = initJson["defaultScene"].asString();
        init->worldUnitsPerMeter = initJson["worldUnitsPerMeter"].asInt();
        init->gravity.x = initJson["gravity"][0].asFloat();
        init->gravity.y = initJson["gravity"][1].asFloat();
        init->localizationRootPath = initJson["localizationRootPath"].asString();
        init->localizationStringFilePath = initJson["localizationStringFilePath"].asString();
        std::vector<std::string> pathFormat = {};
        for (Json::Value element : initJson["localePathFormats"]) {
            if (pathFormat.empty()) {
                pathFormat = Utils::explode(element.asString(),'_');
            } else {
                std::vector<std::string> item = Utils::explode(element.asString(),'_');
                std::string REGION;
                std::string LANGUAGE;
                for (int i{ 0 }; auto &l:pathFormat) {
                    if (l == "<REGION>") REGION = item[i];
                    if (l == "<LANGUAGE>") LANGUAGE = item[i];
                    i++;
                }
                init->localePathFormats.insert(make_pair(REGION, LANGUAGE));
            }
        }
        return init;
    }

    void printInit(Init * init) {
        std::cout << init->exportTime << std::endl;
        std::cout << init->buildName << std::endl;
        std::cout << init->engineFormat << std::endl;
        std::cout << init->defaultScene << std::endl;
        std::cout << init->worldUnitsPerMeter << std::endl;
        std::cout << init->gravity.x << " " << init->gravity.y << std::endl;
        std::cout << init->localizationRootPath << std::endl;   
        std::cout << init->localizationStringFilePath << std::endl;
        for(const auto& elem : init->localePathFormats) std::cout << elem.first << " " << elem.second << std::endl;
    }

    void error(std::string text) {
        std::cout << text << std::endl;
    }

    void print(std::string text) {
        std::cout << text << std::endl;
    }

    Point getScreenSize(int * value){ 
        Point res;
        res.x = 1280;
        res.y = 720;
        return res;
    }

    Json::Value LoadJson(std::string path) {
        std::ifstream stream;
        Json::Value * value = new Json::Value();
        JSONCPP_STRING errors;
        Json::CharReaderBuilder builder;

        stream.open(path);
        if (!stream) {
            std::cout << "***ERROR(JSON): Can't load file: " << path << std::endl;
            return *value;
        }
        if (!parseFromStream(builder, stream, value, &errors)) {
            stream.close();
            std::cout << "***ERROR(JSON): Incorrect json file: " << path << std::endl;
            return *value;
        }
        stream.close();
        return *value;
    }
}