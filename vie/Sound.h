#pragma once

#include <string>
#include <SDL/SDL.h>

namespace vie
{

	class Sound
	{
	public:
		Sound();
		Sound(const std::string& soundPath);
		~Sound();

		// Load new sound from file
		void load(const std::string& soundPath);

		// Load new sound from file and play it
		bool play(const std::string& soundPath);

		// Play the sound where pause previously (or from begin)
		bool play();

		// Pause the sound and stay where are
		void pause();

		// Reset the sound but NOT play
		void reset();

		// Reset and play the sound again
		bool restart();

		bool getIsRunning() const;

	private:
		SDL_AudioDeviceID deviceId;
		SDL_AudioSpec spec;
		Uint32 length;
		Uint8 *buffer;
		bool isRunning;
	};

}
