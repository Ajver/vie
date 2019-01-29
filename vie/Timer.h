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

		float getProgress() const;
		float getInvertedProgress() const;
		float getEaseProgress() const;
		float getEaseInProgress() const;
		float getEaseOutProgress() const;
		float getIncreasingProgress() const;
		float getDecreasingProgress() const;

		bool getIsRunning() const;

	private:
		ulong duration;
		ulong leftTime;
		ulong breakTime;
		bool isRunning;
	};

}