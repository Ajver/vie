#pragma once

typedef unsigned long ulong;

namespace vie
{

	enum TimingFunction : char
	{
		LINEAR = 0x1,
		EASE = 0x2,
		EASE_IN = 0x4,
		EASE_OUT = 0x8,
		INVERTED = 0x128
	};

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

		float getProgress(TimingFunction tf) const;
		float getProgress() const;
		float getInvertedProgress() const;
		float getEaseProgress() const;
		float getEaseInProgress() const;
		float getEaseOutProgress() const;
		float getIncreasingProgress() const;
		float getDecreasingProgress() const;

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