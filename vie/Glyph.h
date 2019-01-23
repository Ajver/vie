#pragma once

#include "Vertex.h"

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

		void rotateByAngle(float angle)
		{
			topLeft.rotate(angle);
			topRight.rotate(angle);
			bottomLeft.rotate(angle);
			bottomRight.rotate(angle);
		}

		void translateByVec2(const glm::vec2& vec)
		{
			topLeft.translate(vec.x, vec.y);
			topRight.translate(vec.x, vec.y);
			bottomLeft.translate(vec.x, vec.y);
			bottomRight.translate(vec.x, vec.y);
		}
	};

}