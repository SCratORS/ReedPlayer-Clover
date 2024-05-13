#pragma once

#include "../WorldNode.h"

class sys_resumedummy:public WorldNode
{
private:
	bool is_select_title = false;
	WorldNode * root;

public:
	sys_resumedummy(Json::Value);
	void render(const Eigen::Affine3f& parent_transform);
	void update(int deltaTime);
	void start(WorldNode *);
};