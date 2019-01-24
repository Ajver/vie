#include "pch.h"

#include <vie/Random.h>

TEST(RandomTest, ShouldReturn_RandomInt)
{
	int randomInt = vie::Random::nextInt(3);
	EXPECT_LE(0, randomInt);
	EXPECT_GT(3, randomInt);
}

TEST(RandomTest, ShouldReturn_RandomInt_FromRange)
{
	int randomInt = vie::Random::nextInt(1, 3);
	EXPECT_LE(1, randomInt);
	EXPECT_GE(3, randomInt);
}

TEST(RandomTest, ShouldReturn_RandomInt_FromReversedRange)
{
	int randomInt = vie::Random::nextInt(3, 1);
	EXPECT_LE(1, randomInt);
	EXPECT_GE(3, randomInt);
}

TEST(RandomTest, ShouldReturn_Random_Float)
{
	float randomFloat = vie::Random::nextFloat();
	EXPECT_LE(0.0f, randomFloat);
	EXPECT_GT(1.0f, randomFloat);
}

TEST(RandomTest, ShouldReturn_Negative_RandomInt)
{
	int randomInt = vie::Random::nextInt(-4);
	EXPECT_LT(-4, randomInt);
	EXPECT_GE(0, randomInt);
}

TEST(RandomTest, ShouldReturn_Negative_RandomInt_FromRange)
{
	int randomInt = vie::Random::nextInt(-2, 3);
	EXPECT_LE(-2, randomInt);
	EXPECT_GE(3, randomInt);
}