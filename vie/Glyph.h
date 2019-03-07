#pragma once

#include "Vertex.h"

#include <glm/glm.hpp>

namespace vie
{

	class Glyph
	{
	public:
		Glyph();
		Glyph(const Glyph& other);

		GLuint textureID;
		float depth;

		Vertex topLeft;
		Vertex topRight;
		Vertex bottomLeft;
		Vertex bottomRight;

		void rotateByAngle(float angle);
		void translateByVec2(const glm::vec2& vec);
		void invertInYAxis(float screenHeight);
		void setUV(const glm::vec4& uvRect);
		void setColor(const Color& color);
	};

	enum class GlyphSortType
	{
		// No sort
		NONE,

		// Normaly (Default)
		FORWARD,

		// Reverse
		BACKWARD,

		// By texture (most efficient)
		TEXTURE
	};
}