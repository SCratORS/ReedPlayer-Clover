#include "dbg_menu_final.h"

dbgMenu::dbgMenu(){

}

void dbgMenu::entry(std::string name, WorldNode * node) {
	entrys.insert(make_pair(name, node));
}
