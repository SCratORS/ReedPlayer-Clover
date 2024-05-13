#pragma once

#include "gui/gui_button.h"

#include "../LabelComponent.h"
#include "../SpriteComponent.h"
#include "../TextureComponent.h"
#include "sys_resume_float_wing.h"

class sys_resume_card:public GUIButton
{
private:
	SpriteComponent * active_component = NULL;
	SpriteComponent * inactive_component = NULL;
	SpriteComponent * floating_component = NULL;
	LabelComponent * debug_filelabel = NULL;
	TextureComponent * screen = NULL;
	GLuint *dummytexture = NULL;
	bool is_need_warning;
public:
	bool is_floating;
	sys_resume_float_wing * wingL = NULL;
	sys_resume_float_wing * wingR = NULL;

	sys_resume_card(Json::Value);
	void start(WorldNode *);

};