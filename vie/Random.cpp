#include "Random.h"

#include <random>

namespace vie
{
	
	int Random::nextInt(int to)
	{
		std::random_device r;
		std::default_random_engine e1(r());
		std::uniform_int_distribution<int> uniform_dist(1);
		int mean = uniform_dist(e1);

		int signMod = 1;

		if (to < 0)
		{
			signMod = -1;
			to *= -1;
		}

		return signMod * mean % to;
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
		return nextInt(1000000) / 1000000.0f;
	}

	void Random::swapInt(int& a, int& b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

	Random::Random() {}

}