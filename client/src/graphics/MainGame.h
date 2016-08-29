#pragma once

struct SDL_Window;
namespace nario {
	enum class GameState
	{
		PLAY,
		EXIT
	};
	class Sprite;
	class MainGame
	{
	public:
		MainGame();
		~MainGame();

		void run();
	private:
		void initSystem();
		void gameloop();
		void processInput();
		void drawGame();

	private:
		SDL_Window* _window;
		int _screenWidth;
		int _screenHeight;
		GameState _gameState;
		Sprite* _sprite;
	};
}