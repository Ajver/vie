#pragma once

#include <vector>
#include "Glyph.h"
#include "RenderBatch.h"


namespace vie
{

	class Layer
	{
	public:
		explicit Layer(GLuint vbo, GLuint vao);
		~Layer();

		void appendGlyph(Glyph* glyph);

		void sortGlyphsBy(GlyphSortType sortType);

		void renderGlyphs();

		std::vector<Glyph*> getGlyphsVector();

	private:
		GLuint vbo;
		GLuint vao;
		std::vector<Glyph*> glyphs;
		std::vector<RenderBatch> renderBatches;

		void createRenderBatches();
		void renderBatch();
		void removeAllGlyphsAndRenderBatches();
		
		static bool compareForward(Glyph* a, Glyph* b);
		static bool compareBackward(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);
	};

}