#pragma once

#include <string>
#include <json/json.h>
#include "Component.h"
#include <SDL2/SDL_mixer.h>

class SoundComponent: public Component
{
private:
	Mix_Chunk * soundData = NULL;	
	bool playing;
public:
	int channel;
	bool autoPlay;
	bool loop;		
	int maxDistance;
	int minDistance;
	int pan;
	int pitch;
	bool positional;
	int priority;
	std::string soundId;
	bool stopWhenDisabled;
	int volume;

	/* propirties */
	bool isBGM = false;
	std::string label;

	SoundComponent(Json::Value);
	~SoundComponent();
	void play();
	void setSoundResource(std::string soundId);
	bool isPlaying();
	uint8_t * getSamplePosition();
	void disable();
};