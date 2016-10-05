#pragma once

struct SDL_Window;
namespace nario {
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
		inline int getMouseX() const { return _mx; }
		inline int getMouseY() const { return _my; }

	private:
		bool init();
		void eventHandler();

	private:
		const char* _name;
		int _width, _height;
		SDL_Window* _window;
		int _mx, _my;
		bool _close;
	};
}