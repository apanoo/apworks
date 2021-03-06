#pragma once
#include <chrono>
#include <ctime>
#include <string>

namespace nario {
	class TimeMgr
	{
	public:
		static TimeMgr* getInstance()
		{
			if (_instance == NULL)
			{
				_instance = new TimeMgr();
			}
			return _instance;
		}

		// return now time
		std::string getNow()
		{
			return timePointToString(_timePoint.now());
		}

	private:
		std::string timePointToString(const std::chrono::system_clock::time_point& tp)
		{
			std::time_t t = std::chrono::system_clock::to_time_t(tp);
			std::string ts = std::ctime(&t);
			ts.resize(ts.size() - 1);
			return ts;
		}

	private:
		class GC
		{
		public:
			GC() {}
			~GC()
			{
				if (_instance != NULL)
				{
					delete _instance;
					_instance = NULL;
				}
			}
		};

	private:
		std::chrono::system_clock _timePoint;
		static GC gc;
		static TimeMgr* _instance;
	};

}
