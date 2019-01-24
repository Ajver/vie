#pragma once


namespace vie
{

	class Random
	{
	public:
		static int nextInt(int to);
		static int nextInt(int from, int to);

		static float nextFloat();

	private:
		static void swapInt(int& a, int& b);

		Random();
	};

}