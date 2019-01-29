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
		explicit Layer(const std::string& n, GLuint vbo, GLuint vao, Camera2D* camera);
		~Layer();

		void appendGlyph(Glyph* glyph);

		void render();
		void setSortType(GlyphSortType newSortType);

		void setCamera(Camera2D* ncamera);
		Camera2D* getCamera() const;

		bool isNamed(const std::string& n) const;
		std::string getName() const;
		std::vector<Glyph*> getGlyphsVector() const;

	private:
		std::string name;
		GLuint vbo;
		GLuint vao;
		Camera2D* camera;
		GLSLProgram colorProgram;

		std::vector<Glyph*> glyphs;
		std::vector<RenderBatch> renderBatches;
		GlyphSortType sortType;

		void prepareShadersAndGL();
		void resetSamplerInShader();

		void renderGlyphs();
		void prepareGlyphs();
		void sortGlyphs();
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