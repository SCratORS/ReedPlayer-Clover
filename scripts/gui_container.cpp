#include "gui_container.h"
#include "helper_nodes.h"

#include "gui/gui_hlayout.h"

using namespace helper_nodes;

gui_container::gui_container(Json::Value json):GUIElement(json) {
	for (auto const& propertieName : json["properties"].getMemberNames()) {
		try {
			if (propertieName=="autoGap") autoGap = json["properties"][propertieName].asBool();
			else if (propertieName=="autoPosition") autoPosition = json["properties"][propertieName].asBool();
			else if (propertieName=="setListener") setListener = json["properties"][propertieName].asBool();
			else if (propertieName=="VGap") VGap = json["properties"][propertieName].asInt();
			else if (propertieName=="HGap") HGap = json["properties"][propertieName].asInt();
			else if (propertieName=="neighborDirection") neighborDirection = json["properties"][propertieName].asString();
			else if (propertieName=="neighborDirection") neighborDirection = json["properties"][propertieName].asString();
			else if (propertieName=="layoutType") layoutType = json["properties"][propertieName]["scriptTypeVariable"].asString();
			else if (propertieName=="elementType") elementType = json["properties"][propertieName]["scriptTypeVariable"].asString();
 			else if (propertieName == "elementArray") {
				for (Json::Value elArray:json["properties"][propertieName]) {
					WorldNode * component = getElement(new Propertie(elArray),"WorldNode");
					if (component) elementArray.push_back(component);
					else std::cout << "***ERROR(gui_container)[elementArray]: Component not found: " << elArray["linkId"].asString() << std::endl;		
				}
			} else properties[propertieName] = new Propertie(json["properties"][propertieName]);
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(gui_container): Except in propertie: " << propertieName << std::endl;
		}
	}
	
	elements = getElement(properties["elements"],"WorldNode");
}

void gui_container::start(WorldNode * parent){
	if (!elements) {
		elements = getChildByName("elements");
		if (!elements) {
			elements = createWorldNode("elements");
			elements->setZIndex(1);
			addChildNode(elements);
		}
	}
	buildElements(parent);
}


void gui_container::buildElements(WorldNode * parent)
{
	std::vector<WorldNode *> _array_of_elements = elementArray;

	if (!elementArray.size()) {
		_array_of_elements = getObjects(elements, elementType!=""?elementType:"GUIElement");
		bool (*sort_function) (const WorldNode *, const WorldNode *) = sort_positionComp;
		if (neighborDirection=="vertical_glid") sort_function = sort_positionCompV;
		std::sort(_array_of_elements.begin(), _array_of_elements.end(), sort_function);
	}

	if (!_array_of_elements.size()) std::cout << "nodes empty!! " << getName() << std::endl;

	WorldNode * element1 = _array_of_elements[0]; //Возможно???
	
	if (layoutType!="") {
			std::cout << "**************************" << std::endl;
		if (layoutType=="GUIHLayout") layout = new GUIHLayout();
		else layout = new GUILayout();
		layout->suspend();
		Point p = elements->getWorldPosition();
		int hGap = HGap;
		int vGap = VGap;
		WorldNode * element1 = _array_of_elements[1];
		WorldNode * element2 = _array_of_elements[2];

		if (_array_of_elements[1] && autoPosition) p = element1->getWorldPosition();

		if (element1 && element2 && autoGap) {
			Point p1 = element1->getWorldPosition();
			Point p2 = element2->getWorldPosition();
			hGap = p2.x - p1.x; 
			vGap = -(p2.y - p1.y);
		}
		std::cout << "*************INITIALIZE" << std::endl;
		layout->initialize(hGap, vGap);
		std::cout << "*************SETWORLD" << std::endl;
		elements->setWorldPosition(p.x, p.y);
		for (auto * component:_array_of_elements) layout->pushBackElement(component);
		layout->resume(true);
	}

	for (auto * component : _array_of_elements) {
		if (setListener) component->listener = this;
		element1->preListener = this; //---- ???
	}

	elementArray = _array_of_elements;

	if (focus && std::find(elementArray.begin(),elementArray.end(),focus)!=elementArray.end()) current = focus;
	else current = elementArray[0];
	repeatedTimes = 0;
}