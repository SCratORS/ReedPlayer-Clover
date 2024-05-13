#include "sys_hud.h"
#include "system.h"
#include <algorithm>

#include "../SpriteComponent.h"
#include "../LabelComponent.h"

extern System * _system;

sys_hud::sys_hud(Json::Value node):WorldNode(node)
{
	for (auto const& propertieName : node["properties"].getMemberNames()) {
		try {
			if (propertieName=="VGap") VGap = node["properties"][propertieName].asInt();
			if (propertieName=="anchor") anchor = node["properties"][propertieName].asString();
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(sys_hud): Except in propertie: " << propertieName << std::endl;
		}
	}
}

void sys_hud::start(WorldNode * parent)
{
	if (anchor == "") anchor = parent->anchor;
	if (!elementList.size()) elementList = {};
	elementList = childrens;

	std::sort(elementList.begin(), elementList.end(), [](auto && l, auto && r) { return l->getName() < r->getName(); });

	Point p = getLocalPosition();
	orgX = p.x;orgY = p.y;

	refresh();
	_system->hud.push_back(this);
}

void sys_hud::refresh() {
	int vGap = VGap;
	float bottom = 0.0;
	std::map<WorldNode *, float> innerList = {};
	float right = 0.0;
	for (WorldNode * childNode : elementList) {
		float size_x = 0;
		float size_y = 0;

		if (childNode->scriptType == "sys_hud") {
			((sys_hud*)childNode)->refresh();
		}

		//function getSize in children WorldNode not defined!
//		if (childNode.getSize) {
//			Point * p = childNode.getSize();
//			size_x = p->x; size_y = p->y;
//		} else {
			Component * component = childNode->getComponent("VisualComponent");
			Point p;
			if (component) {
				if (component->type == "SpriteComponent") p = ((SpriteComponent*)component)->getSize();
				if (component->type == "LabelComponent") p = {(float)((LabelComponent*)component)->wrapWidth,16.0};
				size_x = p.x; size_y = p.y;		
			}
//		}

		innerList[childNode] = right + size_x / 2;
		right += size_x + vGap;
		bottom = std::max(bottom, size_y);
	}
	float left = (right - vGap) / 2;

	if (anchor == "left") left = 0;
	else if (anchor == "center") left = right / 2;
	else if (anchor == "right") left = right;

	for (WorldNode * childNode : elementList) {
		childNode->setLocalPositionX(round(innerList[childNode] - left));
	}
	sizeX = round(right);
	sizeY = round(bottom);
}

Point sys_hud::getSize() {
	return {(float)sizeX, (float)sizeY};
}