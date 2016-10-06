#include <iostream>
#include <vector>
#include <time.h>

// nario lib
#include "../nario.h"

#if 1
int main(int argc, char** argv)
{
	using namespace nario;
	Window window("window", 960, 540);

	Shader* shader = new Shader("shaders/basic.vert", "shaders/basic.frag");

	//Texture texture("textures/basic.png");
	TileLayer layer(shader);

	Group* group = new Group(Matrix4().translationMatrix(Vector3(-15.0f, 5.0f, 0.0f)));
	group->add(new Sprite(0, 0, 6, 3, Vector4(1, 1, 1, 1)));
	group->add(new Sprite(0.5f, 0.5f, 5.0f, 2.0f, Vector4(1, 0, 1, 1)));
	layer.add(group);

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

		layer.render();

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

#endif