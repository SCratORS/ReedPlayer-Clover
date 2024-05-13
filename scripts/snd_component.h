#pragma once

#include "../utils.h"
#include "../SoundComponent.h"

class snd_component: public SoundComponent
{
public:
	snd_component(Json::Value);
	void play();
};