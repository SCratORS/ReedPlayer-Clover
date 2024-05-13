#pragma once
#include "Renderer.h"

class Window
{
public:
	Window();
	~Window();

	bool init(unsigned int width = 1280, unsigned int height = 720);
	void deinit();
	void swapBuffers();
	void renderLoadingScreen();
	
	inline bool isSleeping() const { return mSleeping; }

private:
	bool mSleeping;
};