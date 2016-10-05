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

	Shader* shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
	Shader* shader2 = new Shader("shaders/basic.vert", "shaders/basic.frag");
	shader->enable();
	shader->setUniform2f("light_pos", Vector2(0.0f, 0.0f));

	shader2->enable();
	shader2->setUniform2f("light_pos", Vector2(0.0f, 0.0f));

	TileLayer layer(shader);
	TileLayer layer2(shader2);

	for (float y = -9.0f; y < 9.0f; y += 0.1)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.1)
		{
			layer.add(new Sprite(x, y, 0.08f, 0.08f, Vector4(rand() % 1000 / 1000.0f, 0, 1, 1.0f)));
		}
	}

	layer2.add(new Sprite(0, 0, 4, 4, Vector4(1, 0, 1, 1)));

	Timer time; // timer 
	float t = 0;
	unsigned int frames = 0;
	while (!window.closed())
	{
		window.clear();
		int x = window.getMouseX();
		int y = window.getMouseY(); 
		shader->enable();
		shader->setUniform2f("light_pos", Vector2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
		shader2->enable();
		shader2->setUniform2f("light_pos", Vector2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

		layer.render();
		layer2.render();

		window.update();
		frames++;
		if (time.elapsed() - t > 1.0f)
		{
			t += 1.0f;
			aplog::loginfo(frames, " fps");
			frames = 0;
		}
	}

    return 0;
}