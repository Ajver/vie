#include "pch.h"

#include <vie/Vertex.h>

TEST(VertexTest, ShouldSet_Position)
{
	vie::Vertex vrx;
	vrx.setPosition(10, 20);
	EXPECT_EQ(10, vrx.position.x);
	EXPECT_EQ(20, vrx.position.y);
}

TEST(VertexTest, ShouldSet_Color)
{
	vie::Vertex vrx;
	vrx.setColor(vie::Color(10, 20, 30, 40));
	EXPECT_EQ(vie::Color(10, 20, 30, 40), vrx.color);
}

TEST(VertexTest, ShouldSet_UV)
{
	vie::Vertex vrx;
	vrx.setUV(0.5f, 0.1f);
	EXPECT_EQ(0.5f, vrx.uv.u);
	EXPECT_EQ(0.1f, vrx.uv.v);
}

TEST(VertexTest, Should_Translate)
{
	vie::Vertex vrx;
	vrx.setPosition(1.0f, 2.0f);
	vrx.translate(3.0f, 4.0f);
	EXPECT_EQ(4.0f, vrx.position.x);
	EXPECT_EQ(6.0f, vrx.position.y);
}

TEST(VertexTest, Should_Rotate)
{
	vie::Vertex vrx;
	vrx.setPosition(2.0f, 3.0f);
	vrx.rotate(1.0f);
	EXPECT_EQ(2 * cos(1.0f) - 3 * sin(1.0f), vrx.position.x);
	EXPECT_EQ(2 * sin(1.0f) + 3 * cos(1.0f), vrx.position.y);
}

