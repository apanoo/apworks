#pragma once
#include <string>
#include <time.h>
#include <iostream>
#include <atltime.h>

namespace nario {

	class log
	{
	public:
		static void err(LPCTSTR pstrFormat, ...);
		static void info(LPCTSTR pstrFormat, ...);
	};
}