#pragma once

#include "WorldNode.h"

class Scene
{
private:
	WorldNode * rootWorldNode = NULL;
public:
	Scene(std::string);
	~Scene() {};
	std::string scriptType;
	void update(int deltaTime);
	void render(const Eigen::Affine3f& transform);
	void start();
};