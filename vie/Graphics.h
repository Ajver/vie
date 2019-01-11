#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Color.h"

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

	class Graphics
	{
	public:
		Graphics();
		~Graphics();
		void init();

		// Controll the rendering
		void begin(GlyphSortType st = GlyphSortType::TEXTURE);
		void end();

		void setBackgroundColor(const Color& color);

		// Add new sprite to the batch
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint textureID, float depth, const Color& color = WHITE);
		
		// Sipmly draw texture on position x, y
		void drawTexture(const Texture& texture, float x, float y, const Color& color = WHITE);
		void drawTexture(const Texture& texture, glm::vec2& position, const Color& color = WHITE);

		// Drawp texture on position x, y by scaling it into w, h size
		void drawTexture(const Texture& texture, float x, float y, float w, float h, const Color& color = WHITE);
		void drawTexture(const Texture& texture, glm::vec2& position, glm::vec2& size, const Color& color = WHITE);

		void renderBatch();

	private:

		/////////////////////////////////////////////////////////////////////////////////////////

		class Camera2D
		{
		public:
			Camera2D();
			~Camera2D();

			void init();
			void update();

			void setPosition(glm::vec2 npos);
			void setScale(float nscale);

			glm::vec2 screenToWorldPos(glm::vec2 screenPosition);

			glm::vec2 getPosition();
			float getScale();
			glm::mat4 getCameraMatrix();

		private:
			bool needsMatrixUpdate;

			glm::vec2 position;
			glm::mat4 cameraMatrix;
			glm::mat4 orthoMatrix;

			float scale;
		};

		/////////////////////////////////////////////////////////////////////////////////////////

		class GLSLProgram
		{
		public:
			GLSLProgram();
			~GLSLProgram();

			void compileShaders();

			void linkShaders();

			void addAtribute(const std::string&);

			GLuint getUnitformLocation(const std::string &);

			void use();
			void unuse();

		private:
			int numAttributes;

			GLuint programID;

			GLuint vertexShaderID;
			GLuint fragmentShaderID;

			void compileShader(const std::string&, GLuint);
			std::string getVertexShader();
			std::string getFragmentShader();
		};

		/////////////////////////////////////////////////////////////////////////////////////////

		struct Vertex
		{
			struct Position
			{
				float x, y;
			};

			//-----------------------------------------------

			struct UV
			{
				float u;
				float v;
			};

			//-----------------------------------------------

			Position position;
			Color color;
			UV uv;

			void setPosition(float x, float y)
			{
				position.x = x;
				position.y = y;
			}

			void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255)
			{
				color.setColor(r, g, b, a);
			}

			void setUV(float u, float v)
			{
				uv.u = u;
				uv.v = v;
			}
		};

		/////////////////////////////////////////////////////////////////////////////////////////

		struct Glyph
		{
			GLuint textureID;
			float depth;

			Vertex topLeft;
			Vertex topRight;
			Vertex bottomLeft;
			Vertex bottomRight;
		};

		/////////////////////////////////////////////////////////////////////////////////////////

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

		/////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////

		GLuint vbo;
		GLuint vao;
		GlyphSortType sortType;

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