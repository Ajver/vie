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
		setCamera(ncamera);
		colorProgram.init();

		enableAlphaBlending();
		createOnePixelTexture();
		createVertexArray();
	}

	void Graphics::enableAlphaBlending()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Graphics::createOnePixelTexture()
	{
		unsigned char out[] = { 255, 255, 255, 255 };

		GLuint textureID;
		glGenTextures(1, &textureID);

		onePixelTexture = Texture(textureID, 1, 1, out);
		onePixelTexture.refreshGLBuffer();
	}

	void Graphics::begin(GlyphSortType newSortType)
	{
		setSortType(newSortType);
		nextTextureDepth = 0.0f;
		clearGL();

		colorProgram.use();
		resetSamplerInShader();
	}

	void Graphics::clearGL()
	{
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Graphics::resetSamplerInShader()
	{
		GLint textureLocation = colorProgram.getUnitformLocation("mySampler");
		glUniform1i(textureLocation, 0);
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

	void Graphics::createRenderBatches()
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

	void Graphics::freeMemory()
	{
		renderBatches.clear();

		for (int i = 0; i < glyphs.size(); i++)
			delete glyphs[i];

		glyphs.clear();
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

		glm::vec2 topLeft = transformPoint(glm::vec2(destRect.x, destRect.y));
		glm::vec2 topRight = transformPoint(glm::vec2(destRect.x + destRect.z, destRect.y));
		glm::vec2 bottomLeft = transformPoint(glm::vec2(destRect.x, destRect.y + destRect.w));
		glm::vec2 bottomRight = transformPoint(glm::vec2(destRect.x + destRect.z, destRect.y + destRect.w));

		newGlyph->topLeft.setPosition(topLeft.x, topLeft.y);
		newGlyph->topRight.setPosition(topRight.x, topRight.y);
		newGlyph->bottomLeft.setPosition(bottomLeft.x, bottomLeft.y);
		newGlyph->bottomRight.setPosition(bottomRight.x, bottomRight.y);

		setGlyphAttributes(newGlyph, textureID, depth, uvRect, color);

		glyphs.push_back(newGlyph);
	}

	glm::vec2 Graphics::transformPoint(glm::vec2 point) const
	{
		point = glm::rotate(point, rotateAngleInRadians);
		point *= scale;
		point += translateVec;

		return point;
	}

	void Graphics::setGlyphAttributes(Glyph* glyph, GLuint textureID, float depth, const glm::vec4& uvRect, const Color& color)
	{
		glyph->textureID = textureID;
		glyph->depth = depth;
		setGlyphUV(glyph, uvRect);
		setGlyphColor(glyph, color);
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
	
	void Graphics::drawTexture(const Texture& texture, const glm::vec2& position, const Color& color)
	{
		glm::vec2 size(texture.getWidth(), texture.getHeight());
		drawTexture(texture, position, size, color);
	}

	void Graphics::drawTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const Color& color)
	{
		draw(glm::vec4(position.x, position.y, size.x, size.y), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.getID(), nextTextureDepth + 0.1f, color);
	}	

	void Graphics::fillRect(const glm::vec2& position, const glm::vec2& size, const Color& color)
	{
		drawTexture(onePixelTexture, position, size, color);
	}

	void Graphics::drawRect(const glm::vec2& position, const glm::vec2& size, float weight, const Color& color)
	{
		// Top
		fillRect(glm::vec2(position.x + weight, position.y), glm::vec2(size.x - weight, weight), color);

		// Bottom
		fillRect(glm::vec2(position.x + weight, position.y + size.y - weight), glm::vec2(size.x - weight, weight), color);

		// Left
		fillRect(position, glm::vec2(weight, size.y), color);

		// Right
		fillRect(glm::vec2(position.x + size.x - weight, position.y + weight), glm::vec2(weight, size.y - 2* weight), color);
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

		freeMemory();
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

	void Graphics::setCamera(Camera2D* ncamera)
	{
		camera = ncamera;
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

	Camera2D* Graphics::getCamera() const
	{
		return camera;
	}
	
	std::vector<Glyph*> Graphics::getGlyphsVector() const
	{
		return glyphs;
	}

}