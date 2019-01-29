#pragma once

#include "Vertex.h"

#include <glm/glm.hpp>

namespace vie
{

	struct Glyph
	{
		GLuint textureID;
		float depth;

		Vertex topLeft;
		Vertex topRight;
		Vertex bottomLeft;
		Vertex bottomRight;

		void rotateByAngle(float angle);
		void translateByVec2(const glm::vec2& vec);
		void invertInYAxis(float screenHeight);
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