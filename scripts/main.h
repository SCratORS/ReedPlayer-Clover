#include "gui_container.h"

#include "snd_component.h"
#include "sys_homemenu.h"
#include "../Scene.h"


class Main: public gui_container
{
private:
	snd_component * mainBGM = NULL;
	snd_component * bootBGM = NULL;
	sys_homemenu * startScene = NULL;
	int bgmPhase;
	std::string resMainBGM;
	Scene * bgScene = NULL;
public:
	Main(Json::Value);
	void start();
	void playMainBGM();
	void update(int deltaTime);	
	void render(const Eigen::Affine3f& parent_transform);
};