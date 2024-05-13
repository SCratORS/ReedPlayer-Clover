#include "snd_component.h"

snd_component::snd_component(Json::Value node):SoundComponent(node) {
}

void snd_component::play() {
	std::cout << "***INFO: [PLAY_SOUND] "<< id << " : " << label << std::endl;
	if (isBGM) {
		//Если !debug_store.debugBGMOff
		SoundComponent::play();
	} else {
		//Если !debug_store.debugSEOff
		SoundComponent::play();
	}
}