#include "pch.h"

#include "../vie/Errors.cpp"
#include "../vie/Window.cpp"
#include "../vie/Camera2D.cpp"
#include "../vie/GLSLProgram.cpp"
#include "../vie/Texture.cpp"
#include "../vie/Graphics.cpp"

TEST(GraphicsTest, ShouldRotate)
{
	vie::Graphics g;
	g.rotate(1.0f);
	EXPECT_EQ(1.0f, g.getRotate());
}

int main(int argc, char *args[])
{
	return 0;
}