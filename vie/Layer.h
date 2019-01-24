#pragma once

#include <vector>
#include "Glyph.h"
#include "RenderBatch.h"
#include "GLSLProgram.h"


namespace vie
{
	class Camera2D;

	class Layer
	{
	public:
		explicit Layer(GLuint vbo, GLuint vao, Camera2D* camera);
		~Layer();

		void appendGlyph(Glyph* glyph);
		void sortGlyphsBy(GlyphSortType sortType);

		void setBackgroundColor(const Color& color);

		void begin();
		void end();
		void render();

		void setCamera(Camera2D* ncamera);
		Camera2D* getCamera() const;

		std::vector<Glyph*> getGlyphsVector() const;

	private:
		GLuint vbo;
		GLuint vao;
		Camera2D* camera;
		GLSLProgram colorProgram;

		std::vector<Glyph*> glyphs;
		std::vector<RenderBatch> renderBatches;

		void clearGL();
		void resetSamplerInShader();
		void setCameraMatrix();
		void transformGlyphsByCamera();
		void translateGlyphsByCamera();
		void rotateGlyphsByCamera();
		void createRenderBatches();
		void renderBatch() const;
		void removeAllGlyphsAndRenderBatches();
		
		static bool compareForward(Glyph* a, Glyph* b);
		static bool compareBackward(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);
	};

}