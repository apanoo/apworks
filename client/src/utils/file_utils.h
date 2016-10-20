#pragma once
#include <string>
#include "string_utils.h"

namespace nario {
	class FileUtils
	{
	public:

		static std::string readFile(const char* filename)
		{
			char path[256];
			sprintf(path, "../../res/%s", filename);
			FILE* file = fopen(path, "rt");
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file); // file length
			char* data = new char[length + 1];  // data + '\0'
			memset(data, 0, length + 1);		// clear memory
			fseek(file, 0, SEEK_SET);			// back to begain of file
			fread(data, 1, length, file);
			fclose(file);
			std::string result(data);
			delete[] data;
			return result;
		}

		static std::string getFileExt(const std::string& filename)
		{
			return StringUtils::split(filename, '.').back();
		}
	};
}