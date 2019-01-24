#include "Graphics.h"

#include <algorithm>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "Camera2D.h"
#include "Errors.h"
#include "Window.h"
#include "Layer.h"

namespace vie
{

	Graphics::Graphics() :
		vbo(0),
		vao(0),
		sortType(GlyphSortType::FORWARD),
		scale(1.0f),
		translateVec(glm::vec2(0, 0)),
		nextTextureDepth(0.0f),
		rotateAngleInRadians(0.0f),
		currentLayerName(""),
		currentLayer(nullptr)
	{
	}

	Graphics::~Graphics()
	{
	}

	void Graphics::init(Camera2D* mainCamera)
	{
		enableAlphaBlending();
		createOnePixelTexture();
		createVertexArray();
		currentLayerName = "main_layer";
		currentLayer = new Layer(vbo, vao, mainCamera);
		layersMap[currentLayerName] = currentLayer;
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

	void Graphics::createLayer(const std::string& layerName)
	{
		if (hasLayer(layerName))
			fatalError("Error: Cannot create layer with name: " + layerName + " (Layer exist)");
		else
			layersMap[layerName] = new Layer(vbo, vao, new Camera2D());
	}

	bool Graphics::hasLayer(const std::string& layerName)
	{
		return layersMap.find(layerName) != layersMap.end();
	}

	void Graphics::switchLayer(const std::string& layerName)
	{
		auto layer = layersMap.find(layerName);
		if (layer != layersMap.end())
		{
			currentLayerName = layerName;
			currentLayer = layer->second;
		}
		else
			fatalError("Error: Cannot switch to layer with name: " + layerName + " (Layer not found)");
	}

	void Graphics::removeLayer(const std::string& layerName)
	{
		if (hasLayer(layerName))
			layersMap.erase(layerName);
		else
			fatalError("Error: Cannot remove layer with name: " + layerName + " (Layer not found)");
	}

	Layer* Graphics::getCurrentLayer() const
	{
		return currentLayer;
	}
	std::string Graphics::getCurrentLayerName() const
	{
		return currentLayerName;
	}

	void Graphics::begin()
	{
		nextTextureDepth = 0.0f;
		currentLayer->begin();
	}

	void Graphics::end()
	{
		currentLayer->end();
		currentLayer->sortGlyphsBy(sortType);
	}

	void Graphics::render()
	{
		currentLayer->render();
	}

	void Graphics::setSortType(GlyphSortType newSortType)
	{
		sortType = newSortType;
	}

	void Graphics::setBackgroundColor(const Color& color)
	{
		currentLayer->setBackgroundColor(color);
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

		currentLayer->appendGlyph(newGlyph);
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
		fillRect(glm::vec2(position.x + size.x - weight, position.y + weight), glm::vec2(weight, size.y - 2 * weight), color);
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