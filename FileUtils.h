#ifndef _FILEUTILS_H_
#define _FILEUTILS_H_

#include <string>

namespace FileUtils {
	std::string readFile(const std::string&);
	bool fileExists(const std::string&);
}

#endif
