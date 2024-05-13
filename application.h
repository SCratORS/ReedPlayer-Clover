#pragma once

#include "utils.h"

#include <eigen3/Eigen/Dense>

#include "Scene.h"

#include "scripts/sys_boot.h"

class application
{
private:
	Scene * defaultScene = NULL;
	void (sys_boot::*exitHandler)();
public:
	application(Init*);
	~application();
	Point getScreenSize();
	void loop(const Eigen::Affine3f& transformMatrix, int deltaTime);
	void setExitHandler( void (sys_boot::*handler)()) {exitHandler = handler;}
	void exit();
};