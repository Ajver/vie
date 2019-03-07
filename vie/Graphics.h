#pragma once

#include <map>
#include <glm/glm.hpp>

#include "RenderBatch.h"
#include "GLSLProgram.h"
#include "Texture.h"
#include "Glyph.h"
#include "Camera2D.h"
#include "TextJustification.h"


namespace vie
{
	class Layer;
	class SpriteFont;

	class Graphics
	{
	public:
		Graphics();
		~Graphics();

		void init(Camera2D* mainCamera);
		void appendLayer(Layer* layer);
		void createLayer(const std::string& layerName, Camera2D* camera = new Camera2D());
		void switchLayer(const std::string& layerName);
		void removeLayer(const std::string& layerName);
		
		bool containsLayer(const std::string& layerName) const;
		Layer* getCurrentLayer() const;
		Layer* getLayerByName(const std::string& layerName) const;

		void setColor(const Color& color);
		void setBackgroundColor(const Color& color);

		// Add new sprite to the batch
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureID, float depth, const Color& color = COLOR::WHITE);
		
		void drawTexture(const Texture& texture, const glm::vec2& position, const Color& color = COLOR::WHITE);
		void drawTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const Color& color = COLOR::WHITE);
		void drawTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const glm::vec2& uv, const Color& color = COLOR::WHITE);
		void drawTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const glm::vec4& uv, const Color& color = COLOR::WHITE);

		void fillRect(const glm::vec2& position, const glm::vec2& size);
		void drawRect(const glm::vec2& position, const glm::vec2& size, float weight = 2.0f);

		void fillTriangle(const glm::vec2& posA, const glm::vec2& posB, const glm::vec2& posC);
		void drawTriangle(const glm::vec2& posA, const glm::vec2& posB, const glm::vec2& posC, float weight = 2.0f);

		void drawOval(const glm::vec2& position, const glm::vec2& size, float weight = 2.0f);
		void fillOval(const glm::vec2& position, const glm::vec2& size);

		void drawPolygon(std::vector<glm::vec2> polygon, float weight = 2.0f);
		void fillPolygon(std::vector<glm::vec2> polygon);

		void drawQuadrangle(const glm::vec2& posA, const glm::vec2& posB, const glm::vec2& posC, const glm::vec2& posD, float weight = 2.0f);
		void fillQuadrangle(const glm::vec2& posA, const glm::vec2& posB, const glm::vec2& posC, const glm::vec2& posD);

		void drawLine(const glm::vec2& posA, const glm::vec2& posB, float weight = 2.0f);

		void drawString(const std::string& str, const glm::vec2& position, TextJustification just = TextJustification::LEFT);

		void setOvalPrecision(float nprec);
		void setFont(SpriteFont* nfont);
		void setTranslate(const glm::vec2& newTranslate);
		void setScale(float newScale);
		void setRotate(float newRotate);

		void translate(const glm::vec2& translateVector);
		void scaleUp(float scaleMod);
		void scaleDown(float scaleMod);
		void rotate(float angle);

		void render();

		float getOvalPrecision() const;
		glm::vec2 getTranslate() const;
		float getScale() const;
		float getRotate() const;
		Color getDefaultColor() const;
		SpriteFont* getFont() const;
		GLuint getVBO() const;
		GLuint getVAO() const;
		float getNextTextureDepth() const;

		glm::vec2 transformPoint(glm::vec2 point) const;

	private:
		GLuint vbo;
		GLuint vao;
		GlyphSortType sortType;
		SpriteFont* spriteFont;

		Layer* currentLayer;
		std::vector<Layer*> layers;

		Color defaultColor;
		float nextTextureDepth;
		float nextTextureDepthStep;
		Texture onePixelTexture;
		float ovalRenderingPrecision;

		glm::vec2 translateVec;
		float scale;
		float rotateAngleInRadians;

		void enableAlphaBlending();
		void createOnePixelTexture();
		void createVertexArray();

		void clearScreen();
		void renderLayers();

		void setGlyphAttributes(Glyph* glyph, GLuint id, float depth, const glm::vec4& uvRect, const Color& color);
		void setGlyphPosition(Glyph* glyph, const glm::vec2& topLeft, const glm::vec2& topRight, const glm::vec2& bottomLeft, const glm::vec2& bottomRight);


	};

}