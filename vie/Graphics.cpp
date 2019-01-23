#include "Graphics.h"

#include <algorithm>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "Camera2D.h"
#include "Errors.h"
#include "Window.h"
#include "Glyph.h"

namespace vie
{

	Graphics::Graphics() :
		vbo(0),
		vao(0),
		sortType(GlyphSortType::TEXTURE),
		camera(nullptr),
		scale(1.0f),
		translateVec(glm::vec2(0, 0)),
		nextTextureDepth(0.0f),
		rotateAngleInRadians(0.0f)
	{
	}

	Graphics::~Graphics()
	{
	}

	void Graphics::init(Camera2D* ncamera)
	{
		// Enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		colorProgram.compileShaders();
		colorProgram.addAtribute("vertexPosition");
		colorProgram.addAtribute("vertexColor");
		colorProgram.addAtribute("vertexUV");
		colorProgram.linkShaders();

		camera = ncamera;

		createOnePixelTexture();

		createVertexArray();
	}

	void Graphics::createOnePixelTexture()
	{
		unsigned char out[] = { 255, 255, 255, 255 };

		GLuint textureID;
		glGenTextures(1, &textureID);

		onePixelTexture = Texture(textureID, 1, 1, out);
		onePixelTexture.refreshGLBuffer();
	}

	glm::vec2 rotatePointt(float angle, const glm::vec2& point)
	{
		float nx = point.x * cos(angle) - point.y * sin(angle);
		float ny = point.x * sin(angle) + point.y * cos(angle);
		return glm::vec2(nx, ny);
	}

	void Graphics::begin(GlyphSortType newSortType)
	{
		glClearDepth(1.0);

		// Clear the color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		nextTextureDepth = 0.0f;

		// Enable the shader
		colorProgram.use();

		GLint textureLocation = colorProgram.getUnitformLocation("mySampler");
		glUniform1i(textureLocation, 0);

		setSortType(newSortType);

		// Free the memory
		renderBatches.clear();

		for (int i = 0; i < glyphs.size(); i++)
			delete glyphs[i];

		glyphs.clear();
	}

	void Graphics::end()
	{
		setCameraMatrix();
		sortGlyphs();
		createRenderBatches();
	}

	void Graphics::setCameraMatrix()
	{
		camera->update();

		GLint pLocation = colorProgram.getUnitformLocation("P");
		glm::mat4 cameraMatrix = camera->getCameraMatrix();
		glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

		GLint screeenHeightLocation = colorProgram.getUnitformLocation("screenHeight");
		glUniform1f(screeenHeightLocation, (float)Window::getScreenHeight());

		transformGlyphsByCamera();
	}

	void Graphics::transformGlyphsByCamera()
	{
		translateGlyphsByCamera();
		rotateGlyphsByCamera();
	}

	void Graphics::translateGlyphsByCamera()
	{
		glm::vec2 cameraPosition = camera->getPosition();
		cameraPosition.x *= -1.0f;

		for (int i = 0; i < glyphs.size(); i++)
			glyphs[i]->translateByVec2(cameraPosition);
	}

	void Graphics::rotateGlyphsByCamera()
	{
		float angle = -camera->getRotate();

		for (int i = 0; i < glyphs.size(); i++)
			glyphs[i]->rotateByAngle(angle);
	}

	void Graphics::setSortType(GlyphSortType newSortType)
	{
		sortType = newSortType;
	}

	void Graphics::setBackgroundColor(const Color& color)
	{
		glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
	}

	void Graphics::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureID, float depth, const Color& color)
	{
		if (depth > nextTextureDepth)
			nextTextureDepth = depth;

		Glyph *newGlyph = new Glyph();
		newGlyph->textureID = textureID;
		newGlyph->depth = depth;

		glm::vec2 topLeft(destRect.x, destRect.y);
		glm::vec2 topRight(destRect.x + destRect.z, destRect.y);
		glm::vec2 bottomLeft(destRect.x, destRect.y + destRect.w);
		glm::vec2 bottomRight(destRect.x + destRect.z, destRect.y + destRect.w);

		topLeft = transformPoint(topLeft);
		bottomLeft = transformPoint(bottomLeft);
		bottomRight = transformPoint(bottomRight);
		topRight = transformPoint(topRight);

		newGlyph->topLeft.setPosition(topLeft.x, topLeft.y);
		newGlyph->topRight.setPosition(topRight.x, topRight.y);
		newGlyph->bottomLeft.setPosition(bottomLeft.x, bottomLeft.y);
		newGlyph->bottomRight.setPosition(bottomRight.x, bottomRight.y);

		setGlyphUV(newGlyph, uvRect);

		setGlyphColor(newGlyph, color);

		glyphs.push_back(newGlyph);
	}

	glm::vec2 Graphics::transformPoint(glm::vec2 point) const
	{
		point = glm::rotate(point, rotateAngleInRadians);
		point *= scale;
		point += translateVec;

		return point;
	}

	void Graphics::setGlyphUV(Glyph* glyph, const glm::vec4& uvRect)
	{
		glyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
		glyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		glyph->bottomLeft.setUV(uvRect.x, uvRect.y);
		glyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
	}

	void Graphics::setGlyphColor(Glyph* glyph, const Color& color)
	{
		glyph->topLeft.setColor(color);
		glyph->topRight.setColor(color);
		glyph->bottomLeft.setColor(color);
		glyph->bottomRight.setColor(color);
	}

	void Graphics::drawTexture(const Texture& texture, float x, float y, const Color& color)
	{
		drawTexture(texture, x, y, texture.getWidth(), texture.getHeight(), color);
	}

	void Graphics::drawTexture(const Texture& texture, float x, float y, float w, float h, const Color& color)
	{
		draw(glm::vec4(x, y, w, h), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.getID(), nextTextureDepth + 0.1f, color);
	}
	
	void Graphics::drawTexture(const Texture& texture, const glm::vec2& position, const Color& color)
	{
		draw(glm::vec4(position.x, position.y, texture.getWidth(), texture.getHeight()), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.getID(), nextTextureDepth + 0.1f, color);
	}

	void Graphics::drawTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const Color& color)
	{
		draw(glm::vec4(position.x, position.y, size.x, size.y), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.getID(), nextTextureDepth + 0.1f, color);
	}	

	void Graphics::fillRect(const glm::vec2& position, const glm::vec2& size, const Color& color)
	{
		drawTexture(onePixelTexture, position, size, color);
	}

	void Graphics::drawRect(const glm::vec2& position, const glm::vec2& size, const Color& color)
	{
		// Top
		fillRect(glm::vec2(position.x + 1, position.y), glm::vec2(size.x - 1, 1), color);

		// Bottom
		fillRect(glm::vec2(position.x + 1, position.y + size.y - 1), glm::vec2(size.x - 1, 1), color);

		// Left
		fillRect(position, glm::vec2(1, size.y), color);

		// Right
		fillRect(glm::vec2(position.x + size.x - 1, position.y + 1), glm::vec2(1, size.y - 2), color);
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
			glGenVertexArrays(1, &vao);
		
		glBindVertexArray(vao);

		if (vbo == 0)
			glGenBuffers(1, &vbo);
		
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
			return;

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
				renderBatches.emplace_back(offset, 6, glyphs[cg]->textureID);
			else
				renderBatches.back().numVertices += 6;

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

	void Graphics::setTranslate(const glm::vec2& newTranslate)
	{
		translateVec = newTranslate;
	}

	void Graphics::setScale(float newScale)
	{
		scale = newScale;
	}

	void Graphics::setRotate(float newRotate)
	{
		rotateAngleInRadians = newRotate;
	}

	void Graphics::translate(const glm::vec2& translateVector)
	{
		translateVec += translateVector;
	}

	void Graphics::scaleUp(float scaleMod)
	{
		scale *= scaleMod;
	}

	void Graphics::scaleDown(float scaleMod)
	{
		scale /= scaleMod;
	}

	void Graphics::rotate(float angle)
	{
		rotateAngleInRadians += angle;
	}

	glm::vec2 Graphics::getTranslate() const
	{
		return translateVec;
	}

	float Graphics::getScale() const
	{
		return scale;
	}

	float Graphics::getRotate() const
	{
		return rotateAngleInRadians;
	}

	GlyphSortType Graphics::getSortType() const
	{
		return sortType;
	}
	
}