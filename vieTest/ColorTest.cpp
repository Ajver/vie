#include "pch.h"

#include <vie/Color.h>

TEST(ColorTest, ShouldCreate_WhiteColorAsDefault)
{
	vie::Color color;
	EXPECT_EQ(255, color.r);
	EXPECT_EQ(255, color.g);
	EXPECT_EQ(255, color.b);
	EXPECT_EQ(255, color.a);
}

TEST(ColorTest, ShouldSet_Color)
{
	vie::Color color;
	color.setColor(10, 20, 30, 40);
	EXPECT_EQ(10, color.r);
	EXPECT_EQ(20, color.g);
	EXPECT_EQ(30, color.b);
	EXPECT_EQ(40, color.a);
}

TEST(ColorTest, ShouldSet_AlphaAs255)
{
	vie::Color color(5, 5, 5, 0);
	EXPECT_EQ(0, color.a);

	color.setColor(5, 5, 5);
	EXPECT_EQ(255, color.a);
}

TEST(ColorTest, Should_ColorsBeEquals)
{
	vie::Color redColor(255, 0, 0);
	vie::Color anotherRedColor(255, 0, 0);

	EXPECT_TRUE(redColor == anotherRedColor);
	EXPECT_FALSE(redColor != anotherRedColor);
}

TEST(ColorTest, Should_ColorsBe_NOT_Equals)
{
	vie::Color white(255, 255, 255);
	vie::Color black(0, 0, 0);

	EXPECT_TRUE(white != black);
	EXPECT_FALSE(white == black);
}

TEST(ColorTest, ShouldMultiply_Colors)
{
	vie::Color color = vie::Color(128, 64, 255, 128) * vie::Color(255, 128, 255, 32);
	EXPECT_EQ(128, color.r);
	EXPECT_EQ(32, color.g);
	EXPECT_EQ(255, color.b);
	EXPECT_EQ(16, color.a);
}

TEST(ColorTest, ShouldMultiplyEqual_Color)
{
	vie::Color color(128, 64, 255, 128);
	color *= vie::Color(255, 128, 255, 32);
	EXPECT_EQ(128, color.r);
	EXPECT_EQ(32, color.g);
	EXPECT_EQ(255, color.b);
	EXPECT_EQ(16, color.a);
}

TEST(ColorTest, ShouldAdd_Colors)
{
	vie::Color color = vie::Color(128, 64, 255, 128) + vie::Color(255, 128, 255, 32);
	EXPECT_EQ(255, color.r);
	EXPECT_EQ(192, color.g);
	EXPECT_EQ(255, color.b);
	EXPECT_EQ(160, color.a);
}

TEST(ColorTest, ShouldAddEqual_Color)
{
	vie::Color color(128, 64, 255, 128);
	color += vie::Color(255, 128, 255, 32);
	EXPECT_EQ(255, color.r);
	EXPECT_EQ(192, color.g);
	EXPECT_EQ(255, color.b);
	EXPECT_EQ(160, color.a);
}

TEST(ColorTest, ShouldSubtract_Colors)
{
	vie::Color color = vie::Color(255, 64, 255, 128) - vie::Color(128, 128, 255, 32);
	EXPECT_EQ(127, color.r);
	EXPECT_EQ(0, color.g);
	EXPECT_EQ(0, color.b);
	EXPECT_EQ(96, color.a);
}

TEST(ColorTest, ShouldSubtractEqual_Color)
{
	vie::Color color(255, 64, 255, 128);
	color -= vie::Color(128, 128, 255, 32);
	EXPECT_EQ(127, color.r);
	EXPECT_EQ(0, color.g);
	EXPECT_EQ(0, color.b);
	EXPECT_EQ(96, color.a);
}

TEST(ColorTest, Should_ExampleColorsBeValid)
{
	EXPECT_EQ(vie::Color(255, 0, 0), vie::COLOR::RED);
	EXPECT_EQ(vie::Color(0, 255, 0), vie::COLOR::GREEN);
	EXPECT_EQ(vie::Color(0, 0, 255), vie::COLOR::BLUE);
	EXPECT_EQ(vie::Color(255, 255, 255), vie::COLOR::WHITE);
	EXPECT_EQ(vie::Color(0, 0, 0, 255), vie::COLOR::BLACK);
	EXPECT_EQ(vie::Color(0, 0, 0, 0), vie::COLOR::TRANSPARENT);
	EXPECT_EQ(vie::Color(255, 255, 0), vie::COLOR::YELLOW);
	EXPECT_EQ(vie::Color(255, 128, 0), vie::COLOR::ORANGE);
	EXPECT_EQ(vie::Color(255, 0, 255), vie::COLOR::PURPLE);
	EXPECT_EQ(vie::Color(255, 128, 128), vie::COLOR::PINK);
	EXPECT_EQ(vie::Color(128, 128, 128), vie::COLOR::GRAY);
	EXPECT_EQ(vie::Color(192, 192, 192), vie::COLOR::LIGHT_GRAY);
	EXPECT_EQ(vie::Color(64, 64, 64), vie::COLOR::DARK_GRAY);
}