#pragma once
#include "renderable2d.h"
#include "math/maths.h"
#include <vector>

namespace nario {

	class Renderer2d;
	class Group : public Renderable2d
	{
	public:
		Group(const Matrix4& transform);
		~Group();

		void submit(Renderer2d* renderer) const override;
		void add(Renderable2d* renderable);
	private:
		std::vector<Renderable2d*> _renderables;
		Matrix4 _transformation;
	};
}