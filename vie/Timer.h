#pragma once

typedef unsigned long ulong;

namespace vie
{

	class Timer
	{
	public:
		Timer();
		Timer(ulong ndur);

		bool tick() const;

		void start();
		void start(ulong ndur);
		void restart();
		void pause();
		void stop();

		void setDuration(ulong ndur);
		void setProgress(float progress);

		ulong getElapsedTime() const;

		float getProgress() const;
		float getProgressINV() const;
		float getEaseProgress() const;
		float getEaseProgressINV() const;
		float getEaseInProgress() const;
		float getEaseInProgressINV() const;
		float getEaseOutProgress() const;
		float getEaseOutProgressINV() const;
		float getIncreasingProgress() const;
		float getIncreasingProgressINV() const;
		float getDecreasingProgress() const;
		float getDecreasingProgressINV() const;

		bool getIsRunning() const;
		ulong getDuration() const;
		ulong getLeftTime() const;

	private:
		ulong duration;
		ulong leftTime;
		ulong breakTime;
		bool isRunning;

		float getFromRange01(float a) const;
	};

}