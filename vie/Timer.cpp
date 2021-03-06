#include "Timer.h"

#include <SDL/SDL.h>

#include <cmath>

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

	void Timer::setDuration(ulong ndur)
	{
		leftTime = getLeftTime() + (ndur - duration);
		breakTime = SDL_GetTicks() + leftTime;
		duration = ndur;
	}

	void Timer::setProgress(float progress)
	{
		float invProgress = 1.0f - getFromRange01(progress);
		leftTime = duration * invProgress;
		breakTime = SDL_GetTicks() + leftTime;
	}

	ulong Timer::getElapsedTime() const
	{
		return SDL_GetTicks() - (breakTime - duration);
	}

	float Timer::getProgress() const
	{
		return 1.0f - getProgressINV();
	}

	float Timer::getProgressINV() const
	{
		if (duration == 0)
			return 0.0f;

		float diff;

		if (isRunning)
			diff = 1.0f * breakTime - SDL_GetTicks();
		else
			diff = 1.0f * leftTime;

		return getFromRange01(diff / duration);
	}

	float Timer::getEaseProgress() const
	{
		float progress = getProgress();
		return (1.0f - cos(progress * M_PI)) / 2.0f;
	}

	float Timer::getEaseProgressINV() const
	{
		return 1.0f - getEaseProgress();
	}

	float Timer::getEaseInProgress() const
	{
		float progress = getProgress();
		if (progress < 0.5f)
			return getEaseProgress();
		else
			return progress;
	}

	float Timer::getEaseInProgressINV() const
	{
		return 1.0f - getEaseInProgress();
	}

	float Timer::getEaseOutProgress() const
	{
		float progress = getProgress();
		if (progress >= 0.5f)
			return getEaseProgress();
		else
			return progress;
	}

	float Timer::getEaseOutProgressINV() const
	{
		return 1.0f - getEaseOutProgress();
	}

	float Timer::getIncreasingProgress() const
	{
		float progress = getProgress();
		return progress * progress;
	}

	float Timer::getIncreasingProgressINV() const
	{
		return 1.0f - getIncreasingProgress();
	}

	float Timer::getDecreasingProgress() const
	{
		return 1.0f - getDecreasingProgressINV();
	}

	float Timer::getDecreasingProgressINV() const
	{
		float progress = getProgressINV();
		return progress * progress;
	}

	bool Timer::getIsRunning() const
	{
		return isRunning;
	}

	ulong Timer::getDuration() const
	{
		return duration;
	}

	ulong Timer::getLeftTime() const
	{
		if(isRunning)
			return breakTime - SDL_GetTicks();

		return 0;
	}

	float Timer::getFromRange01(float a) const
	{
		if (a < 0.0f)
			return 0.0f;
		if (a > 1.0f)
			return 1.0f;
		return a;
	}

}
