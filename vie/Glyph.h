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
	};

}