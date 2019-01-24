#include "Vertex.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

namespace vie
{

	void Vertex::setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	void Vertex::setColor(const Color& ncolor)
	{
		color = ncolor;
	}

	void Vertex::setUV(float u, float v)
	{
		uv.u = u;
		uv.v = v;
	}

	void Vertex::rotate(float angle)
	{
		glm::vec2 rotatedPos = glm::rotate(glm::vec2(position.x, position.y), angle);
		setPosition(rotatedPos.x, rotatedPos.y);
	}

	void Vertex::translate(float x, float y)
	{
		position.x += x;
		position.y += y;
	}

}