#include "Graphics.h"

#include <algorithm>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "Camera2D.h"
#include "Logger.h"
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
		spriteFont(nullptr),
		nextTextureDepthStep(0.1f),
		ovalRenderingPrecision(1.0f)
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
			Logger::fatalError("Error: Cannot create layer with name: " + layerName + " (Layer exist)");
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
		Logger::fatalError("Error: Cannot switch to layer with name: " + layerName + " (Layer not found)");
	}
	void Graphics::removeLayer(const std::string& layerName)
	{
		if (layerName == "main")
			Logger::fatalError("Error: Cannot remove main layer!");
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

		Logger::fatalError("Error: Cannot remove layer with name: " + layerName + " (Layer not found)");
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
		Logger::fatalError("Error: Cannot get layer with name: " + layerName + " (Layer not found)");
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
		glyph->setUV(uvRect);
		glyph->setColor(color);
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

	void Graphics::drawTriangle(const glm::vec2& posA, const glm::vec2& posB, const glm::vec2& posC, float weight)
	{
		// This 'nextTextureDepth -= nextTextureDepthStep' operation is important for render all lines in the same depth
		drawLine(posA, posB, weight);
		nextTextureDepth -= nextTextureDepthStep;
		drawLine(posB, posC, weight);
		nextTextureDepth -= nextTextureDepthStep;
		drawLine(posC, posA, weight);
	}

	void Graphics::fillTriangle(const glm::vec2& posA, const glm::vec2& posB, const glm::vec2& posC)
	{
		nextTextureDepth = getNextTextureDepth();

		Glyph *newGlyph = new Glyph();

		glm::vec2 a = transformPoint(posA);
		glm::vec2 b = transformPoint(posB);
		glm::vec2 c = transformPoint(posC);

		newGlyph->topLeft.setPosition(a.x, a.y);
		newGlyph->topRight.setPosition(b.x, b.y);
		newGlyph->bottomLeft.setPosition(c.x, c.y);
		newGlyph->bottomRight.setPosition(c.x, c.y);

		setGlyphAttributes(newGlyph, onePixelTexture.getID(), nextTextureDepth, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), defaultColor);

		currentLayer->appendGlyph(newGlyph);
	}

	void Graphics::drawOval(const glm::vec2& position, const glm::vec2& size, float weight)
	{
		static const float TWO_PI = M_PI * 2.0f;
		const float step = TWO_PI / (ovalRenderingPrecision * fmin(size.x, size.y) * 0.4f);

		glm::vec2 prev = glm::vec2(position.x + size.x, position.y);
		for (float i = step; i <= TWO_PI; i += step)
		{
			glm::vec2 a(cos(i)*size.x, sin(i)*size.y);
			a += position;
			drawLine(prev, a, weight);
			prev = a;
		}
		drawLine(prev, glm::vec2(position.x + size.x, position.y), weight);
	}

	void Graphics::fillOval(const glm::vec2& position, const glm::vec2& size)
	{
		static const float TWO_PI = M_PI * 2.0f;
		const float step = TWO_PI / (ovalRenderingPrecision * fmin(size.x, size.y) * 0.4f);

		glm::vec2 prev(position.x + size.x, position.y);
		glm::vec2 curr(cos(step)*size.x + position.x, sin(step)*size.y + position.y);
		for (float i = step * 2.0f; i <= TWO_PI; i += step * 2.0f)
		{
			glm::vec2 a(cos(i)*size.x + position.x, sin(i)*size.y + position.y);
			fillQuadrangle(prev, curr, a, position);
			prev = a;
			curr = glm::vec2(cos(i + step)*size.x + position.x, sin(i + step)*size.y + position.y);
		}
		fillTriangle(prev, glm::vec2(position.x + size.x, position.y), position);
	}

	void Graphics::drawPolygon(std::vector<glm::vec2> polygon, float weight)
	{
		if (polygon.size() < 2)
			return;

		if (polygon.size() == 3)
		{
			drawTriangle(polygon[0], polygon[1], polygon[2], weight);
			return;
		}

		if (polygon.size() == 4)
		{
			drawQuadrangle(polygon[0], polygon[1], polygon[2], polygon[3], weight);
			return;
		}

		// This 'nextTextureDepth -= nextTextureDepthStep' operation is important for render all lines in the same depth
		for (int i = 0; i < polygon.size() - 1; i++)
		{
			nextTextureDepth -= nextTextureDepthStep;
			drawLine(polygon[i], polygon[i + 1], weight);
		}

		nextTextureDepth -= nextTextureDepthStep;
		drawLine(polygon[0], polygon[polygon.size() - 1], weight);
	}

	void Graphics::fillPolygon(std::vector<glm::vec2> polygon)
	{
		if (polygon.size() < 2)
			return;

		if (polygon.size() == 3)
		{
			fillTriangle(polygon[0], polygon[1], polygon[2]);
			return;
		}

		if (polygon.size() == 4)
		{
			fillQuadrangle(polygon[0], polygon[1], polygon[2], polygon[3]);
			return;
		}

		// This 'nextTextureDepth -= nextTextureDepthStep' operation is important for render all lines in the same depth
		for (int i = 1; i < polygon.size() - 2; i += 2)
		{
			nextTextureDepth -= nextTextureDepthStep;
			fillQuadrangle(polygon[0], polygon[i], polygon[i + 1], polygon[i + 2]);
		}
		if (polygon.size() % 2 != 0)
		{
			nextTextureDepth -= nextTextureDepthStep;
			fillTriangle(polygon[0], polygon[polygon.size() - 2], polygon[polygon.size() - 1]);
		}
	}

	void Graphics::drawQuadrangle(const glm::vec2& posA, const glm::vec2& posB, const glm::vec2& posC, const glm::vec2& posD, float weight)
	{
		// This 'nextTextureDepth -= nextTextureDepthStep' operation is important for render all lines in the same depth
		drawLine(posA, posB, weight);
		nextTextureDepth -= nextTextureDepthStep;
		drawLine(posB, posC, weight);
		nextTextureDepth -= nextTextureDepthStep;
		drawLine(posC, posD, weight);
		nextTextureDepth -= nextTextureDepthStep;
		drawLine(posD, posA, weight);
	}

	void Graphics::fillQuadrangle(const glm::vec2& posA, const glm::vec2& posB, const glm::vec2& posC, const glm::vec2& posD)
	{
		nextTextureDepth = getNextTextureDepth();

		Glyph *newGlyph = new Glyph();

		glm::vec2 a = transformPoint(posA);
		glm::vec2 b = transformPoint(posB);
		glm::vec2 c = transformPoint(posC);
		glm::vec2 d = transformPoint(posD);

		newGlyph->topLeft.setPosition(a.x, a.y);
		newGlyph->topRight.setPosition(b.x, b.y);
		newGlyph->bottomRight.setPosition(c.x, c.y);
		newGlyph->bottomLeft.setPosition(d.x, d.y);

		setGlyphAttributes(newGlyph, onePixelTexture.getID(), nextTextureDepth, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), defaultColor);

		currentLayer->appendGlyph(newGlyph);
	}

	void Graphics::drawLine(const glm::vec2& posA, const glm::vec2& posB, float weight)
	{
		nextTextureDepth = getNextTextureDepth();

		Glyph *newGlyph = new Glyph();

		float angle = atan2f(posB.y - posA.y, posB.x - posA.x);

		glm::vec2 offset = glm::rotate(glm::vec2(0.0f, -weight), angle) * 0.5f;

		glm::vec2 a1 = transformPoint(posA - offset);
		glm::vec2 a2 = transformPoint(posA + offset);
		glm::vec2 b1 = transformPoint(posB - offset);
		glm::vec2 b2 = transformPoint(posB + offset);

		newGlyph->topLeft.setPosition(a1.x, a1.y);
		newGlyph->topRight.setPosition(a2.x, a2.y);
		newGlyph->bottomLeft.setPosition(b1.x, b1.y);
		newGlyph->bottomRight.setPosition(b2.x, b2.y);

		setGlyphAttributes(newGlyph, onePixelTexture.getID(), nextTextureDepth, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), defaultColor);

		currentLayer->appendGlyph(newGlyph);
	}

	void Graphics::drawString(const std::string& str, const glm::vec2& position, TextJustification just)
	{
		if (spriteFont == nullptr)
			Logger::fatalError("Error: Graphics class has no font initialized.\nTry setFont() before drawString()");
		else
			spriteFont->draw(this, str.c_str(), position, glm::vec2(scale), getNextTextureDepth(), defaultColor, just);
	}

	void Graphics::setOvalPrecision(float nprec)
	{
		ovalRenderingPrecision = nprec;
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

	float Graphics::getOvalPrecision() const
	{
		return ovalRenderingPrecision;
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
		return nextTextureDepth + nextTextureDepthStep;
	}

}