#include "pch.h"

#include "../vie/Color.h"

TEST(ColorTest, ShouldCreateWhiteColorAsDefault)
{
	vie::Color color;
	EXPECT_EQ(255, color.r);
	EXPECT_EQ(255, color.g);
	EXPECT_EQ(255, color.b);
	EXPECT_EQ(255, color.a);
}

TEST(ColorTest, ShouldSetColor)
{
	vie::Color color;
	color.setColor(10, 20, 30, 40);
	EXPECT_EQ(10, color.r);
	EXPECT_EQ(20, color.g);
	EXPECT_EQ(30, color.b);
	EXPECT_EQ(40, color.a);
}

TEST(ColorTest, ShouldSetAlphaAs255)
{
	vie::Color color(5, 5, 5, 0);
	EXPECT_EQ(0, color.a);

	color.setColor(5, 5, 5);
	EXPECT_EQ(255, color.a);
}

TEST(ColorTest, ShouldColorsBeEquals)
{
	vie::Color redColor(255, 0, 0);
	vie::Color anotherRedColor(255, 0, 0);

	EXPECT_TRUE(redColor == anotherRedColor);
	EXPECT_FALSE(redColor != anotherRedColor);
}

TEST(ColorTest, ShouldColorsBe_NOT_Equals)
{
	vie::Color white(255, 255, 255);
	vie::Color black(0, 0, 0);

	EXPECT_TRUE(white != black);
	EXPECT_FALSE(white == black);
}

TEST(ColorTest, ShouldExampleColorsBeValid)
{
	EXPECT_EQ(vie::Color(255, 0, 0), vie::RED);
	EXPECT_EQ(vie::Color(0, 255, 0), vie::GREEN);
	EXPECT_EQ(vie::Color(0, 0, 255), vie::BLUE);
	EXPECT_EQ(vie::Color(255, 255, 255), vie::WHITE);
	EXPECT_EQ(vie::Color(0, 0, 0, 255), vie::BLACK);
	EXPECT_EQ(vie::Color(0, 0, 0, 0), vie::TRANSPARENT);
	EXPECT_EQ(vie::Color(255, 255, 0), vie::YELLOW);
	EXPECT_EQ(vie::Color(255, 128, 0), vie::ORANGE);
	EXPECT_EQ(vie::Color(255, 0, 255), vie::PURPLE);
	EXPECT_EQ(vie::Color(255, 128, 128), vie::PINK);
}