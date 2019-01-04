#include "Errors.h"

#include <SDL/SDL.h>

namespace vie
{
	void fatalError(std::string errorString)
	{
		printf((errorString + "\n").c_str());
		system("pause");

		SDL_Quit();
		exit(-1);
	}
}