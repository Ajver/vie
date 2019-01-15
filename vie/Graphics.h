#pragma once

#include <vector>

#include "Camera2D.h"
#include "RenderBatch.h"
#include "GLSLProgram.h"
#include "Glyph.h"
#include "Texture.h"

namespace vie
{

	enum class GlyphSortType
	{
		// No sort
		NONE,

		// Normaly (Default)
		FRONT_TO_BACK,

		// Reverse
		BACK_TO_FRONT,

		// By texture (most efficient)
		TEXTURE
	};

	class Graphics
	{
	public:
		Graphics();
		~Graphics();

		void init(Camera2D* ncamera);

		// Controll the rendering
		void begin(GlyphSortType newSortType = GlyphSortType::FRONT_TO_BACK);
		void end();

		void setSortType(GlyphSortType newSortType);

		void setBackgroundColor(const Color& color);

		// Add new sprite to the batch
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureID, float depth, const Color& color = WHITE);
		
		// Sipmly draw texture on position x, y
		void drawTexture(const Texture& texture, float x, float y, const Color& color = WHITE);
		void drawTexture(const Texture& texture, const glm::vec2& position, const Color& color = WHITE);

		// Drawp texture on position x, y by scaling it into w, h size
		void drawTexture(const Texture& texture, float x, float y, float w, float h, const Color& color = WHITE);
		void drawTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const Color& color = WHITE);

		void fillRect(const glm::vec2& position, const glm::vec2& size, const Color& color);
		void drawRect(const glm::vec2& position, const glm::vec2& size, const Color& color);

		void setTranslate(glm::vec2 newTranslate);
		void setScale(float newScale);

		void translate(const glm::vec2& translateVector);
		void scaleUp(float scaleMod);
		void scaleDown(float scaleMod);

		glm::vec2 getTranslate();
		float getScale();

		void renderBatch();

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

		void createOnePixelTexture();
		void createVertexArray();
		void createRenderBatches();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

	};

}