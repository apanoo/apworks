#pragma once
#include <SDL.h>

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();
	void initSystem();
private:
	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
};