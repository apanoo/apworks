#include <iostream>
#include <vector>
#include <time.h>

// nario lib
#include "../nario.h"

#define BATCH 1

int main(int argc, char** argv)
{
	using namespace nario;
	Window window("window", 960, 540);


	Matrix4 ortho = Matrix4().orthographicMatrix(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	
	srand(time(NULL));
	std::vector<Renderable2d*> sprites;
	for (float y = 0; y < 9.0f;y += 0.05f)
	{
		for (float x = 0; x < 16.0f;x += 0.05f)
		{
			sprites.push_back(new 
#if BATCH
				Sprite
#else 
				StaticSprite
#endif
				(x, y, 0.04f, 0.04f, Vector4(rand() % 1000 / 1000.0f, 0, 1, 1)
#if !BATCH
					, shader
#endif

				));
		}
	}
#if BATCH
	BatchRenderer2d renderer;
#else
	SimpleRenderer2d renderer;
#endif
	
	shader.setUniform2f("light_pos", Vector2(0.0f, 0.0f));
	shader.setUniform4f("colour", Vector4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!window.closed())
	{
		window.clear();
		int x = window.getMouseX();
		int y = window.getMouseY(); 
		shader.setUniform2f("light_pos", Vector2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
#if BATCH
		renderer.begin();
#endif
		for (unsigned int i = 0; i < sprites.size(); ++i)
		{
			renderer.submit(sprites[i]);
		}
#if BATCH
		renderer.end();
#endif
		renderer.flush();

		std::cout << sprites.size() << std::endl;
		window.update();
	}

	sprites.clear();
    return 0;
}