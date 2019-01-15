#pragma once

#include <GL/glew.h>

namespace vie
{

	struct RenderBatch
	{
		RenderBatch(GLuint of, GLuint nv, GLuint tID) :
			offset(of),
			numVertices(nv),
			textureID(tID)
		{}

		GLuint offset;
		GLuint numVertices;
		GLuint textureID;
	};

}