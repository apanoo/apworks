#pragma once
#include <functional>

struct SDL_Window;
namespace nario {
#define MAX_KEY 256
#define MAX_BTN 16

	// Event Handler
	typedef std::function<void(int)> EventHandler;

	class Window
	{
	public:
		Window(const char* name, int width, int height);
		~Window();
		void clear() const;
		bool closed();
		void update();

		inline int getWidth() const { return _width; }
		inline int getHeight() const { return _height; }
		inline int getMouseX() const { return _wx; }
		inline int getMouseY() const { return _wy; }

	private:
		bool init();
		void eventHandler();

	private:
		const char* _name;
		int _width, _height;
		SDL_Window* _window;
		int _wx, _wy;
		bool _close;
		bool _keyState[MAX_KEY];
		bool _mouseState[MAX_BTN];

	// public handler
	public:
		EventHandler keyTypeHandler;
		EventHandler keyPressHandler;
		EventHandler mouseClickHandler;
		EventHandler mousePressHandler;
	};
}