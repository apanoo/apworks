#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include "timer/time_mgr.h"

namespace nario {

#define fg_blue FOREGROUND_BLUE
#define fg_red FOREGROUND_RED
#define fg_green FOREGROUND_GREEN
#define fg_intensity FOREGROUND_INTENSITY
#define fg_yellow (FOREGROUND_RED | FOREGROUND_GREEN)
#define fg_default (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

	class aplog
	{
	public:
		// level 4: log err 
		template <typename...Args>
		static void logerr(Args...args)
		{
			colorInfo(fg_red, args...);
		}

		// level 3: log warning
		template <typename...Args>
		static void logwarning(Args...args)
		{
			colorInfo(fg_yellow, args...);
		}

		// level 2: log info
		template <typename...Args>
		static void loginfo(Args...args)
		{
			colorInfo(fg_intensity, args...);
		}

		// level 1: log debug
		template <typename...Args>
		static void logdebug(Args...args)
		{
			colorInfo(fg_default, args...);
		}

	private:
		template <typename...Args>
		static void colorInfo(int color, Args...args)
		{
			if (_color != color)
			{
				setColorLight(color);
			}
			info("[", TimeMgr::getInstance()->getNow(), "]", ": ", args...);
		}

		// info
		template <typename T, typename...Args>
		static void info(T h, Args... args) {
			print(h);
			aplog::info(args...);
		}

		// info end
		template <typename T>
		static void info(T h) {
			print(h);
			std::cout << std::endl;
			if (_color != fg_default)
			{
				_color = fg_default;
				setColor(fg_default);
			}
		}

		template <typename T>
		static void print(T str) {
			std::cout << str;
		}

		// for std string
		template <>
		static void print<std::string>(std::string str) {
			print(str.c_str());
		}

		static void setColor(int color) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
		}

		static void setColorLight(int color) {
			_color = color;
			setColor(color | FOREGROUND_INTENSITY);
		}

	private:
		static int _color;
	};
}