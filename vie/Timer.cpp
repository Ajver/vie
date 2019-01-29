#include "Timer.h"

#include <SDL/SDL.h>

namespace vie
{

	Timer::Timer() :
		duration(0),
		leftTime(0),
		breakTime(0),
		isRunning(false)
	{
	}

	Timer::Timer(ulong ndur) :
		duration(ndur),
		leftTime(ndur),
		breakTime(SDL_GetTicks() + leftTime),
		isRunning(true)
	{
	}

	bool Timer::tick() const
	{
		return isRunning && (SDL_GetTicks() >= breakTime);
	}

	void Timer::start()
	{
		isRunning = true;
		breakTime = SDL_GetTicks() + leftTime;
	}

	void Timer::start(ulong ndur)
	{
		duration = ndur;
		restart();
	}

	void Timer::restart()
	{
		leftTime = duration;
		start();
	}

	void Timer::pause()
	{
		isRunning = false;
		leftTime = breakTime - SDL_GetTicks();
	}

	void Timer::stop()
	{
		leftTime = duration;
		isRunning = false;
	}

	float Timer::getProgress() const
	{
		return 1.0f - getInvertedProgress();
	}

	float Timer::getInvertedProgress() const
	{
		if (duration == 0)
			return 0.0f;

		float diff;

		if (isRunning)
			diff = 1.0f * breakTime - SDL_GetTicks();
		else
			diff = 1.0f * leftTime;

		return diff / duration;
	}

	float Timer::getEaseProgress() const
	{
		float progress = getProgress();
		return (1.0f - cos(progress * M_PI)) / 2.0f;
	}

	float Timer::getEaseInProgress() const
	{
		float progress = getProgress();
		if (progress < 0.5f)
			return getEaseProgress();
		else 
			return progress;
	}

	float Timer::getEaseOutProgress() const
	{
		float progress = getProgress();
		if (progress > 0.5f)
			return getEaseProgress();
		else
			return progress;
	}

	float Timer::getIncreasingProgress() const
	{
		float progress = getProgress();
		return progress * progress;
	}

	float Timer::getDecreasingProgress() const
	{
		float progress = getInvertedProgress();
		progress *= progress;
		return 1.0f - progress;
	}

	bool Timer::getIsRunning() const
	{
		return isRunning;
	}

}