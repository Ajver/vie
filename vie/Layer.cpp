#include "Layer.h"

#include <algorithm>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "Glyph.h"
#include "Camera2D.h"
#include "Window.h"

#include <iostream>

namespace vie
{

	Layer::Layer(const std::string& n, GLuint vbo, GLuint vao, Camera2D* ncamera) :
		name(n),
		vbo(vbo),
		vao(vao),
		camera(ncamera),
		sortType(GlyphSortType::NONE)
	{
		colorProgram.init();
	}


	Layer::~Layer()
	{
		removeAllGlyphsAndRenderBatches();
	}

	void Layer::appendGlyph(Glyph* glyph)
	{
		glyphs.push_back(glyph);
	}

	void Layer::render()
	{	
		prepareShadersAndGL();
		renderGlyphs();
		removeAllGlyphsAndRenderBatches();
		colorProgram.unuse();
	}

	void Layer::prepareShadersAndGL()
	{
		colorProgram.use();
		resetSamplerInShader();
	}

	void Layer::resetSamplerInShader()
	{
		GLint textureLocation = colorProgram.getUnitformLocation("sampler");
		glUniform1i(textureLocation, 0);
	}

	void Layer::renderGlyphs()
	{
		prepareGlyphs();
		renderBatch();
	}

	void Layer::prepareGlyphs()
	{
		sortGlyphs();
		transformGlyphsByCamera();
		createRenderBatches();
	}

	void Layer::sortGlyphs()
	{
		switch (sortType)
		{
		case GlyphSortType::FORWARD:
			std::sort(glyphs.begin(), glyphs.end(), compareForward);
			break;
		case GlyphSortType::BACKWARD:
			std::sort(glyphs.begin(), glyphs.end(), compareBackward);
			break;
		case GlyphSortType::TEXTURE:
			std::sort(glyphs.begin(), glyphs.end(), compareTexture);
			break;
		}
	}

	void Layer::transformGlyphsByCamera()
	{
		setCameraMatrix();

		glm::vec2 cameraPosition = -camera->getPosition();
		float angle = -camera->getRotate();
		float screenHeight = Window::getScreenHeight();

		for (auto& currGlyph : glyphs)
		{
			currGlyph->translateByVec2(cameraPosition);
			currGlyph->rotateByAngle(angle);
			currGlyph->invertInYAxis(screenHeight);
		}
	}

	void Layer::setCameraMatrix()
	{
		camera->update();

		GLint pLocation = colorProgram.getUnitformLocation("P");
		glm::mat4 cameraMatrix = camera->getCameraMatrix();
		glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	}

	void Layer::createRenderBatches()
	{
		if (glyphs.empty())
			return;

		std::vector<Vertex> vertices;
		vertices.resize(glyphs.size() * 6);

		int currVertex = 0, offset = 0;
		Glyph* prevGlyp = nullptr;

		for (auto& currGlyph : glyphs)
		{
			if (prevGlyp != nullptr)
			{
				if (currGlyph->textureID != prevGlyp->textureID)
					renderBatches.emplace_back(offset, 6, currGlyph->textureID);
				else
					renderBatches.back().numVertices += 6;
			}
			else
			{
				prevGlyp = currGlyph;
				renderBatches.emplace_back(0, 6, glyphs[0]->textureID);
			}

			vertices[currVertex++] = currGlyph->topLeft;
			vertices[currVertex++] = currGlyph->bottomLeft;
			vertices[currVertex++] = currGlyph->bottomRight;
			vertices[currVertex++] = currGlyph->bottomRight;
			vertices[currVertex++] = currGlyph->topRight;
			vertices[currVertex++] = currGlyph->topLeft;
			offset += 6;
		}		

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Layer::renderBatch() const
	{
		glBindVertexArray(vao);

		for (auto& currRenderBatch : renderBatches)
		{
			glBindTexture(GL_TEXTURE_2D, currRenderBatch.textureID);
			glDrawArrays(GL_TRIANGLES, currRenderBatch.offset, currRenderBatch.numVertices);
		}

		glBindVertexArray(0);

		// Disable all textures
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Layer::removeAllGlyphsAndRenderBatches()
	{
		renderBatches.clear();

		for (auto& currGlyph : glyphs)
			delete currGlyph;

		glyphs.clear();
	}

	void Layer::setCamera(Camera2D* ncamera)
	{
		camera = ncamera;
	}

	void Layer::setSortType(GlyphSortType newSortType)
	{
		sortType = newSortType;
	}

	Camera2D* Layer::getCamera() const
	{
		return camera;
	}

	bool Layer::isNamed(const std::string& n) const
	{
		return name == n;
	}

	std::string Layer::getName() const
	{
		return name;
	}

	std::vector<Glyph*> Layer::getGlyphsVector() const
	{
		return glyphs;
	}

	GlyphSortType Layer::getSortType() const
	{
		return sortType;
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