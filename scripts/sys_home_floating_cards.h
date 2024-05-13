#pragma once

#include "../WorldNode.h"
#include "../fuwafuwa.h"

#include "sys_resume_floating_card.h"
#include "snd_component.h"
#include "effect_smoke.h"


class sys_home_floating_cards:public WorldNode
{
private:
	sys_resume_floating_card * cardL = NULL;
	sys_resume_floating_card * cardM = NULL;
	sys_resume_floating_card * cardS = NULL;
	WorldNode * operation = NULL;
	fuwafuwa * _fuwafuwa = NULL;
	snd_component * floatingEraseSound = NULL;
	effect_smoke * smoke = NULL;
	int orgX, orgY;
	int Lx, Ly;
	int Mx, My;
	int Sx, Sy;
	std::string cardSize;
	std::string info;
	bool is_moving;
public:
	sys_home_floating_cards(Json::Value);
	void setInfo(std::string txt) {info = txt;}
	void start(WorldNode *);
};