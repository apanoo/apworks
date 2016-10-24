#pragma once
#include <functional>

struct SDL_Window;
namespace nario {

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
		void shutdown();

		inline int getWidth() const { return _width; }
		inline int getHeight() const { return _height; }
		
	private:
		bool init();

	private:
		const char* _name;
		int _width, _height;
		SDL_Window* _window;
		bool _close;
	};
}