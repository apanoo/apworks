#pragma once
#include "utils/stdafx.h"
#include "renderable2d.h"
#include "math/maths.h"

namespace nario {
	class Renderer2d
	{
	protected:
		virtual void submit(Renderable2d* renderable) = 0;
		virtual void flush() = 0;
	};
}