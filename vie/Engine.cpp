#include "Engine.h"

namespace vie
{

	Engine::Engine() :
		isRunning(false)
	{
	}


	Engine::~Engine()
	{
	}

	void Engine::run()
	{
		// Run only if not running yet
		if (isRunning)
			return;

		isRunning = true;

		while (isRunning)
		{

		}
	}

}