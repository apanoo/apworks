#pragma once
#include "utils/StdAfx.h"
#include "Renderable2d.h"
#include "math/Maths.h"

namespace nario {
	class Renderer2d
	{
	protected:
		virtual void submit(Renderable2d* renderable) = 0;
		virtual void flush() = 0;
	};
}