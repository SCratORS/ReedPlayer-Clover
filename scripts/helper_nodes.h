#ifndef _HELPER_NODES_H_
#define _HELPER_NODES_H_

#include <typeinfo>
#include <vector>
#include <string>

#include "../WorldNode.h"

namespace helper_nodes {
	std::vector<WorldNode*> getObjects(WorldNode * node, std::string type);
	bool sort_positionComp(const WorldNode *, const WorldNode *);
	bool sort_positionCompV(const WorldNode *, const WorldNode *);
	bool isDifferentType(std::string src, std::string dest);
}

#endif

