#pragma once
#include <string>
#include <json/json.h>
#include <eigen3/Eigen/Dense>
#include <iostream>


class Component
{
public:
	
	struct Propertie {
		std::string linkType;
		std::string linkId;
	};

	std::string type;
	bool enabled;
	std::string id;
	std::string scriptType;
	std::map <std::string, Propertie> properties;

	Component(Json::Value);
	~Component();
	void disable() {enabled = false;}
	void enable() {enabled = true;}
	void setType(std::string new_type) {type = new_type;}
	void render(const Eigen::Affine3f& transformMatrix) {}
	void update(int deltaTime) {}
	Propertie * getPropByName(std::string );
};