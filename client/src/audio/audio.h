#pragma once
#include <string>
#include "ga.h"
#include "gau.h"

namespace nario {
	class Audio
	{
	public:
		Audio(const std::string& name, const std::string& filename);
		~Audio();

		void play();
		void loop();
		void pause();
		void resume();
		void stop();

		void setVolume(float volume);

		inline const float getVolume() const { return _volume; }
		inline const bool isPlaying() const { return _playing; }
		inline const std::string& getName() const { return _name; }
		inline const std::string& getFilePath() const { return _filepath; }

		friend void destroyOnFinish(ga_Handle* in_handle, void* in_context);
		friend void loopOnFinish(ga_Handle* in_handle, void* in_context);
	private:
		std::string _name;
		std::string _filepath;

		ga_Sound* _sound;
		ga_Handle* _handle;

		float _volume;
		bool _playing;
	};
}