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

	private:
		bool init();
		void eventHandler();

	private:
		bool _close;
		const char* _name;
		int _width, _height;
		SDL_Window* _window;
	};
}