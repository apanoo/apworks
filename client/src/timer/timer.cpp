#include "timer.h"

namespace nario {
	
	Timer::~Timer()
	{

	}

	// reset timer
	void Timer::reset()
	{
		_start = _hrClock::now();
	}

	// pass seconds
	float Timer::elapsed()
	{
		return std::chrono::duration_cast<milliseconds_type>(_hrClock::now() - _start).count() / 1000.0f;
	}

	Timer::Timer()
	{
		reset();
	}

}
