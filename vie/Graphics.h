#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "RenderBatch.h"
#include "GLSLProgram.h"
#include "Texture.h"
#include "Glyph.h"

namespace vie
{
	class Camera2D;

	class Graphics
	{
	public:
		Graphics();
		~Graphics();

		void init(Camera2D* ncamera);

		// Controll the rendering
		void begin(GlyphSortType newSortType = GlyphSortType::FORWARD);
		void end();

		void setSortType(GlyphSortType newSortType);
		void setCamera(Camera2D* ncamera);

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
		Camera2D* getCamera() const;
		std::vector<Glyph*> getGlyphsVector() const;

		void renderBatch();

		glm::vec2 transformPoint(glm::vec2 point) const;

	private:
		GLuint vbo;
		GLuint vao;
		GlyphSortType sortType;

		Camera2D* camera;
		GLSLProgram colorProgram;

		float nextTextureDepth;
		Texture onePixelTexture;
		std::vector<Glyph*> glyphs;
		std::vector<RenderBatch> renderBatches;

		glm::vec2 translateVec;
		float scale;
		float rotateAngleInRadians;

		void clearGL();
		void resetSamplerInShader();

		void setCameraMatrix();
		void transformGlyphsByCamera();
		void translateGlyphsByCamera();
		void rotateGlyphsByCamera();

		void sortGlyphs();
		void freeMemory();

		void enableAlphaBlending();
		void createOnePixelTexture();
		void createVertexArray();
		void createRenderBatches();

		void setGlyphAttributes(Glyph* glyph, GLuint id, float depth, const glm::vec4& uvRect, const Color& color);
		void setGlyphUV(Glyph* glyph, const glm::vec4& uvRect);
		void setGlyphColor(Glyph* glyph, const Color& color);

		static bool compareForward(Glyph* a, Glyph* b);
		static bool compareBackward(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

	};

}