#include "helper_nodes.h"
#include "system.h"
#include "gui/gui_element.h"

extern System * _system;

namespace helper_nodes {
    std::vector<std::string> _gui_container = {"sys_resumemenu", "sys_resumedatalist" , "sys_resume_lockmode", "sys_resume_emptymode", "sys_resume_changemode",
                                                "sys_option_setting", "sys_option_languages", "sys_option_display", "sys_option", "sys_menubarU", "sys_manual",
                                                "sys_homemenu", "sys_gametitlelist", "sys_dialog", "sys_copyright_text", "sys_copyright", "Main", "gui_container"};


    std::map<std::string, std::vector<std::string>> differentTypesList = {
        {"gui_container",_gui_container}
    };

    bool isDifferentType(std::string src, std::string dest) {
        for (auto & d : differentTypesList.find(src)->second) {
            if (d == dest) return true;
        }
        return false;
    }

    std::vector<WorldNode*> getObjects(WorldNode * node, std::string type) {
        std::vector<WorldNode*> * table = new std::vector<WorldNode*>;
//        std::cout << "***TEST(helper_nodes)[getObjects]: function getObjects find type: " << type << std::endl;
        for (auto * component : node->childrens) {
//            std::cout << component->scriptType;
            if (isDifferentType(type, component->scriptType)) {
//                std::cout << " <-----";
                table->push_back(component);
                if (((GUIElement*)component)->hvc_only && !_system->is_hvc() || ((GUIElement*)component)->nes_only && !_system->is_nes()) component->disable();
            }
//            std::cout << std::endl;
        }
        return *table;
    }

    bool sort_positionComp(const WorldNode * i, const WorldNode * j) {
        Point pi = i->getLocalPosition();
        Point pj = j->getLocalPosition();
        if (pi.y == pj.y) return pi.x < pj.x;
        else return pj.y < pi.y;
    }

    bool sort_positionCompV(const WorldNode * i, const WorldNode * j) {
        Point pi = i->getLocalPosition();
        Point pj = j->getLocalPosition();
        if (pi.x == pj.x) return pj.y < pi.y;
        else return pi.x < pj.x;
    }
}