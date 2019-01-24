#pragma once

#include <map>
#include <glm/glm.hpp>

#include "RenderBatch.h"
#include "GLSLProgram.h"
#include "Texture.h"
#include "Glyph.h"

namespace vie
{
	class Camera2D;
	class Layer;

	class Graphics
	{
	public:
		Graphics();
		~Graphics();

		void init(Camera2D* mainCamera);
		void createLayer(const std::string& layerName);
		bool hasLayer(const std::string& layerName);
		void switchLayer(const std::string& layerName);
		void removeLayer(const std::string& layerName);

		Layer* getCurrentLayer() const;
		std::string getCurrentLayerName() const;

		// Controll the rendering
		void begin();
		void end();
		void render();

		void setSortType(GlyphSortType newSortType);

		void setBackgroundColor(const Color& color);

		// Add new sprite to the batch
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureID, float depth, const Color& color = COLOR::WHITE);
		
		// Sipmly draw texture on Position with original texture size
		void drawTexture(const Texture& texture, const glm::vec2& position, const Color& color = COLOR::WHITE);

		// Drawp texture on Position by scaling it to Size
		void drawTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const Color& color = COLOR::WHITE);

		void fillRect(const glm::vec2& position, const glm::vec2& size, const Color& color);
		void drawRect(const glm::vec2& position, const glm::vec2& size, float weight, const Color& color);

		void setTranslate(const glm::vec2& newTranslate);
		void setScale(float newScale);
		void setRotate(float newRotate);

		void translate(const glm::vec2& translateVector);
		void scaleUp(float scaleMod);
		void scaleDown(float scaleMod);
		void rotate(float angle);

		glm::vec2 getTranslate() const;
		float getScale() const;
		float getRotate() const;
		GlyphSortType getSortType() const;

		glm::vec2 transformPoint(glm::vec2 point) const;

	private:
		GLuint vbo;
		GLuint vao;
		GlyphSortType sortType;

		std::string currentLayerName;
		Layer* currentLayer;
		std::map<std::string, Layer*> layersMap;

		float nextTextureDepth;
		Texture onePixelTexture;

		glm::vec2 translateVec;
		float scale;
		float rotateAngleInRadians;

		void enableAlphaBlending();
		void createOnePixelTexture();
		void createVertexArray();

		void setGlyphAttributes(Glyph* glyph, GLuint id, float depth, const glm::vec4& uvRect, const Color& color);
		void setGlyphUV(Glyph* glyph, const glm::vec4& uvRect);
		void setGlyphColor(Glyph* glyph, const Color& color);

	};

}