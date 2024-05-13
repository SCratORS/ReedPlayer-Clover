#pragma once

//the Makefile defines one of these:
//#define USE_OPENGL_ES
//#define USE_OPENGL_DESKTOP

#ifdef USE_OPENGL_ES
	#define GLHEADER <GLES/gl.h>
#endif

#ifdef USE_OPENGL_DESKTOP
	#define GLHEADER <SDL_opengl.h>
#else
	#define GLHEADER <GL/gl.h>
#endif

#ifdef USE_OPENGL_ES
	#define glOrtho glOrthof
#endif

typedef struct _Rect { 
  unsigned left; 
  unsigned top; 
  unsigned width; 
  unsigned height; 
} Rect, *Prect; 

#define GL_CLAMP_TO_EDGE 0x812F

#define CLOVER_UI_PLATFORM "hvc"