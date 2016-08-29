#include <GL/glew.h>
#include <SDL.h>
#include "MainGame.h"
#include "../log/log.h"
#include "Sprite.h"

namespace nario {

	MainGame::MainGame()
		:_window(nullptr), _screenWidth(1024), _screenHeight(768), _gameState(GameState::PLAY)
	{
	}

	MainGame::~MainGame()
	{

	}

	void MainGame::run()
	{
		initSystem();
		_sprite = new Sprite();
		_sprite->init(-1.0f, -1.0f, 1.0f, 1.0f);

		gameloop();
	}

	void MainGame::initSystem()
	{
		// init SDL
		SDL_Init(SDL_INIT_EVERYTHING);
	
		_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			_screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
		if (_window == nullptr)
		{
			log::err("SDL window could not be created!");
			SDL_Quit();
		}

		// opengl context
		SDL_GLContext glContex = SDL_GL_CreateContext(_window);
		if (glContex == nullptr)
		{
			log::err("SDL gl context coult not be created!");
			SDL_Quit();
		}

		// init glew 
		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			log::err("Glew init failed!");
			SDL_Quit();
		}

		// double buffer 
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		// window background color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void MainGame::gameloop()
	{
		while (_gameState != GameState::EXIT)
		{
			processInput();
			drawGame();
		}
	}

	/**
	* Event Handler
	*/
	void MainGame::processInput()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				auto mousx = event.motion.x;
				auto mousy = event.motion.y;
				break;
			}
		}
	}

	void MainGame::drawGame()
	{
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_sprite->draw();

		// double buffer should to swap buffer
		SDL_GL_SwapWindow(_window);
	}
}
