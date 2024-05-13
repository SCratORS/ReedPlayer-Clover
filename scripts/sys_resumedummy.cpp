#include "sys_resumedummy.h"

sys_resumedummy::sys_resumedummy(Json::Value json):WorldNode(json) {
	for (auto const& propertieName : json["properties"].getMemberNames()) {
		try {
			properties[propertieName] = new Propertie(json["properties"][propertieName]);
		} catch (const std::exception& ex) {
			std::cout << "***ERROR(sys_resumedummy): Except in propertie: " << propertieName << std::endl;
		}
	}
	root = getElement(properties["root"],"WorldNode");
}

void sys_resumedummy::start(WorldNode * parent)
{
	disable();
	is_select_title = false;
}