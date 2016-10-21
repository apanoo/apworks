#include <gl/glew.h>

#include "log/aplog.h"
#include "math/maths.h"
#include "timer/timer.h"
#include "utils/file_utils.h"

#include "graphics/window.h"
#include "graphics/shader.h"
#include "graphics/buffer/vertex_array.h"
#include "graphics/buffer/index_buffer.h"
#include "graphics/2d/renderer2d.h"
#include "graphics/2d/renderable2d.h"
#include "graphics/2d/sprite.h"
#include "graphics/2d/batch_renderer2d.h"
#include "graphics/2d/layer.h"
#include "graphics/2d/group.h"
#include "graphics/texture.h"
#include "graphics/2d/label.h"
#include "graphics/2d/font.h"

#include "audio/audio.h"
#include "audio/audio_mgr.h"

namespace nario {
#define MAX_KEY 256
#define MAX_BTN 16
	class Nario
	{
	public:
		void start()
		{
			init();
			run();
		}

		inline int getMouseX() const { return _mx; }
		inline int getMouseY() const { return _my; }

	protected:
		Nario() 
			: _frames(0), _updates(0)
		{
			for (size_t i = 0; i < MAX_KEY; i++)
			{
				_keyState[i] = false;
			}
			for (size_t i = 0; i < MAX_BTN; i++)
			{
				_mouseState[i] = false;
			}
		}
		virtual ~Nario() 
		{
			delete _window;
			delete _timer;
		}

		Window* createWindow(const char* name, int width, int height)
		{
			_window = new Window(name, width, height);
			return _window;
		}

		// initialization
		virtual void init() = 0;

		// run once per second
		virtual void tick() {};

		// run 60 times per second
		virtual void update() {};

		// run as fast as possible
		virtual void render() = 0;

		virtual void keyTypeHandler(int key) {}
		virtual void keyPressHandler(int key) {}
		virtual void mouseClickHandler(int index) {}
		virtual void mousePressHandler(int index) {}

		const unsigned int getFps() const { return _frames; }
		const unsigned int getUps() const { return _updates; }

	private:
		void eventUpdate()
		{
			// key press handler
			for (int key = 0; key < MAX_KEY; ++key)
			{
				if (_keyState[key])
				{
					keyPressHandler(key);
				}
			}

			for (int index = 0; index < MAX_BTN; ++index)
			{
				if (_mouseState[index])
				{
					mousePressHandler(index);
				}
			}
		}

		void run()
		{
			_timer = new Timer();
			float time = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;
			unsigned int frames = 0;
			unsigned int updates = 0;
			while (!_window->closed())
			{
				_window->clear();
				if (_timer->elapsed() - updateTimer > updateTick)
				{
					updates++;
					update();
					eventUpdate(); // check press event 60 times per second
					updateTimer += updateTick;
				}

				render();

				_window->update();

				/**
				* must handle event after render() and update() !
				* because if shutdown window and release memory!
				* then run render() func will failed!
				*/
				eventHandler(); 

				frames++;
				if (_timer->elapsed() - time > 1.0f)
				{
					time += 1.0f;

					_frames = frames;
					_updates = updates;

					frames = 0;
					updates = 0;

					tick();
				}
			}
		}

		void eventHandler()
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					_window->shutdown();
					break;
				case SDL_MOUSEMOTION:
					_mx = event.motion.x;
					_my = event.motion.y;
					break;
				case SDL_KEYDOWN:
				{
					SDL_Keycode key = event.key.keysym.sym;
					if (key >= MAX_KEY) return;

					// key type handler
					if (!_keyState[key])
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
					if (!_mouseState[index])
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

	private:
		Window* _window;
		Timer* _timer; // timer 
		unsigned int _frames;
		unsigned int _updates;

		int _mx, _my;

		bool _keyState[MAX_KEY];
		bool _mouseState[MAX_BTN];
	};
}

///** Export function
//* API rule -> define in header files (header.h):
//*/
//#ifdef EXPORT_NARIO_API
//#define NARIO_PAI __declspec(dllexport)   // if export like C style you should : #define NARIO_PAI extern "C" __declspec(dllexport)
//#else
//#define NARIO_PAI __declspec(dllimport)   // if export like C style you should : #define NARIO_PAI extern "C" __declspec(dllimport)
//#endif // EXPORT_NARIO_API
//// define function:
// NARIO_PAI void function();
///**
//* API rule -> define in source files (header.cpp):
//*/
//#define EXPORT_NARIO_API
//#include "header.h"
//// function
// void function() {}

/// Export class: class NARIO_PAI classname {}; 这时导出方式不能用"C" style
// "C" style方式导出时函数签名和函数名一样，可用于显示链接动态库
// 非"C" style方式导出时函数签名在函数名基础上增加随机字符，因此不可用于显示链接动态库