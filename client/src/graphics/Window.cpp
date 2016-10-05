#include "window.h"
#include "utils/stdafx.h"
#include "log/aplog.h"

#define ErrExit(str) { \
	aplog::logerr(str);\
	_close = true;     \
	SDL_Quit();        \
}

#define NormalExit() { \
	_close = true;     \
	SDL_Quit();        \
}

nario::Window::Window(const char* name, int width, int height)
	:_name(name), _width(width), _height(height), _close(false), _mx(0), _my(0)
{
	if (!init())
	{
		ErrExit("Window init failed!");
	}
}

nario::Window::~Window()
{

}

void nario::Window::clear() const
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool nario::Window::closed()
{
	return _close;
}

void nario::Window::update()
{
	SDL_GL_SwapWindow(_window); // double swap

	/*SDL_GetWindowSize(_window, &_width, &_height);  // TODO : opt
	glViewport(0, 0, _width, _height);*/

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		aplog::logerr("OpenGL Error: " , error);
	}

	eventHandler();
}

bool nario::Window::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		_width, _height, SDL_WINDOW_OPENGL /*| SDL_WINDOW_RESIZABLE*/);
	if (_window == nullptr)
	{
		ErrExit("SDL window could not be created!");
		return false;
	}

	// opengl context
	SDL_GLContext glContex = SDL_GL_CreateContext(_window);
	if (glContex == nullptr)
	{
		ErrExit("SDL gl context coult not be created!");
		return false;
	}

	// 垂直同步开关
	SDL_GL_SetSwapInterval(0.0);

	// init glew after make context
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		ErrExit("Glew init failed!");
		return false;
	}
	else
	{
		std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
	}

	// double buffer 
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// window background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	return true;
}

void nario::Window::eventHandler()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			NormalExit();
			break;
		case SDL_MOUSEMOTION:
			_mx = event.motion.x;
			_my = event.motion.y;
			break;
		}
	}
}

