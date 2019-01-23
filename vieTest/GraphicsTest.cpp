#include "pch.h"

#include<vie/Graphics.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

TEST(GraphicsTest, ShouldSet_Translate)
{
	vie::Graphics g;
	g.setTranslate(glm::vec2(10.0f, 50.0f));
	EXPECT_EQ(10.0f, g.getTranslate().x);
	EXPECT_EQ(50.0f, g.getTranslate().y);
}

TEST(GraphicsTest, ShouldSet_Scale)
{
	vie::Graphics g;
	g.setScale(1.5f);
	EXPECT_EQ(1.5f, g.getScale());
}

TEST(GraphicsTest, ShouldSet_Rotate)
{
	vie::Graphics g;
	g.setRotate(1.0f);
	EXPECT_EQ(1.0f, g.getRotate());
}

TEST(GraphicsTest, Should_Translate)
{
	vie::Graphics g;
	g.translate(glm::vec2(15.0f, 30.0f));
	EXPECT_EQ(glm::vec2(15.0f, 30.0f), g.getTranslate());

	g.translate(glm::vec2(30.0f, -40.0f));
	EXPECT_EQ(glm::vec2(45.0f, -10.0f), g.getTranslate());
}

TEST(GraphicsTest, Should_ScaleUp)
{
	vie::Graphics g;
	g.scaleUp(1.5f);
	EXPECT_EQ(1.5f, g.getScale());

	g.scaleUp(0.5f);
	EXPECT_EQ(0.75f, g.getScale());
}

TEST(GraphicsTest, Should_ScaleDown)
{
	vie::Graphics g;
	g.scaleDown(0.5f);
	EXPECT_EQ(2.0f, g.getScale());

	g.scaleDown(4.0f);
	EXPECT_EQ(0.5f, g.getScale());
}

TEST(GraphicsTest, Should_IncreaseRotateAngle)
{
	vie::Graphics g;
	g.rotate(1.0f);
	EXPECT_EQ(1.0f, g.getRotate());

	g.rotate(-3.0f);
	EXPECT_EQ(-2.0f, g.getRotate());
}

TEST(GraphicsTest, ShouldSet_SortType)
{
	vie::Graphics g;
	g.setSortType(vie::GlyphSortType::TEXTURE);
	EXPECT_EQ(vie::GlyphSortType::TEXTURE, g.getSortType());
}

TEST(GraphicsTest, Should_TransformPoint)
{
	vie::Graphics g;
	g.setTranslate(glm::vec2(10.0f, 30.0f));
	g.setScale(2.0f);
	g.setRotate(3.0f);

	glm::vec2 point(100.0f, 100.0f);
	point = glm::rotate(point, 3.0f);
	point *= 2.0f;
	point.x += 10.0f;
	point.y += 30.0f;

	EXPECT_EQ(point, g.transformPoint(glm::vec2(100.0f, 100.0f)));
}

TEST(GraphicsTest, Should_Not_ChangeOriginalVec2)
{
	vie::Graphics g;
	glm::vec2 translateVec(10.0f, 5.0f);
	g.setTranslate(translateVec);
	g.translate(glm::vec2(20.0f, -15.0f));
	EXPECT_EQ(glm::vec2(30.0f, -10.0f), g.getTranslate());
	EXPECT_EQ(glm::vec2(10.0f, 5.0f), translateVec);
}