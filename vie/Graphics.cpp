#include "Graphics.h"

#include <algorithm>

namespace vie
{

	Graphics::Graphics() :
		screenWidth(0),
		screenHeight(0),
		vbo(0),
		vao(0),
		sortType(GlyphSortType::TEXTURE)
	{
	}


	Graphics::~Graphics()
	{
	}

	void Graphics::init(unsigned int sw, unsigned int sh)
	{
		colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
		colorProgram.addAtribute("vertexPosition");
		colorProgram.addAtribute("vertexColor");
		colorProgram.addAtribute("vertexUV");
		colorProgram.linkShaders();

		camera.init(sw, sh);

		createVertexArray();
	}

	void Graphics::begin(GlyphSortType st)
	{
		glClearDepth(1.0);

		// Clear the color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Enable the shader
		colorProgram.use();

		GLint textureLocation = colorProgram.getUnitformLocation("mySampler");
		glUniform1i(textureLocation, 0);

		// Set camera matrix
		camera.update();
		GLint pLocation = colorProgram.getUnitformLocation("P");
		glm::mat4 cameraMatrix = camera.getCameraMatrix();

		glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

		sortType = st;

		// Free the memory
		renderBatches.clear();

		for (int i = 0; i < glyphs.size(); i++)
		{
			delete glyphs[i];
		}
		glyphs.clear();
	}

	void Graphics::end()
	{
		sortGlyphs();
		createRenderBatches();
	}

	void Graphics::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureID, float depth, const Color& color)
	{
		Glyph *newGlyph = new Glyph();
		newGlyph->textureID = textureID;
		newGlyph->depth = depth;

		newGlyph->topLeft.setColor(color.r, color.g, color.b, color.a);
		newGlyph->topRight.setColor(color.r, color.g, color.b, color.a);
		newGlyph->bottomLeft.setColor(color.r, color.g, color.b, color.a);
		newGlyph->bottomRight.setColor(color.r, color.g, color.b, color.a);

		newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
		newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);

		newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
		newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);
		newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		glyphs.push_back(newGlyph);
	}

	void Graphics::renderBatch()
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

		// Disable the shader
		colorProgram.unuse();
	}

	void Graphics::createVertexArray()
	{
		if (vao == 0)
		{
			glGenVertexArrays(1, &vao);
		}
		glBindVertexArray(vao);

		if (vbo == 0)
		{
			glGenBuffers(1, &vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// Position			  
		// index, How many vars, type, normalize?, size, pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position)));
		// Color 
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));
		// UV
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, uv)));

		// Disable all 
		glBindVertexArray(0);
	}

	void Graphics::createRenderBatches()
	{
		if (glyphs.empty())
		{
			return;
		}

		std::vector<Vertex> vertices;
		vertices.resize(glyphs.size() * 6);

		int offset = 0;

		// Current Vertex
		int cv = 0;

		// Create and push new element with specyfic attributes
		renderBatches.emplace_back(0, 6, glyphs[0]->textureID);
		vertices[cv++] = glyphs[0]->topLeft;
		vertices[cv++] = glyphs[0]->bottomLeft;
		vertices[cv++] = glyphs[0]->bottomRight;
		vertices[cv++] = glyphs[0]->bottomRight;
		vertices[cv++] = glyphs[0]->topRight;
		vertices[cv++] = glyphs[0]->topLeft;

		offset += 6;

		// Current Glyph
		int cg = 1;

		for (int cg = 1; cg < glyphs.size(); cg++)
		{
			if (glyphs[cg]->textureID != glyphs[cg - 1]->textureID)
			{
				renderBatches.emplace_back(offset, 6, glyphs[cg]->textureID);
			}
			else
			{
				renderBatches.back().numVertices += 6;
			}

			vertices[cv++] = glyphs[cg]->topLeft;
			vertices[cv++] = glyphs[cg]->bottomLeft;
			vertices[cv++] = glyphs[cg]->bottomRight;
			vertices[cv++] = glyphs[cg]->bottomRight;
			vertices[cv++] = glyphs[cg]->topRight;
			vertices[cv++] = glyphs[cg]->topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		// Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		// Upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Graphics::sortGlyphs()
	{
		switch (sortType)
		{
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(glyphs.begin(), glyphs.end(), compareFrontToBack);
			break;
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(glyphs.begin(), glyphs.end(), compareBackToFront);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(glyphs.begin(), glyphs.end(), compareTexture);
			break;
		}
	}

	bool Graphics::compareFrontToBack(Glyph* a, Glyph* b)
	{
		return a->depth < b->depth;
	}
	bool Graphics::compareBackToFront(Glyph* a, Glyph* b)
	{
		return a->depth > b->depth;
	}
	bool Graphics::compareTexture(Glyph* a, Glyph* b)
	{
		// Sorted by texture id
		return a->textureID < b->textureID;
	}

}