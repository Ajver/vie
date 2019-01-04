#pragma once

namespace vie
{

	class Engine
	{
	public:
		Engine();
		~Engine();

		virtual void onCreate();

		void run();

	private:
		bool isRunning;
	};

}

