#include "simple_renderer2d.h"

void nario::SimpleRenderer2d::submit(const Renderable2d* renderable)
{
	_renderQueue.push_back((const StaticSprite*)renderable);
}

void nario::SimpleRenderer2d::flush()
{
	while (!_renderQueue.empty())
	{
		const StaticSprite* renderable = _renderQueue.front();
		renderable->getVAO()->bind();
		renderable->getIBO()->bind();

		// ´¦ÀíÎ»ÖÃ
		renderable->getShader().setUniformMat4("ml_matrix", Matrix4().translationMatrix(renderable->getPosition()));

		// draw
		glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

		renderable->getIBO()->unbind();
		renderable->getVAO()->unbind();

		_renderQueue.pop_front();
	}
}
