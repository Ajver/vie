#include "pch.h"

#include <vie/Layer.h>
#include <vie/Glyph.h>
#include <vie/Camera2D.h>
#include <time.h>

vie::Layer* getInitedLayer();
vie::Layer* getLayerWithSomeGlyphs();
bool areGlyphsVectorTheSame(const std::vector<vie::Glyph*>& a, const std::vector<vie::Glyph*>& b);
bool areSorted_FORWARD(const std::vector<vie::Glyph*>& glyphs);
bool areSorted_BACKWARD(const std::vector<vie::Glyph*>& glyphs);
bool areSorted_TEXTURE(const std::vector<vie::Glyph*>& glyphs);

TEST(LayerTest, Should_CreateEmptyGlyphsVector)
{
	vie::Layer* layer = getInitedLayer();
	EXPECT_EQ(0, layer->getGlyphsVector().size());
}

TEST(LayerTest, ShouldSet_Camera)
{
	vie::Layer* layer = getInitedLayer();
	vie::Camera2D* cam = new vie::Camera2D();
	layer->setCamera(cam);
	EXPECT_EQ(cam, layer->getCamera());
}

TEST(LayerTest, Should_AppendGlyph)
{
	vie::Layer* layer = getInitedLayer();
	layer->appendGlyph(new vie::Glyph());
	EXPECT_EQ(1, layer->getGlyphsVector().size());
}

TEST(LayerTest, Should_Not_SortGlyphs)
{
	vie::Layer* layer = getLayerWithSomeGlyphs();
	std::vector<vie::Glyph*> glyphsBeforeSort = layer->getGlyphsVector();
	layer->setSortType(vie::GlyphSortType::NONE);
	layer->sortGlyphs();
	std::vector<vie::Glyph*> glyphsAfterSort = layer->getGlyphsVector();
	bool areNOTSorted = areGlyphsVectorTheSame(glyphsBeforeSort, glyphsAfterSort);
	EXPECT_TRUE(areNOTSorted);
	EXPECT_EQ(glyphsBeforeSort.size(), glyphsAfterSort.size());
}

TEST(LayerTest, Should_SortGlyphs_FORWARD)
{
	vie::Layer* layer = getLayerWithSomeGlyphs();
	std::vector<vie::Glyph*> glyphsBeforeSort = layer->getGlyphsVector();
	layer->setSortType(vie::GlyphSortType::FORWARD);
	layer->sortGlyphs();
	std::vector<vie::Glyph*> glyphsAfterSort = layer->getGlyphsVector();
	bool areSorted = areSorted_FORWARD(glyphsAfterSort);
	EXPECT_TRUE(areSorted);
	EXPECT_EQ(glyphsBeforeSort.size(), glyphsAfterSort.size());
}

TEST(LayerTest, Should_SortGlyphs_BACKWARD)
{
	vie::Layer* layer = getLayerWithSomeGlyphs();
	std::vector<vie::Glyph*> glyphsBeforeSort = layer->getGlyphsVector();
	layer->setSortType(vie::GlyphSortType::BACKWARD);
	layer->sortGlyphs();
	std::vector<vie::Glyph*> glyphsAfterSort = layer->getGlyphsVector();
	bool areSorted = areSorted_BACKWARD(glyphsAfterSort);
	EXPECT_TRUE(areSorted);
	EXPECT_EQ(glyphsBeforeSort.size(), glyphsAfterSort.size());
}

TEST(LayerTest, Should_SortGlyphs_TEXTURE)
{
	vie::Layer* layer = getLayerWithSomeGlyphs();
	std::vector<vie::Glyph*> glyphsBeforeSort = layer->getGlyphsVector();
	layer->setSortType(vie::GlyphSortType::TEXTURE);
	layer->sortGlyphs();
	std::vector<vie::Glyph*> glyphsAfterSort = layer->getGlyphsVector();
	bool areSorted = areSorted_TEXTURE(glyphsAfterSort);
	EXPECT_TRUE(areSorted);
	EXPECT_EQ(glyphsBeforeSort.size(), glyphsAfterSort.size());
}

TEST(LayerTest, Should_RemoveGlyphsAfterRender)
{
	vie::Layer* layer = getLayerWithSomeGlyphs();
	EXPECT_LT(0, layer->getGlyphsVector().size());

	layer->render();
	EXPECT_EQ(0, layer->getGlyphsVector().size());
}


vie::Layer* getInitedLayer()
{
	return new vie::Layer("test_layer", 1, 1, new vie::Camera2D());
}

vie::Layer* getLayerWithSomeGlyphs()
{
	vie::Layer* layer = getInitedLayer();

	for (int i = 0; i < 20; i++)
	{
		vie::Glyph* glyph = new vie::Glyph();
		glyph->textureID = rand() % 200;
		glyph->depth = rand() % 200;
		layer->appendGlyph(glyph);
	}

	return layer;
}

bool areGlyphsVectorTheSame(const std::vector<vie::Glyph*>& a, const std::vector<vie::Glyph*>& b)
{
	if (a.size() != b.size())
		return false;

	for (int i = 0; i < a.size(); i++)
		if (a[i] != b[i])
			return false;
	
	return true;
}

bool areSorted_FORWARD(const std::vector<vie::Glyph*>& glyphs)
{
	for (int i = 1; i < glyphs.size(); i++)
	{
		if (glyphs[i - 1]->depth <= glyphs[i]->depth)
			continue;
		else
			return false;
	}

	return true;
}

bool areSorted_BACKWARD(const std::vector<vie::Glyph*>& glyphs)
{
	for (int i = 1; i < glyphs.size(); i++)
	{
		if (glyphs[i - 1]->depth >= glyphs[i]->depth)
			continue;
		else
			return false;
	}

	return true;
}

bool areSorted_TEXTURE(const std::vector<vie::Glyph*>& glyphs)
{
	for (int i = 1; i < glyphs.size(); i++)
	{
		if (glyphs[i - 1]->textureID <= glyphs[i]->textureID)
			continue;
		else
			return false;
	}

	return true;
}