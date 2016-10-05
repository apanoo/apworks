#pragma once
#include "utils/stdafx.h"
#include "renderable2d.h"
#include "math/maths.h"
#include <vector>

namespace nario {
	class Renderer2d
	{
	public:
		void push(const Matrix4& matrix, bool override = false)
		{
			if (override)
			{
				_transformations.push_back(matrix);
			}
			else
			{
				_transformations.push_back(_transformations.back() * matrix);
			}
			_transformationBack = &_transformations.back();
		}

		void pop()
		{
			if (_transformations.size() > 1)
			{
				_transformations.pop_back();
			}
			_transformationBack = &_transformations.back();
		}

		virtual void begin() {}
		virtual void submit(const Renderable2d* renderable) = 0;
		virtual void end() {}
		virtual void flush() = 0;
	protected:
		Renderer2d()
		{
			_transformations.push_back(Matrix4().identityMatrix());
			_transformationBack = &_transformations.back();
		}
	protected:
		std::vector<Matrix4> _transformations;
		const Matrix4* _transformationBack;
	};
}