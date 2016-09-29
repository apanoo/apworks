#include "SimpleRenderer2d.h"

void nario::SimpleRenderer2d::submit(Renderable2d* renderable)
{
	_renderQueue.push_back(renderable);
}

void nario::SimpleRenderer2d::flush()
{
	while (!_renderQueue.empty())
	{
		Renderable2d* renderable = _renderQueue.front();
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
