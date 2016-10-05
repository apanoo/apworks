#pragma once
#include <chrono>

namespace nario {
	class Timer
	{
	public:
		Timer();
		~Timer();

		void reset();
		float elapsed();

	private:
		typedef std::chrono::high_resolution_clock _hrClock;
		typedef std::chrono::duration<float, std::milli> milliseconds_type;
		std::chrono::time_point<_hrClock> _start;
	};
}