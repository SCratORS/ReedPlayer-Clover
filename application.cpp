#include "application.h"

#include "ResourcesCollect.h"

extern std::string __RESORCES_DIR__;
extern ResourcesCollect * resourcesCollect;

application::application(Init* init) {
	resource * defaultSceneRes = resourcesCollect->getParam(init->defaultScene);
	if (!defaultSceneRes) {
		std::cout << "***CRITICAL ERROR(Application): Not found default scene resource: " << defaultSceneRes->path << std::endl;
		return;
	}
	if (defaultSceneRes->type == "Scene") {
		defaultScene = new Scene(__RESORCES_DIR__ + defaultSceneRes->path);
		if (!defaultScene) std::cout << "***CRITICAL ERROR(Application): Default scene not loaded: " << defaultSceneRes->path << std::endl;
	}
	else std::cout << "***CRITICAL ERROR(Application): Cant load default scene path: " << defaultSceneRes->path << std::endl;
}

application::~application() {

}

void application::loop(const Eigen::Affine3f& transform, int deltaTime)
{	
	if (defaultScene) {
		defaultScene->update(deltaTime);
		defaultScene->render(transform);
	}
}

void application::exit(){
	
}