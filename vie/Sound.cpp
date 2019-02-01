#include "Sound.h"


namespace vie
{

	Sound::Sound() :
		isRunning(false)
	{
	}

	Sound::Sound(const std::string& soundPath) :
		isRunning(false)
	{
		load(soundPath);
	}

	Sound::~Sound()
	{
		SDL_CloseAudioDevice(deviceId);
		SDL_FreeWAV(buffer);
		delete buffer;
	}

	void Sound::load(const std::string& soundPath)
	{
		SDL_LoadWAV(soundPath.c_str(), &spec, &buffer, &length);

		// TODO - maybe it is not need to override it all time 
		deviceId = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
	}

	bool Sound::play(const std::string& soundPath)
	{
		load(soundPath);
		return play();
	}

	bool Sound::play()
	{
		isRunning = true;

		int success = SDL_QueueAudio(deviceId, buffer, length);
		SDL_PauseAudioDevice(deviceId, 0);

		return success;
	}

	void Sound::pause()
	{
		isRunning = false;
		SDL_PauseAudioDevice(deviceId, 1);
	}

	void Sound::reset()
	{

	}

	bool Sound::restart()
	{
		reset();
		return play();
	}

	bool Sound::getIsRunning() const
	{
		return isRunning;
	}

}