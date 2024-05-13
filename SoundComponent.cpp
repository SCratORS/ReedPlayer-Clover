#include "SoundComponent.h"
#include <iostream>

#include "ResourcesCollect.h"

extern std::string __RESORCES_DIR__;
extern ResourcesCollect * resourcesCollect;

SoundComponent::SoundComponent(Json::Value node):Component(node) {
	for (auto const& paramName : node.getMemberNames()) {
		try {
			if (paramName != "scriptType" && paramName != "type" && paramName != "enabled" && paramName != "id") {
				if (paramName == "autoPlay") autoPlay = node[paramName].asBool();
				else if (paramName == "loop") loop = node[paramName].asBool();		
				else if (paramName == "maxDistance") maxDistance = node[paramName].asInt();
				else if (paramName == "minDistance") minDistance = node[paramName].asInt();
				else if (paramName == "pan") pan = node[paramName].asInt();
				else if (paramName == "pitch") pitch = node[paramName].asInt();
				else if (paramName == "positional") positional = node[paramName].asBool();
				else if (paramName == "priority") priority = node[paramName].asInt();
				else if (paramName == "soundId") soundId = node[paramName].asString();
				else if (paramName == "stopWhenDisabled") stopWhenDisabled = node[paramName].asBool();
				else if (paramName == "volume") volume = node[paramName].asInt();
				else if (paramName == "properties") for (auto const& propertieName : node[paramName].getMemberNames()) {
					if (propertieName == "isBGM") isBGM = node[paramName][propertieName].asBool();
					else if (propertieName == "label") label = node[paramName][propertieName].asString();
					else {
						Component::Propertie prop;
						prop.linkType = node[paramName][propertieName]["linkType"].asString();
						prop.linkId = node[paramName][propertieName]["linkId"].asString();
						properties.insert(make_pair(propertieName, prop));
					}
				}
				else std::cout << "***WARNING(SoundComponent): Unknown param: " << paramName << std::endl;
			}
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(SoundComponent): Except in propertie: " << paramName << std::endl;
		}
	}
	if (soundId != "") setSoundResource(soundId);
}

void SoundComponent::play() {
//	channel = Mix_AllocateChannels(-1);

	channel = Mix_PlayChannel(-1,soundData,loop?-1:0);
	Mix_Volume(channel, volume*128);
	Mix_SetPanning(channel, pan>0?0:255, pan<0?0:255);
}

SoundComponent::~SoundComponent() {
	//SDL_FreeWAV(wavBuffer);
}

void SoundComponent::setSoundResource(std::string soundId) {
	std::string path = __RESORCES_DIR__ + resourcesCollect->getParam(soundId)->path;
	soundData = Mix_LoadWAV(path.c_str());
}

uint8_t * SoundComponent::getSamplePosition() {
	return 0;
}


bool SoundComponent::isPlaying(){
	return Mix_Playing(channel);
}

void SoundComponent::disable()  {
	Component::disable();
	//if (stopWhenDisabled) Mix_HaltChannel (channel);
}