#include "Object.h"

namespace vie
{

	Object::Object()
	{
	}


	Object::~Object()
	{
	}

	void Object::setPosition(const glm::vec2& npos)
	{
		position = npos;
	}

	void Object::setSize(const glm::vec2& nsize)
	{
		size = nsize;
	}

	void Object::setVelocity(const glm::vec2& nvel)
	{
		velocity = nvel;
	}

	glm::vec2 Object::getPosition()
	{
		return position;
	}

	glm::vec2 Object::getSize()
	{
		return size;
	}

	glm::vec2 Object::getVelocity()
	{
		return velocity;
	}
}