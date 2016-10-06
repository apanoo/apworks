#pragma once
#include <string>
#include <FreeImage.h>
#include "utils/stdafx.h"

namespace nario {
	class ResourcesMgr
	{
	public:
		static ResourcesMgr* getInstance()
		{
			if (_instance == NULL)
			{
				init();
				_instance = new ResourcesMgr();
			}
			return _instance;
		}
		std::string loadText(const char* filename);
		BYTE* loadImage(const char* filename, GLsizei* width, GLsizei* height);

	private:
		static void init();
		static void destroy();

		class GC
		{
		public:
			GC() {}
			~GC()
			{
				if (_instance != NULL)
				{
					destroy();
					delete _instance;
					_instance = NULL;
				}
			}
		};

	private:
		static GC gc;
		static ResourcesMgr* _instance;
	};
}
