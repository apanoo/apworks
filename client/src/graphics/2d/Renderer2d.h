#pragma once
#include "utils/stdafx.h"
#include "renderable2d.h"
#include "math/maths.h"

namespace nario {
	class Renderer2d
	{
	public:
		virtual void begin() {}
		virtual void submit(const Renderable2d* renderable) = 0;
		virtual void end() {}
		virtual void flush() = 0;
	};
}