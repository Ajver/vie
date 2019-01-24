#include "Random.h"

#include <Windows.h>
#include <time.h>

namespace vie
{
	
	int Random::nextInt(int to)
	{
		srand(time(NULL));
		int signMod = 1;

		if (to < 0)
		{
			signMod = -1;
			to *= -1;
		}

		return signMod * rand() % to;
	}

	int Random::nextInt(int from, int to)
	{
		if (from > to)
			swapInt(from, to);

		int diff = to - from + 1;

		return nextInt(diff) + from;
	}

	float Random::nextFloat()
	{
		srand(time(NULL));
		return rand() / (float)RAND_MAX;
	}

	void Random::swapInt(int& a, int& b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

	Random::Random() {}

}