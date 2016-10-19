#pragma once
#include <vector>
#include <memory>
#include "audio.h"

#define GAU_THREAD_POLICY_MULTI 2
namespace nario {
	class AudioMgr
	{
		friend class Audio;
	private:
		AudioMgr();
		virtual ~AudioMgr();
		static void Destroy(AudioMgr* amgr)
		{
			if (amgr)
			{
				amgr->~AudioMgr();
			}
		}
	public:
		static void add(Audio* audio);
		static Audio* get(const std::string& name);
		static void update();

	private:
		static void init();
		static void clean();

	public:
		static std::shared_ptr<AudioMgr> getInstance()
		{
			static std::shared_ptr<AudioMgr> _instance(new AudioMgr, Destroy);
			return _instance;
		}

	private:
		static std::vector<Audio*> _audios;

		static gau_Manager* _mgr;
		static ga_Mixer* _mixer;
	};
}