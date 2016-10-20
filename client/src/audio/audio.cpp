#include "audio.h"
#include "audio_mgr.h"
#include "utils/file_utils.h"

namespace nario {

	void destroyOnFinish(ga_Handle* in_handle, void* in_context)
	{
		Audio* audio = (Audio*)in_handle->sound;
		audio->stop();
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
	: _filepath(filename), _name(name), _playing(false), _handle(nullptr)
{
	_sound = gau_load_sound_file(filename.c_str(), FileUtils::getFileExt(filename).c_str());
}

nario::Audio::~Audio()
{
	ga_sound_release(_sound);
}

void nario::Audio::play()
{
	gc_int32 quit = 0;
	_handle = gau_create_handle_sound(AudioMgr::_mixer, _sound, &destroyOnFinish, &quit, NULL);
	_handle->sound = this;
	ga_handle_play(_handle);
	_playing = true;
}

void nario::Audio::loop()
{
	gc_int32 quit = 0;
	_handle = gau_create_handle_sound(AudioMgr::_mixer, _sound, &loopOnFinish, &quit, NULL);
	_handle->sound = this;
	ga_handle_play(_handle);
	_playing = true;
}

void nario::Audio::pause()
{
	if (_playing)
	{
		_playing = false;
		if(_handle) ga_handle_stop(_handle);
	}
}

void nario::Audio::resume()
{
	if (_handle)
	{
		ga_handle_play(_handle);
	}
	_playing = true;
}

void nario::Audio::stop()
{
	if (!_playing)
	{
		return;
	}
	if (_handle)
	{
		ga_handle_stop(_handle);
	}
	_playing = false;
}

void nario::Audio::setVolume(float volume)
{
	if (!_playing)
	{
		return;
	}
	_volume = volume;
	ga_handle_setParamf(_handle, GA_HANDLE_PARAM_GAIN, volume);
}

