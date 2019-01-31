#pragma once

#include <map>
#include <glm/glm.hpp>

#include "RenderBatch.h"
#include "GLSLProgram.h"
#include "Texture.h"
#include "Glyph.h"
#include "Camera2D.h"


namespace vie
{
	class Layer;

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
		void drawRect(const glm::vec2& position, const glm::vec2& size, float weight = 1.0f);

		void setTranslate(const glm::vec2& newTranslate);
		void setScale(float newScale);
		void setRotate(float newRotate);

		void translate(const glm::vec2& translateVector);
		void scaleUp(float scaleMod);
		void scaleDown(float scaleMod);
		void rotate(float angle);

		void render();

		glm::vec2 getTranslate() const;
		float getScale() const;
		float getRotate() const;
		Color getDefaultColor() const;
		GLuint getVBO() const;
		GLuint getVAO() const;
		float getNextTextureDepth() const;

		glm::vec2 transformPoint(glm::vec2 point) const;

	private:
		GLuint vbo;
		GLuint vao;
		GlyphSortType sortType;

		Layer* currentLayer;
		std::vector<Layer*> layers;

		Color defaultColor;
		float nextTextureDepth;
		Texture onePixelTexture;

		glm::vec2 translateVec;
		float scale;
		float rotateAngleInRadians;

		void enableAlphaBlending();
		void createOnePixelTexture();
		void createVertexArray();

		void clearScreen();
		void renderLayers();

		void setGlyphAttributes(Glyph* glyph, GLuint id, float depth, const glm::vec4& uvRect, const Color& color);
		void setGlyphUV(Glyph* glyph, const glm::vec4& uvRect);
		void setGlyphColor(Glyph* glyph, const Color& color);

	};

}