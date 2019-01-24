#include "pch.h"

#include<vie/Graphics.h>
#include<vie/Camera2D.h>
#include<vie/Layer.h>

void drawSomething(vie::Graphics* g);
vie::Graphics* getInitedGraphics();


TEST(GraphicsTest, Should_AppendLayer)
{
	vie::Graphics g = *getInitedGraphics();
	g.appendLayer(new vie::Layer("test_layer", 1, 1, new vie::Camera2D()));
	EXPECT_TRUE(g.containsLayer("test_layer"));
}

TEST(GraphicsTest, Should_GetLayerByName)
{
	vie::Graphics g = *getInitedGraphics();
	g.appendLayer(new vie::Layer("test_layer", 1, 1, new vie::Camera2D()));
	EXPECT_FALSE(nullptr == g.getLayerByName("test_layer"));
}

TEST(GraphicsTest, Should_CreateLayer)
{
	vie::Graphics g;
	EXPECT_FALSE(g.containsLayer("test_layer"));

	g.createLayer("test_layer");
	EXPECT_TRUE(g.containsLayer("test_layer"));
}

TEST(GraphicsTest, Should_SwitchLayer)
{
	vie::Graphics g = *getInitedGraphics();
	g.createLayer("test_layer");
	EXPECT_FALSE("test_layer" == g.getCurrentLayer()->getName());
	
	g.switchLayer("test_layer");
	EXPECT_EQ("test_layer", g.getCurrentLayer()->getName());
}

TEST(GraphicsTest, Should_RemoveLayer)
{
	vie::Graphics g;
	g.createLayer("test_layer");
	EXPECT_TRUE(g.containsLayer("test_layer"));
	
	g.removeLayer("test_layer");
	EXPECT_FALSE(g.containsLayer("test_layer"));
}

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

TEST(GraphicsTest, ShouldSet_Color)
{
	vie::Graphics g;
	g.setColor(vie::Color(10, 20, 30, 40));
	EXPECT_EQ(vie::Color(10, 20, 30, 40), g.getDefaultColor());
}

void drawSomething(vie::Graphics* g)
{
	for (int i = 0; i < 5; i++)
		g->fillRect(glm::vec2(), glm::vec2());
}

vie::Graphics* getInitedGraphics()
{
	vie::Graphics* g = new vie::Graphics();
	g->init(new vie::Camera2D());
	return g;
}