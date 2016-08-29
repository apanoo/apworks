#include "log.h"

namespace nario {
	void log::err(std::string err)
	{
		std::cout << err << std::endl;
		std::cout << "Enter any key to quit..." << std::endl;
		int code;
		std::cin >> code;
		// other operation
	}
}
