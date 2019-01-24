#include "Layer.h"

#include <algorithm>

#include "Glyph.h"

namespace vie
{

	Layer::Layer(GLuint vbo, GLuint vao) :
		vbo(vbo),
		vao(vao)
	{
	}


	Layer::~Layer()
	{
	}

	void Layer::appendGlyph(Glyph* glyph)
	{
		glyphs.push_back(glyph);
	}

	void Layer::sortGlyphsBy(GlyphSortType sortType)
	{
		switch (sortType)
		{
		case vie::GlyphSortType::FORWARD:
			std::sort(glyphs.begin(), glyphs.end(), compareForward);
			break;
		case vie::GlyphSortType::BACKWARD:
			std::sort(glyphs.begin(), glyphs.end(), compareBackward);
			break;
		case vie::GlyphSortType::TEXTURE:
			std::sort(glyphs.begin(), glyphs.end(), compareTexture);
			break;
		}
	}

	void Layer::renderGlyphs()
	{
		createRenderBatches();
		renderBatch();
		removeAllGlyphsAndRenderBatches();
	}

	void Layer::createRenderBatches()
	{
		if (glyphs.empty())
			return;

		std::vector<Vertex> vertices;
		vertices.resize(glyphs.size() * 6);

		for (int curGlyph = 0, curVertex = 0, offset = 0; curGlyph < glyphs.size(); curGlyph++)
		{
			if (curGlyph > 0)
			{
				if (glyphs[curGlyph]->textureID != glyphs[curGlyph - 1]->textureID)
					renderBatches.emplace_back(offset, 6, glyphs[curGlyph]->textureID);
				else
					renderBatches.back().numVertices += 6;
			}
			else
			{
				renderBatches.emplace_back(0, 6, glyphs[0]->textureID);
			}

			vertices[curVertex++] = glyphs[curGlyph]->topLeft;
			vertices[curVertex++] = glyphs[curGlyph]->bottomLeft;
			vertices[curVertex++] = glyphs[curGlyph]->bottomRight;
			vertices[curVertex++] = glyphs[curGlyph]->bottomRight;
			vertices[curVertex++] = glyphs[curGlyph]->topRight;
			vertices[curVertex++] = glyphs[curGlyph]->topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Layer::renderBatch()
	{
		glBindVertexArray(vao);

		for (int i = 0; i < renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, renderBatches[i].textureID);
			glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].numVertices);
		}

		glBindVertexArray(0);

		// Disable all textures
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Layer::removeAllGlyphsAndRenderBatches()
	{
		renderBatches.clear();

		for (int i = 0; i < glyphs.size(); i++)
			delete glyphs[i];

		glyphs.clear();
	}

	std::vector<Glyph*> Layer::getGlyphsVector()
	{
		return glyphs;
	}

	bool Layer::compareForward(Glyph* a, Glyph* b)
	{
		return a->depth < b->depth;
	}
	bool Layer::compareBackward(Glyph* a, Glyph* b)
	{
		return a->depth > b->depth;
	}
	bool Layer::compareTexture(Glyph* a, Glyph* b)
	{
		return a->textureID < b->textureID;
	}

}