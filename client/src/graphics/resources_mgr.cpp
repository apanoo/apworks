#include "resources_mgr.h"
#include "utils/file_utils.h"
#include "utils/image_utils.h"

namespace nario {

	std::string ResourcesMgr::loadText(const char* filename)
	{
		return FileUtils::readFile(filename);
	}

	BYTE* ResourcesMgr::loadImage(const char* filename, GLsizei* width, GLsizei* height, GLsizei* bits)
	{
		return ImageUtils::loadImage(filename, width, height, bits);
	}

	void ResourcesMgr::init()
	{
		// init freeimage
		FreeImage_Initialise();
	}

	void ResourcesMgr::destroy()
	{
		// destroy freeimage
		FreeImage_DeInitialise();
	}

	ResourcesMgr* ResourcesMgr::_instance = NULL;
	ResourcesMgr::GC ResourcesMgr::gc;
}