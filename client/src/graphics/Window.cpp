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
	:_name(name), _width(width), _height(height), _close(false), _wx(0), _wy(0)
	,keyTypeHandler(nullptr)
	,keyPressHandler(nullptr)
	,mouseClickHandler(nullptr)
	,mousePressHandler(nullptr)
{
	for (size_t i = 0; i < MAX_KEY; i++)
	{
		_keyState[i] = false;
	}
	for (size_t i = 0; i < MAX_BTN; i++)
	{
		_mouseState[i] = false;
	}
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

	// key press handler
	for (int key = 0; key < MAX_KEY; ++key)
	{
		if (keyPressHandler != nullptr && _keyState[key])
		{
			keyPressHandler(key);
		}
	}

	for (int index = 0; index < MAX_BTN; ++index)
	{
		if (mousePressHandler != nullptr && _mouseState[index])
		{
			mousePressHandler(index);
		}
	}

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
	SDL_GL_SetSwapInterval(0);

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

	// enable blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
			_wx = event.motion.x;
			_wy = event.motion.y;
			break;
		case SDL_KEYDOWN:
		{
			SDL_Keycode key = event.key.keysym.sym;
			if (key >= MAX_KEY) return;

			// key type handler
			if (keyTypeHandler != nullptr && !_keyState[key])
			{
				keyTypeHandler(key);
			}
			_keyState[key] = true;
		}
			break;
		case SDL_KEYUP:
		{
			SDL_Keycode key = event.key.keysym.sym;
			if (key >= MAX_KEY) return;
			_keyState[key] = false;
		}
			break;
		case SDL_MOUSEBUTTONDOWN:
		{
			int index = (int)event.button.button;
			if (index >= MAX_BTN) return;

			// mouse click handler
			if (mouseClickHandler != nullptr && !_mouseState[index])
			{
				mouseClickHandler(index);
			}
			_mouseState[index] = true;
		}
			break;
		case SDL_MOUSEBUTTONUP:
		{
			int index = (int)event.button.button;
			if (index >= MAX_BTN) return;
			_mouseState[index] = false;
		}
			break;
		}
	}
}

