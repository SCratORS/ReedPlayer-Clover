#pragma once

#include "../WorldNode.h"
#include "../SoundComponent.h"
#include "../CameraComponent.h"
#include "../Scene.h"

class sys_boot : public WorldNode
{
private:
	Scene * defaultScene = NULL;
	SoundComponent * bootSound = NULL;
	CameraComponent * camera = NULL;
	unsigned int bootTime;

	std::vector<int*> fonts;
	bool dialogclosed = false;

public:
	sys_boot(Json::Value);
	void start();
	void render(const Eigen::Affine3f& parent_transform);
	void update(int deltaTime);
	void exitFunction();
};