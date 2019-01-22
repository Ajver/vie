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

TEST(TextureTest, Should_CreateSubTexture)
{
	unsigned char testPixelsArray[8] = { 
		// Pixel 0, 0
		10, 20, 30, 40,
		// Pixel 1, 0
		50, 60, 70, 80
	};
	vie::Texture texture(0, 2, 1, testPixelsArray);
	vie::Texture subTexture = texture.getSubTexture(1, 0, 1, 1);
	EXPECT_FALSE(texture.getID() == subTexture.getID());
	EXPECT_EQ(1, subTexture.getWidth());
	EXPECT_EQ(1, subTexture.getHeight());
	EXPECT_EQ(vie::Color(50, 60, 70, 80), subTexture.getPixelColor(0, 0));
}

