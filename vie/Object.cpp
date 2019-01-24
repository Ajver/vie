#include "Object.h"

#include <string>

namespace vie
{

	Object::Object() :
		position(glm::vec2(0, 0)),
		size(glm::vec2(0, 0)),
		velocity(glm::vec2(0, 0))
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

	void Object::setIsMouseHover(bool flag)
	{
		isMouseHover = flag;
	}

	void Object::setLabel(const std::string& nlabel)
	{
		label = nlabel;
	}

	glm::vec2 Object::getPosition() const
	{
		return position;
	}

	glm::vec2 Object::getSize() const
	{
		return size;
	}

	glm::vec2 Object::getVelocity() const
	{
		return velocity;
	}

	bool Object::getIsMouseHover() const
	{
		return isMouseHover;
	}
	
	std::string Object::getLabel() const
	{
		return label;
	}

	bool Object::isPointInside(const glm::vec2& point) const
	{
		return point.x >= position.x &&
			point.x < position.x + size.x &&
			point.y >= position.y &&
			point.y < position.y + size.y;
	}

	bool Object::is(const std::string& lab) const
	{
		return label == lab;
	}

	void Object::update(float et) {}
	void Object::render(Graphics* g) {}

	void Object::onMouseEnter() {}
	void Object::onMouseLeave() {}
	void Object::onMouseMove() {}
	void Object::onMouseDrag() {}
	void Object::onMousePress() {}
	void Object::onMouseRelease() {}
	void Object::onKeyPress() {}
	void Object::onKeyRelease() {}

}