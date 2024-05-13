#pragma once

#include "WorldNode.h"
#include "CameraComponent.h"
#include "ScriptComponent.h"

class GUIManager
{
public:
	WorldNode * worldNode = NULL;
	CameraComponent * inputCamera = NULL;
	bool hasAutomaticNavigation = false;
	int dragThresholdX = 0;
	int dragThresholdY = 0;
	bool roundedUnits = false;
	float repeatDelay = 0.0;
	float repeatRate = 0.0;
	GUIManager(WorldNode*, ScriptComponent *);
};