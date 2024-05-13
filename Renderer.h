#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "platform.h"
#include GLHEADER

namespace Renderer
{
	unsigned int getScreenWidth();
	unsigned int getScreenHeight();
	bool init(int w, int h);
	void deinit();
	void swapBuffers();
}

#endif