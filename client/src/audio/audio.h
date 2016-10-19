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
		void stop();

		inline const std::string& getName() const { return _name; }
		inline const std::string& getFilePath() const { return _filepath; }
	private:
		std::string _name;
		std::string _filepath;

		ga_Sound* _sound;
		ga_Handle* _handle;
	};
}