#include "audio_mgr.h"

nario::AudioMgr::AudioMgr()
{
	init();
}

nario::AudioMgr::~AudioMgr()
{
	clean();
}

gau_Manager* nario::AudioMgr::_mgr = nullptr;
ga_Mixer* nario::AudioMgr::_mixer = nullptr;
void nario::AudioMgr::init()
{
	/* Initialize library + manager */
	gc_initialize(0);
	_mgr = gau_manager_create();
	_mixer = gau_manager_mixer(_mgr);

	_audios.clear();
}

std::vector<nario::Audio*> nario::AudioMgr::_audios;
void nario::AudioMgr::add(Audio* audio)
{
	_audios.push_back(audio);
}

nario::Audio* nario::AudioMgr::get(const std::string& name)
{
	if (name.empty())
	{
		return nullptr;
	}
	for (Audio* audio : _audios)
	{
		if (audio->getName() == name)
		{
			return audio;
		}
	}
	return nullptr;
}

void nario::AudioMgr::update()
{
	if (_mgr)
	{
		gau_manager_update(_mgr);
	}
}

void nario::AudioMgr::clean()
{
	for (size_t i = 0; i < _audios.size(); i++)
	{
		delete _audios[i];
	}

	/* Clean up library + manager */
	gau_manager_destroy(_mgr);
	gc_shutdown();
}

