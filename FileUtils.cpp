#include "FileUtils.h"


namespace FileUtils { 
	std::string readFile(const std::string& fileName) {
		std::string body = "";
		
		FILE* file = fopen(fileName.c_str(), "r");
		if (!file) return body;

		fseek(file, 0, SEEK_END);
			size_t size = ftell(file);

			body.resize(size);
			
		fread(const_cast<char*>(body.data()), size, 1, file);
		fclose(file);

		return body;
	}

	bool fileExists(const std::string& fileName) {
		if (FILE *file = fopen(fileName.c_str(), "r")) {
	        fclose(file);
	        return true;
	    } else {
	        return false;
	    }
	}

}
