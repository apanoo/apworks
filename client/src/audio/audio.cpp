#include "audio.h"
#include "audio_mgr.h"

namespace nario {

	void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
	{
		gc_int32* flag = (gc_int32*)(in_context);
		*flag = 1;
		ga_handle_destroy(in_handle);
	}

	void loopOnFinish(ga_Handle* in_handle, void* in_context)
	{
		// destroy
		ga_handle_destroy(in_handle);

		// play again
		Audio* audio = (Audio*)in_handle->sound;
		if (audio != nullptr)
		{
			audio->loop();
		}
	}
}

nario::Audio::Audio(const std::string& name, const std::string& filename)
	: _filepath(filename), _name(name)
{
	_sound = gau_load_sound_file(filename.c_str(), "ogg");
}

nario::Audio::~Audio()
{
	ga_sound_release(_sound);
}

//#if _WIN32
//	#include <windows.h>
//#endif
void nario::Audio::play()
{
	gc_int32 quit = 0;
	_handle = gau_create_handle_sound(AudioMgr::_mixer, _sound, &setFlagAndDestroyOnFinish, &quit, NULL);
	ga_handle_play(_handle);

//	while (!quit)
//	{
//		gau_manager_update(AudioMgr::_mgr);
//#if _WIN32
//		Sleep(1);
//#endif
//	}
}

void nario::Audio::loop()
{
	gc_int32 quit = 0;
	_handle = gau_create_handle_sound(AudioMgr::_mixer, _sound, &loopOnFinish, &quit, NULL);
	_handle->sound = this;
	ga_handle_play(_handle);
}

void nario::Audio::pause()
{

}

void nario::Audio::stop()
{

}

