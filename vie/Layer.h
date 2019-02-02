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
		void sortGlyphs();

		void setCamera(Camera2D* ncamera);
		void setIsRemovingGlyphs(bool flag);

		bool isNamed(const std::string& n) const;
		Camera2D* getCamera() const;
		std::string getName() const;
		std::vector<Glyph*> getGlyphsVector() const;
		GlyphSortType getSortType() const;
		bool getIsRemovingGlyphs() const;

	private:
		std::string name;
		GLuint vbo;
		GLuint vao;
		Camera2D* camera;
		GLSLProgram colorProgram;
		bool isRemovingGlyphs;

		std::vector<Glyph*> glyphs;
		std::vector<Glyph*> transformedGlyphs;
		std::vector<RenderBatch> renderBatches;
		GlyphSortType sortType;

		void prepareShadersAndGL();
		void resetSamplerInShader();

		void renderGlyphs();
		void prepareGlyphs();
		void setCameraMatrix();
		void transformGlyphsByCamera();
		void createRenderBatches();
		void renderBatch() const;
		void clearAfterRender();
		void removeRenderBatches();
		void removeTransformedGlyphs();
		void removeOriginalGlyphs();
		
		static bool compareForward(Glyph* a, Glyph* b);
		static bool compareBackward(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);
	};

}