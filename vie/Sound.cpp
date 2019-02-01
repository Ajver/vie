#include "Sound.h"
#include "Errors.h"

namespace vie
{

	Sound::Sound() :
		isRunning(false),
		deviceId(0),
		length(0),
		buffer(nullptr)
	{
	}

	Sound::Sound(const std::string& soundPath) :
		isRunning(false),
		deviceId(0),
		length(0),
		buffer(nullptr)
	{
		load(soundPath);
	}

	Sound::~Sound()
	{
		SDL_CloseAudioDevice(deviceId);
		freeMemory();
	}

	void Sound::freeMemory()
	{
		if (buffer != nullptr)
		{
			SDL_FreeWAV(buffer);
			delete buffer;
		}
	}

	void Sound::load(const std::string& soundPath)
	{
		freeMemory();

		if (SDL_LoadWAV(soundPath.c_str(), &spec, &buffer, &length) == NULL)
		{
			std::string errorMsg = "Error: Could not load wav sound from path: " + soundPath + "\n";
			errorMsg += "Check if the file exist in right directory\n";
			errorMsg += "then check if the file has valid type (wav)\n";
			errorMsg += "SDL error: ";
			errorMsg += SDL_GetError();
			fatalError(errorMsg);
		}

		reset();
	}

	void Sound::play(const std::string& soundPath)
	{
		load(soundPath);
		return play();
	}

	void Sound::play()
	{
		isRunning = true;
		SDL_PauseAudioDevice(deviceId, 0);
	}

	void Sound::pause()
	{
		isRunning = false;
		SDL_PauseAudioDevice(deviceId, 1);
	}

	void Sound::reset()
	{
		isRunning = false;
		SDL_CloseAudioDevice(deviceId);
		deviceId = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
		SDL_QueueAudio(deviceId, buffer, length);
	}

	void Sound::replay()
	{
		reset();
		play();
	}

	bool Sound::getIsRunning() const
	{
		return isRunning;
	}

}