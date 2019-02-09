#include "Graphics.h"

#include <algorithm>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "Camera2D.h"
#include "Errors.h"
#include "Window.h"
#include "Layer.h"
#include "SpriteFont.h"

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
		currentLayer(nullptr),
		defaultColor(COLOR::WHITE),
		spriteFont(nullptr)
	{
	}

	Graphics::~Graphics()
	{
		for (auto& currLayer : layers)
			delete currLayer;

		layers.clear();
	}

	void Graphics::init(Camera2D* mainCamera)
	{
		enableAlphaBlending();
		createOnePixelTexture();
		createVertexArray();

		currentLayer = new Layer("main", vbo, vao, mainCamera);
		layers.push_back(currentLayer);
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

	void Graphics::appendLayer(Layer* layer)
	{
		layers.push_back(layer);
	}
	void Graphics::createLayer(const std::string& layerName, Camera2D* camera)
	{
		if (containsLayer(layerName))
			fatalError("Error: Cannot create layer with name: " + layerName + " (Layer exist)");
		else
			layers.push_back(new Layer(layerName, vbo, vao, camera));
	}
	void Graphics::switchLayer(const std::string& layerName)
	{
		for (auto& currLayer : layers)
		{
			if (currLayer->isNamed(layerName))
			{
				currentLayer = currLayer;
				return;
			}			
		}
		fatalError("Error: Cannot switch to layer with name: " + layerName + " (Layer not found)");
	}
	void Graphics::removeLayer(const std::string& layerName)
	{
		if (layerName == "main")
			fatalError("Error: Cannot remove main layer!");
		else
		{
			int osize = layers.size();
			for (int i = 0; i < osize; i++)
			{
				Layer* layer = *(&layers[0] + i);
				if (layer->isNamed(layerName))
				{
					layers.erase(layers.begin() + i);
					return;
				}
			}
		}

		fatalError("Error: Cannot remove layer with name: " + layerName + " (Layer not found)");
	}
	bool Graphics::containsLayer(const std::string& layerName) const
	{
		for (auto& currLayer : layers)
			if (currLayer->isNamed(layerName))
				return true;

		return false;
	}
	Layer* Graphics::getCurrentLayer() const
	{
		return currentLayer;
	}
	Layer* Graphics::getLayerByName(const std::string& layerName) const
	{
		for (auto& currLayer : layers)
		{
			if (currLayer->isNamed(layerName))
				return currLayer;
		}
		fatalError("Error: Cannot get layer with name: " + layerName + " (Layer not found)");
		return nullptr;
	}

	void Graphics::render()
	{
		clearScreen();
		renderLayers();
		nextTextureDepth = 0.0f;
	}

	void Graphics::clearScreen()
	{
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Graphics::renderLayers()
	{
		for (auto& currLayer : layers)
			currLayer->render();
	}

	void Graphics::setColor(const Color& color)
	{
		defaultColor = color;
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
		drawTexture(texture, position, texture.getSize(), color);
	}

	void Graphics::drawTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const Color& color)
	{
		draw(glm::vec4(position.x, position.y, size.x, size.y), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), texture.getID(), getNextTextureDepth(), color);
	}	
	void Graphics::drawTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const glm::vec2& uv, const Color& color)
	{
		draw(glm::vec4(position.x, position.y, size.x, size.y), glm::vec4(0.0f, 0.0f, uv.x, uv.y), texture.getID(), getNextTextureDepth(), color);
	}
	void Graphics::drawTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const glm::vec4& uv, const Color& color)
	{
		draw(glm::vec4(position.x, position.y, size.x, size.y), uv, texture.getID(), getNextTextureDepth(), color);
	}

	void Graphics::fillRect(const glm::vec2& position, const glm::vec2& size)
	{
		drawTexture(onePixelTexture, position, size, defaultColor);
	}

	void Graphics::drawRect(const glm::vec2& position, const glm::vec2& size, float weight)
	{
		// Top
		fillRect(glm::vec2(position.x + weight, position.y), glm::vec2(size.x - weight, weight));

		// Bottom
		fillRect(glm::vec2(position.x + weight, position.y + size.y - weight), glm::vec2(size.x - weight, weight));

		// Left
		fillRect(position, glm::vec2(weight, size.y));

		// Right
		fillRect(glm::vec2(position.x + size.x - weight, position.y + weight), glm::vec2(weight, size.y - 2 * weight));
	}

	void Graphics::drawString(const std::string& str, const glm::vec2& position, TextJustification just)
	{
		if (spriteFont == nullptr)
			fatalError("Error: Graphics class has no font initialized.\nTry setFont() before drawString()");
		else
			spriteFont->draw(this, str.c_str(), position, glm::vec2(scale), getNextTextureDepth(), defaultColor, just);
	}

	void Graphics::setFont(SpriteFont* nfont)
	{
		spriteFont = nfont;
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

	Color Graphics::getDefaultColor() const
	{
		return defaultColor;
	}

	SpriteFont* Graphics::getFont() const
	{
		return spriteFont;
	}

	GLuint Graphics::getVBO() const
	{
		return vbo;
	}
	GLuint Graphics::getVAO() const
	{
		return vao;
	}

	float Graphics::getNextTextureDepth() const
	{
		return nextTextureDepth + 0.1f;
	}

}