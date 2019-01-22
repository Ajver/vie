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