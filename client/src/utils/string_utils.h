#pragma once
#include <sstream>
#include <string>
#include <vector>

namespace nario {
	class StringUtils
	{
	public:
		static std::vector<std::string> split(const std::string& str, char delim)
		{
			std::vector<std::string> elems;
			std::stringstream strs(str);
			std::string item;
			while (std::getline(strs, item, delim))
			{
				elems.push_back(item);
			}
			return elems;
		}
	};
}