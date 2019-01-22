#include "pch.h"

#include <vie/Texture.h>

TEST(TextureTest, Should_CreateTextureWithParameters)
{
	unsigned char* testPixelsArray = new unsigned char[1];
	testPixelsArray[0] = 123;
	vie::Texture texture(0, 100, 50, testPixelsArray);
	EXPECT_EQ(0, texture.getID());
	EXPECT_EQ(100, texture.getWidth());
	EXPECT_EQ(50, texture.getHeight());
	EXPECT_EQ(testPixelsArray, texture.getPixelsArray());
}

TEST(TextureTest, ShouldReturn_ValidColor)
{
	unsigned char testPixelsArray[4] = { 10, 20, 30, 40 };
	vie::Texture texture(0, 1, 1, testPixelsArray);
	EXPECT_EQ(vie::Color(10, 20, 30, 40), texture.getPixelColor(0, 0));
}

TEST(TextureTest, ShouldSet_Color)
{
	vie::Texture texture(0, 1, 1, new unsigned char[4]);
	texture.setPixelColor(0, 0, vie::Color(10, 20, 30, 40));
	EXPECT_EQ(vie::Color(10, 20, 30, 40), texture.getPixelColor(0, 0));
}
