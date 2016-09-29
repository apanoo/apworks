#include <iostream>
#include <gl/glew.h>

// nario lib
#include "../nario.h"

int main(int argc, char** argv)
{
	using namespace nario;
	Window window("window", 960, 540);


	Matrix4 ortho = Matrix4().orthographicMatrix(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	
	Renderable2d sprite(Vector3(5, 5, 0), Vector2(4, 4), Vector4(1, 0, 1, 1), shader);
	Renderable2d sprite2(Vector3(7, 1, 0), Vector2(2, 3), Vector4(0.2f, 0, 1, 1), shader);
	SimpleRenderer2d renderer;

	
	shader.setUniform2f("light_pos", Vector2(0.0f, 0.0f));
	shader.setUniform4f("colour", Vector4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!window.closed())
	{
		window.clear();
		int x = window.getMouseX();
		int y = window.getMouseY(); 
		shader.setUniform2f("light_pos", Vector2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));

		renderer.submit(&sprite);
		renderer.submit(&sprite2);
		renderer.flush();

		window.update();
	}

    return 0;
}