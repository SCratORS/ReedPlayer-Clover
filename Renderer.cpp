#include "Renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace Renderer
{
	static bool initialCursorState;
	unsigned int display_width = 0;
	unsigned int display_height = 0;
	unsigned int getScreenWidth() { return display_width; }
	unsigned int getScreenHeight() { return display_height; }
	SDL_Window* sdlWindow = NULL;
	SDL_GLContext sdlContext = NULL;

	bool createSurface()
	{
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) return false;

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		#ifdef USE_OPENGL_ES
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
		#endif

		sdlWindow = SDL_CreateWindow("clover", 
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			display_width, display_height, 
			SDL_WINDOW_OPENGL);
		if(sdlWindow == NULL)	return false;
		size_t width = 0;
		size_t height = 0;
 		sdlContext = SDL_GL_CreateContext(sdlWindow);
		initialCursorState = SDL_ShowCursor(0) == 1;
		Mix_OpenAudio(44100,AUDIO_S16SYS,2,1024);
		return true;
	}

	void swapBuffers()
	{
		SDL_GL_SwapWindow(sdlWindow);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void destroySurface()
	{
		SDL_GL_DeleteContext(sdlContext);
		sdlContext = NULL;
		SDL_DestroyWindow(sdlWindow);
		sdlWindow = NULL;
		//show mouse cursor
		SDL_ShowCursor(initialCursorState);
		SDL_CloseAudio();
		SDL_Quit();
	}

	bool init(int w, int h)
	{
		if (w) display_width = w;
		if (h) display_height = h;
		if(!createSurface()) return false;
		glViewport(0, 0, display_width, display_height);
		glMatrixMode(GL_PROJECTION);
		glOrtho(-w/2, w/2, -h/2, h/2, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		return true;
	}

	void deinit()
	{
		destroySurface();
	}
};