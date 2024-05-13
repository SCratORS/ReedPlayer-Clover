#include "gui_layout.h"
#include <iostream>
#include <ostream>


GUILayout::GUILayout() {

}

void GUILayout::initialize(int hGap, int vGap) {
	std::cout << "***TO-DO(GUILayout): function initialize() need modifed" << std::endl;
}

void GUILayout::pushBackElement(WorldNode * node) {
	std::cout << "***TO-DO(GUILayout): function pushBackElement() need modifed" << std::endl;
}
void GUILayout::resume(bool need_refresh) {
	refreshSuspended = false;
	if (need_refresh) refresh();
}
void GUILayout::suspend() {
	refreshSuspended = true;
}

void GUILayout::refresh() {
	std::cout << "***TO-DO(GUILayout): function refresh() need modifed" << std::endl;
}