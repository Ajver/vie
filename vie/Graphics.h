#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Vertex.h"
#include "GLSLProgram.h"
#include "Camera2D.h"

#include "Texture.h"

namespace vie
{

	enum class GlyphSortType
	{
		// No sort
		NONE,

		// Normaly 
		FRONT_TO_BACK,

		// Reverse
		BACK_TO_FRONT,

		// By texture (most efficient)
		TEXTURE
	};

	struct Glyph
	{
		GLuint textureID;
		float depth;

		Vertex topLeft;
		Vertex topRight;
		Vertex bottomLeft;
		Vertex bottomRight;
	};

	class RenderBatch
	{
	public:
		RenderBatch(GLuint of, GLuint nv, GLuint tID) : 
			offset(of), 
			numVertices(nv), 
			textureID(tID)
		{}

		GLuint offset;
		GLuint numVertices;
		GLuint textureID;
	};

	class Graphics
	{
	public:
		Graphics();
		~Graphics();
		void init(unsigned int sw, unsigned int sh);

		// Controll the rendering
		void begin(GlyphSortType st = GlyphSortType::TEXTURE);
		void end();

		// Add new sprite to the batch
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureID, float depth, const Color& color = WHITE);
		
		// Sipmly draw texture on position x, y
		void drawTexture(const Texture& texture, float x, float y, const Color& color = WHITE);

		// Drawp texture on position x, y by scaling it into w, h size
		void drawTexture(const Texture& texture, float x, float y, float w, float h, const Color& color = WHITE);
		
		void renderBatch();

	private:
		GLuint vbo;
		GLuint vao;
		GlyphSortType sortType;

		// Screen size
		unsigned int screenWidth;
		unsigned int screenHeight;

		Camera2D camera;
		GLSLProgram colorProgram;

		std::vector<Glyph*> glyphs;
		std::vector<RenderBatch> renderBatches;

		void createVertexArray();
		void createRenderBatches();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);
	};

}