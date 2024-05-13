#include "Scene.h"

#include "utils.h"
#include "scripts/sys_boot.h"
#include "scripts/main.h"

Scene::Scene(std::string path) {
	std::cout << "***INFO: [LOAD_SCENE] " << path << std::endl;
    Json::Value jsonScene = Utils::LoadJson(path);

    if (jsonScene.isMember("rootWorldNode")) {
    	scriptType = jsonScene["rootWorldNode"]["scriptType"].asString();
    	if (scriptType == "sys_boot") rootWorldNode = new sys_boot(jsonScene["rootWorldNode"]);   
    	else if (scriptType == "Main") rootWorldNode = new Main(jsonScene["rootWorldNode"]); 
    	else if (scriptType == "WorldNode") rootWorldNode = new WorldNode(jsonScene["rootWorldNode"]); 
    	else std::cout << "***WARNING(Scene):  Unknown scriptType" << scriptType << std::endl;	
    } else std::cout << "***CRITICAL ERROR: Node \"rootWorldNode\" not found in: " << path << std::endl;

    start();

}

void Scene::update(int deltaTime) {
	if (rootWorldNode) {
		if (scriptType == "Main") ((Main*)rootWorldNode)->update(deltaTime);
		else if (scriptType == "sys_boot") ((sys_boot*)rootWorldNode)->update(deltaTime);
		else rootWorldNode->update(deltaTime);
	}
}
void Scene::render(const Eigen::Affine3f& transform) {
	if (rootWorldNode) {
		if (scriptType == "Main") ((Main*)rootWorldNode)->render(transform);
		else if (scriptType == "sys_boot") ((sys_boot*)rootWorldNode)->render(transform);
		else rootWorldNode->render(transform);
	}
}
void Scene::start() {
	if (rootWorldNode) {
		if (scriptType == "Main") ((Main*)rootWorldNode)->start();
		if (scriptType == "sys_boot") ((sys_boot*)rootWorldNode)->start();
		rootWorldNode->start();
	}
}