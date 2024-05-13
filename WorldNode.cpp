#include "WorldNode.h"

#include "SpriteComponent.h"
#include "SoundComponent.h"
#include "TextureComponent.h"
#include "AnimatedSpriteComponent.h"
#include "AnimatorComponent.h"
#include "LabelComponent.h"
#include "CameraComponent.h"

#include "GUIManager.h"

#include "scripts/snd_component.h"
#include "scripts/sys_hud.h"
#include "scripts/sys_resumedummy.h"
#include "scripts/sys_resume_card.h"
#include "scripts/sys_resume_floating_card.h"

#include "scripts/gui/gui.h"
#include "scripts/gui/gui_button.h"
#include "scripts/gui/gui_element.h"

#include "scripts/sys_home_floating_cards.h"
#include "scripts/effect_smoke.h"
#include "scripts/sys_resume_float_wing.h"
#include "scripts/sys_homemenu.h"
#include "scripts/store.h"

extern gui * GUI;
extern _Store * Store;


WorldNode::WorldNode(Json::Value json) {
	for (auto const& propertieName : json["properties"].getMemberNames()) {
		try {		
			if (propertieName == "render_node") properties[propertieName] = new Propertie(json["properties"][propertieName]);
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(WorldNode): Except in propertie: " << propertieName << std::endl;
		}
	}

	id = json["id"].asString();
	name = json["name"].asString();
	visible = json["visible"].asBool();
	category = json["category"].asInt();
	zIndex = json["zIndex"].asInt();
	enabled = json["enabled"].asBool();
	scriptType = json["scriptType"].asString();

	Eigen::Matrix4f eMatrix;
	eMatrix <<
	 	json["transform"][0].asFloat(),json["transform"][1].asFloat(), 0.0, json["transform"][2].asFloat(),
		json["transform"][3].asFloat(),json["transform"][4].asFloat(), 0.0, json["transform"][5].asFloat(),
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0;

	transform.setIdentity();
	transform = (Eigen::Matrix4f&)eMatrix;

	/*Ну допустим*/
	LocalPosition.x = json["transform"][2].asInt();
	LocalPosition.y = json["transform"][5].asInt();

	for (Json::Value componentJson: json["components"]) {
		components.push_back(CreateComponent(componentJson));
	}		
	for (Json::Value elementJson: json["children"]) addChildNode(CreateElement(elementJson));

	std::sort(childrens.begin(), childrens.end(), [](auto && l, auto && r) { return l->zIndex < r->zIndex; });

	if (properties["render_node"]) render_node =  getElement(properties["render_node"], "WorldNode");

}

WorldNode::~WorldNode() {
	
}

WorldNode * WorldNode::CreateElement(Json::Value json){
	std::string scriptType = json["scriptType"].asString();
	std::string name = json["name"].asString();
	if (scriptType == "effect_smoke") return new effect_smoke(json);
	if (scriptType == "sys_hud") return new sys_hud(json);
	if (scriptType == "sys_homemenu") return new sys_homemenu(json);
	if (scriptType == "sys_resumedummy") return new sys_resumedummy(json);
	if (scriptType == "sys_home_floating_cards") return new sys_home_floating_cards(json);
	if (scriptType == "sys_resume_card") return new sys_resume_card(json);
	if (scriptType == "sys_resume_float_wing") return new sys_resume_float_wing(json);
	if (scriptType == "sys_resume_floating_card") return new sys_resume_floating_card(json);
	if (scriptType == "GUIElement") return new GUIElement(json);
	if (scriptType == "GUIButton") return new GUIButton(json);
	return new WorldNode(json);
}

Component * WorldNode::CreateComponent(Json::Value json){
	std::string type = json["type"].asString();
	std::string scriptType = json["scriptType"].asString();
	if (type == "ScriptComponent") {
		if (scriptType == "GUI") return GUI = new gui(json);
		if (scriptType == "Store") return Store = new _Store(json);
		return new ScriptComponent(json);
	}
	if (type == "LabelComponent") return new LabelComponent(json);
	if (type == "CameraComponent") return new CameraComponent(json);
	if (type == "AnimatorComponent") return new AnimatorComponent(json);
	if (type == "SpriteComponent") return new SpriteComponent(json);
	if (type == "TextureComponent") return new TextureComponent(json);
	if (type == "AnimatedSpriteComponent") return new AnimatedSpriteComponent(json);
	if (type == "SoundComponent") {
		if (scriptType == "snd_component") return new snd_component(json);
		else return new SoundComponent(json);
	}
	return new Component(json);
}

Component * WorldNode::getComponent(std::string id) {
	if (id == "") return NULL;
	if (id == "VisualComponent") {
		//Ох это жудкий костыль...
		for (auto &component:components) {
			if (component->type == "SpriteComponent") return component;
			if (component->type == "LabelComponent") return component;
		}
		return NULL;
	}
	for (auto &component:components) if (component->id == id) return component;
	for (auto &element:childrens) {
			Component * component = element->getComponent(id);
			if (component) return component;
		}
	return NULL;
}

WorldNode * WorldNode::getElement(Propertie * propertie, std::string currentType) {
	if (propertie) {
		if (propertie->linkId!="") {
			if (this->id == propertie->linkId) {
				if (this->scriptType == currentType && propertie->linkType == "Component"  || propertie->linkType == "WorldNode") return this;
				else {
					std::cout << "***ERROR("<<currentType<<"): Type "<< scriptType <<" not supported" << std::endl;
					return NULL;				
				}
			} else {
				for (auto &element:childrens) {
					WorldNode * node = element->getElement(propertie, currentType);
					if (node) return node; 
				}
				return NULL;
			} 
		} else {
			std::cout << "***WARNING("<<currentType<<") "<< this->id <<" : linkId is empty" << std::endl;
			return NULL;
		}
	} else return NULL;		
}

WorldNode * WorldNode::getChildByName(std::string name) {
	if (name != "") {
		if (this->name == name) return this;
		for (auto &element:childrens) {
			WorldNode * node = element->getChildByName(name);
			if (node) return node;
		}
	}
	return NULL;
}

WorldNode * WorldNode::createWorldNode(std::string name) {
	std::string text ="{\"id\":\"\",\"name\":\""+name+"\",\"transform\":[1,0,0,0,1,0],\"enabled\":false,\"zIndex\":0,\"visible\":false,\"color\":[1,1,1,1],\"components\":[],\"children\":[],\"scriptType\":\"WorldNode\",\"properties\":{}}";
	Json::CharReaderBuilder builder;
	Json::CharReader * reader = builder.newCharReader();
	Json::Value root;
	std::string errors;
	bool parsingSuccessful = reader->parse(text.c_str(), text.c_str() + text.size(), &root, &errors);
	delete reader;
	WorldNode * node = NULL;
	if ( !parsingSuccessful ) node = new WorldNode(root);
	return node;
}

void WorldNode::addChildNode(WorldNode * node){
	childrens.push_back(node);
}

void WorldNode::render(const Eigen::Affine3f& parent_transform)
{	
	if (!(visible&&enabled)) return;
	Eigen::Affine3f trans = parent_transform * transform;
	for (auto * component : components) {
		if (component->scriptType == "SpriteComponent") ((SpriteComponent*)component)->render(trans);
		if (component->scriptType == "TextureComponent") ((TextureComponent*)component)->render(trans);
	}
	for (auto * children : childrens) children->render(trans);
}


void WorldNode::start() {
	for (auto * component : components) {
		if (component->type == "ScriptComponent"){
			if (component->scriptType == "GUI") ((gui*)component)->start(new GUIManager(this, (ScriptComponent*)component));
			if (component->scriptType == "Store") ((_Store*)component)->start(this);
		}
	}

	for (auto * children : childrens) {
		if (children->scriptType == "effect_smoke") ((effect_smoke*)children)->start(this);
		if (children->scriptType == "sys_hud") ((sys_hud*)children)->start(this);
		if (children->scriptType == "sys_homemenu") ((sys_homemenu*)children)->start(this);
		if (children->scriptType == "sys_resumedummy") ((sys_resumedummy*)children)->start(this);
		if (children->scriptType == "sys_home_floating_cards") ((sys_home_floating_cards*)children)->start(this);
		if (children->scriptType == "sys_resume_card") ((sys_resume_card*)children)->start(this);
		if (children->scriptType == "sys_resume_float_wing") ((sys_resume_float_wing*)children)->start(this);
		if (children->scriptType == "sys_resume_floating_card") ((sys_resume_floating_card*)children)->start(this);
		if (children->scriptType == "gui_container") ((gui_container*)children)->start(this);
		if (children->scriptType == "GUIElement") ((GUIElement*)children)->start(this);
		if (children->scriptType == "GUIButton") ((GUIButton*)children)->start(this);
		children->start();
	}
}

void WorldNode::update(int deltaTime)
{
	if (!enabled) return;
	for (auto * component : components) component->update(deltaTime);
	for (auto * children : childrens) children->update(deltaTime);
}

Point WorldNode::getLocalPosition() const{
	std::cout << "***TO-DO(WorldNode): function getLocalPosition() need modifed" << std::endl;
	return LocalPosition;
}

Point WorldNode::getWorldPosition() const{
	std::cout << "***TO-DO(WorldNode): function getWorldPosition() need modifed" << std::endl;
	return LocalPosition;
}

void WorldNode::setWorldPosition(int x, int y) {
	std::cout << "***TO-DO(WorldNode): function setWorldPosition() need modifed" << std::endl;
}

void WorldNode::setLocalPositionX(int x) {
	LocalPosition.x = x;
	Eigen::Matrix4f eMatrix;
	eMatrix <<
	 	1.0, 0.0, 0.0, float(x),
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0;

	Eigen::Affine3f set_matrix;	
	set_matrix.setIdentity();
	set_matrix = (Eigen::Matrix4f&)eMatrix;
	transform = transform * set_matrix;
}