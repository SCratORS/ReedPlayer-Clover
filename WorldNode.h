#pragma once

#include "utils.h"
#include <string>
#include <eigen3/Eigen/Dense>
#include <typeinfo>
#include "platform.h"
#include GLHEADER

#include "Component.h"

#include "Propertie.h"

#include "scripts/platform.h"

class WorldNode
{
private:
	std::string name;

public:
	std::string id;
	Eigen::Affine3f transform;
	bool enabled;
	int zIndex;
	bool visible;
	GLubyte* color;
	unsigned int category;
	std::string scriptType;
	std::map <std::string, Propertie*> properties;

	WorldNode * render_node = NULL;
	WorldNode * preListener = NULL;
	WorldNode * listener = NULL;
	Point LocalPosition;
	
	//для наследования между sys_hud
	std::string anchor = "";

	std::vector<Component *> components;
	std::vector<WorldNode *> childrens;
	


	WorldNode(Json::Value);
	~WorldNode();
	void render(const Eigen::Affine3f& parent_transform);
	void update(int deltaTime);
	void start();
	
	void setName(std::string value) {name = value;} 
	std::string getName() {return name;}
	void disable() {enabled = false;}
	void enable() {enabled = true;}
	WorldNode * getElement(Propertie *, std::string);
	Component * getComponent(std::string id);
	WorldNode * getChildByName(std::string name);
	WorldNode * createWorldNode(std::string name);
	Component * CreateComponent(Json::Value);
	WorldNode * CreateElement(Json::Value json);
	void addChildNode(WorldNode*);
	void setZIndex(int index) {zIndex = index;}
	Point getLocalPosition() const;
	Point getWorldPosition() const;
	void setWorldPosition(int, int);
	void setLocalPositionX(int);

};