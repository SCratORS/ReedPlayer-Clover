#pragma once

#include "../WorldNode.h"
#include "../AnimatedSpriteComponent.h"

class effect_smoke:public WorldNode
{
private:
	AnimatedSpriteComponent * L = NULL;
	AnimatedSpriteComponent * S = NULL;
public:
	effect_smoke(Json::Value);
	void start(WorldNode *);
	void run();
	void runL();
	void runM();
	void runS();

};