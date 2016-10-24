#include <iostream>
#include <vector>
#include <time.h>

// nario lib
#include "../nario.h"

#include "tile_layer.h"

#if 0
int main(int argc, char** argv)
{
	using namespace nario;
	Window window("window", 960, 540);

	Shader* shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
	TileLayer layer(shader);

	Texture* texture = new Texture("textures/basic.png");

	nario::AudioMgr::getInstance()->add(new nario::Audio("test", "../../res/audio/ringtones/Backroad.ogg"));

	// sprite group : example for button
	//Group* group = new Group(Matrix4().translationMatrix(Vector3(-15.0f, 5.0f, 0.0f)));
	//group->add(new Sprite(0, 0, 6, 3, Vector4(1, 1, 1, 1)));
	//group->add(new Sprite(0.5f, 0.5f, 5.0f, 2.0f, Vector4(1, 0, 1, 1)));
	//layer.add(group);

	for (float i = -16.0f; i < 16.0f; i++)
	{
		for (float j = -9.0f; j < 9.0f; j++)
		{
			layer.add(new Sprite(i, j, 0.9f, 0.9f, texture));
		}
	}

	Font* font = new Font("arial", "../../res/fonts/arial.ttf", 64);
	Label* label = new Label("nario!", 0, 0, 0xff00ff00, font);
	layer.add(label);

	nario::AudioMgr::getInstance()->get("test")->loop();
	float gain = 0.5f;
	nario::AudioMgr::getInstance()->get("test")->setVolume(gain);

	window.keyTypeHandler = [&](int key) {
		if (key == SDLK_0)
		{
			//gain += 0.05f;
			//nario::AudioMgr::getInstance()->get("test")->setVolume(gain);
			nario::AudioMgr::getInstance()->get("test")->stop();
		}
		//label->setText(std::to_string(key));
	};

	window.mouseClickHandler = [](int index) {
		if(index == SDL_BUTTON_LEFT) aplog::logwarning(index);
	};

	Timer time; // timer 
	float t = 0;
	unsigned int frames = 0;
	while (!window.closed())
	{
		window.clear();
		int x = window.getMouseX();
		int y = window.getMouseY(); 
		shader->enable();
		shader->setUniform2f("light_pos", Vector2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));

		layer.render();

		window.update();
		frames++;
		if (time.elapsed() - t > 1.0f)
		{
			t += 1.0f;
			//aplog::loginfo(frames, " fps");
			frames = 0;
		}
	}

	delete texture;
	delete font;
    return 0;
}

#endif


using namespace nario;
class Game : public Nario
{
public:
	Game()
	{

	}
	~Game()
	{
		delete layer;
		delete font;
	}

	void init() override
	{
		_window = createWindow("Game", 960, 540);

		font = new Font("arial", "../../res/fonts/arial.ttf", 32);
		font->setScale(_window->getWidth() / 32.0f, _window->getHeight() / 18.0f);
		label = new Label("", -15.5f, 8.0f, 0xff00ff00, font);

		shader = ShaderFactory::defaultShader();
		layer = new Layer(new BatchRenderer2d(), shader, Matrix4().orthographicMatrix(-16.0f, 16.0f, -9.0f, 9.0f, -1, 1));
		sprite = new Sprite(0.0f, 0.0f, 4, 4, new Texture("textures/basic.png"));
		layer->add(sprite);
		
		layer->add(label);
	}

	void render() override
	{
		layer->render();
		label->setText(std::to_string(getFps()) + " fps");
	}

	void update() override
	{
		int x = getMouseX();
		int y = getMouseY();
		shader->enable();
		shader->setUniform2f("light_pos", Vector2((float)(x * 32.0f / _window->getWidth() - 16.0f), (float)(9.0f - y * 18.0f / _window->getHeight())));
	}

	void keyPressHandler(int key) override
	{
		static float speed = 0.1f;
		switch (key)
		{
		case SDLK_w:
			sprite->setPositionY(sprite->getPosition().getY() + speed);
			break;
		case SDLK_s:
			sprite->setPositionY(sprite->getPosition().getY() - speed);
			break;
		case SDLK_a:
			sprite->setPositionX(sprite->getPosition().getX() - speed);
			break;
		case SDLK_d:
			sprite->setPositionX(sprite->getPosition().getX() + speed);
			break;
		}
	}

private:
	Layer* layer;
	Font* font;
	Label* label;
	Sprite* sprite;
	Shader* shader;

	Window* _window;
};

int main(int argc, char** argv)
{
	Game game;
	game.start();
	return 0;
}
