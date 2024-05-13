#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#ifdef WIN32
#include <Windows.h>
#endif

#include "scripts/system.h"
#include "scripts/store.h"
#include "scripts/dbg_menu_final.h"
#include "scripts/app/clover_pad.h"
#include "scripts/app/clover_task.h"
#include "scripts/gui/gui.h"
#include "ResourcesCollect.h"
#include "TextureResourceCollect.h"
#include "FontResourceCollect.h"
#include "SpriteSheetCollect.h"
#include "ScriptComponent.h"
#include "Pad.h"



#include "Window.h"
#include "application.h"
#include "utils.h"



char* __LANGUAGE__ = NULL;
char* __REGION__   = NULL;
char* __BOOTAPP__  = NULL;

std::string __RESORCES_DIR__;
std::vector<char* > __SCRIPTS__;

ResourcesCollect * resourcesCollect;
TextureResourceCollect  * textureResourceCollect = new TextureResourceCollect();
FontResourceCollect  * fontResourceCollect = new FontResourceCollect();
SpriteSheetCollect  * spriteSheetCollect = new SpriteSheetCollect();

gui * GUI = NULL;
pad * Pad = new pad();
cloverPadUI * CloverPadUI = new cloverPadUI();
cloverTask * CloverTask = new cloverTask();
System * _system = new System();
application * Application = NULL;
dbgMenu * DbgMenu = new dbgMenu();

_Store * Store = NULL;
_Store::_debug_store * debug_store = NULL;
_Store::_store * store = NULL;

int TITLE_RETURN_CODE = 0;

int main(int argc, char* argv[])
{	
	Window window;
	unsigned int width = 1280;
	unsigned int height = 720;

	unsigned int argcount = argc;
	while (--argcount) {
		if (strstr(argv[argcount],"--language=")) 	__LANGUAGE__ 	= strstr(argv[argcount],"--language=")+11;
		if (strstr(argv[argcount],"--region=")) 	__REGION__ 		= strstr(argv[argcount],"--region=")+9;
		if (strstr(argv[argcount],"--bootapp="))	__BOOTAPP__ 	= strstr(argv[argcount],"--bootapp=")+10;
		if (strstr(argv[argcount],"--script-file")) for (int i=argcount+1; i < argc; i++) __SCRIPTS__.push_back(argv[i]);
	}
	if (!__BOOTAPP__ || !__LANGUAGE__ || !__REGION__) {
		std::cout << "***CRITICAL ERROR(general): Too many actual parametrs!" << std::endl;
		return 0;
	}
	__RESORCES_DIR__ = std::string(__BOOTAPP__) + std::string("/resources");

	resourcesCollect = new ResourcesCollect(__BOOTAPP__ + std::string("/dependencies.json"));
	
	if( !window.init(width, height) ) return false;
	window.renderLoadingScreen();
	window.swapBuffers();

	Application = new application(Utils::loadInit(__BOOTAPP__ + std::string("/init.json")));

	int lastTime = SDL_GetTicks();
	bool running = true;
	while(running)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_JOYHATMOTION:
				case SDL_JOYBUTTONDOWN:
				case SDL_JOYBUTTONUP:
				case SDL_KEYDOWN:
				case SDL_KEYUP:
				case SDL_JOYAXISMOTION:
				case SDL_TEXTINPUT:
				case SDL_TEXTEDITING:
				case SDL_JOYDEVICEADDED:
				case SDL_JOYDEVICEREMOVED:
					break;
				case SDL_QUIT:
					running = false;
					break;
			}
		}

		if(window.isSleeping())
		{
			lastTime = SDL_GetTicks();
			SDL_Delay(1); // this doesn't need to be accurate, we're just giving up our CPU time until something wakes us up
			continue;
		}

		int curTime = SDL_GetTicks();
		int deltaTime = curTime - lastTime;
		lastTime = curTime;

		// cap deltaTime at 1000
		if(deltaTime > 1000 || deltaTime < 0)
			deltaTime = 1000;

		Application->loop(Eigen::Affine3f::Identity(), deltaTime);
		window.swapBuffers();
	}
	window.deinit();
	return 0;
}